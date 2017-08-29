// VcTab.cpp : implementation file
//

#include "stdafx.h"
#include "tb.h"
#include "VcTab.h"
#include "EditDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVcTab

#ifndef COLOR_GRADIENTINACTIVECAPTION
#define COLOR_GRADIENTINACTIVECAPTION 28
#endif

#define VC_TAB _T("__VC_TAB__")			//�Զ��崰������
#define DISTWIDTH	10					//��ǩ���ε��ϱߺ��±߲��1/2
#define IDC_NEWLAB		2010			//�޸ı�ǩ���ı�ʱ�����ı༭��ؼ�ID

const COLORREF CVcTab::m_clNormal
=GetSysColor(COLOR_BTNFACE),
CVcTab::m_clSel=GetSysColor(COLOR_WINDOW),
CVcTab::m_clTrack=GetSysColor(COLOR_GRADIENTINACTIVECAPTION),
CVcTab::m_clText=RGB(0,0,0);
const CPen CVcTab::m_pen(0,1,RGB(0,0,0));		//��ǩ�߿򻭱�

CVcTab::CVcTab()
{
	m_nTrack=-1;
	m_nCurSel=0;

}

CVcTab::~CVcTab()
{
	if(m_font.GetSafeHandle())
		m_font.DeleteObject();
	if(m_fontSel.GetSafeHandle())
		m_font.DeleteObject();
}


BEGIN_MESSAGE_MAP(CVcTab, CWnd)
	//{{AFX_MSG_MAP(CVcTab)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVcTab message handlers



void CVcTab::Register()
{
	WNDCLASS wc={0};
	wc.style=CS_HREDRAW|CS_VREDRAW;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.lpfnWndProc=::DefWindowProc;
	wc.hInstance=AfxGetInstanceHandle();
	wc.hIcon=NULL;
	wc.hCursor=AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	wc.hbrBackground=::GetSysColorBrush(COLOR_BTNSHADOW);
	wc.lpszClassName=VC_TAB;
	wc.lpszMenuName=NULL;
	AfxRegisterClass(&wc);
}

/*************************************************
* BOOL CVcTab::Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID)
* ���ܣ������Զ���Ĵ���
* �����������MSDN
* ����ֵ���Ƿ񴴽��ɹ�
*************************************************/
BOOL CVcTab::Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID)
{
	static BOOL b=TRUE;
	if(b)
	{
		//ִֻ��һ��
		b=FALSE;
		Register();
	}
	CFont* pFont=pParentWnd->GetFont();
	if(!pFont)
	{
		HFONT hFont=(HFONT)::GetStockObject(DEFAULT_GUI_FONT);
		pFont=CFont::FromHandle(hFont);
	}
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	m_font.CreateFontIndirect(&lf);
	lf.lfWeight=700;
	m_fontSel.CreateFontIndirect(&lf);
	return CWnd::Create(VC_TAB,NULL,dwStyle,rect,pParentWnd,nID);
}


/*******************************************************
* BOOL CVcTab::InsertItem(int nItem, LPCTSTR szItem)
* ����:�����µı�ǩ��
* ������nItem,��ǩ�������
		szItem,��ǩ����ı�
* ����ֵ���Ƿ����ɹ�
*******************************************************/
BOOL CVcTab::InsertItem(int nItem, LPCTSTR szItem)
{
	SItem item;
	item.szText=szItem;
	item.nImage=-1;//����
	item.nWidth=GetTextWidth(szItem)+15;
	m_arr.InsertAt(nItem,item);
	return TRUE;
}


/******************************************************
* int CVcTab::GetTextWidth(CString szText)
* ���ܣ�//�������ֺ��������ÿ����
* ������Ҫ�����ȵ��ı�
* ����ֵ���ı��Ŀ��
******************************************************/
int CVcTab::GetTextWidth(CString szText)	
{
	CClientDC dc(this);
	dc.SelectObject(&m_font);
	CSize size=dc.GetTextExtent(szText);
	return size.cx;
}


/***************************************************
* BOOL CVcTab::OnEraseBkgnd(CDC* pDC)
* ���ܣ���Ϣ��Ӧ���������Ʊ���,ֱ�ӷ���TRUE,ʹ������ˢ�£���ֹ��˸
* �������豸DC
* ����ֵ���Ƿ�ˢ�³ɹ�
***************************************************/
BOOL CVcTab::OnEraseBkgnd(CDC* pDC) 
{
	//ȥ��������ͼ���Լ�����˸
	return TRUE;
}


/***************************************************
* void CVcTab::OnLButtonDown(UINT nFlags, CPoint point) 
* ����:��Ϣ��Ӧ�������ж�������Ƿ��ڱ�ǩ���ڲ���¼��ѡ�б�ǩ�������,
		ģ���򸸴��ڷ���SELCHANGE��Ϣ
* �����������MSDN
***************************************************/
void CVcTab::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(rect);
	rect.right=rect.left+DISTWIDTH;
	int i=-1,nCount=GetItemCount();
	BOOL flag=TRUE;		//������λ�ò����κα�ǩ���ڣ�=TRUE;
	while(++i<nCount)
	{
		//ѭ������ÿ����ǩ��Ŀռ�
		rect.left=rect.right-DISTWIDTH;
		rect.right+=m_arr[i].nWidth+DISTWIDTH;
		if(rect.PtInRect(point))
		{
			flag=FALSE;
			//������ĳ����ǩ�����ڣ�������Ϊѡ���ǩ
			m_nCurSel=i;
			Invalidate(FALSE);

			//ģ�ⷢ��CTabCtrl��TCN_SELCHANGE��������Ϣ
			NMHDR hdr={m_hWnd,GetDlgCtrlID(),TCN_SELCHANGE};
			GetParent()->SendMessage(WM_NOTIFY,(WPARAM)m_hWnd,(LPARAM)&hdr);
			return;
		}
	
	}

	//����ڷ�����Ϣ
	GetClientRect(&rect);
	if(flag&&rect.PtInRect(point))
	{
		GetParent()->SendMessage(WM_LBUTTONDOWN,(WPARAM)nFlags,(LPARAM)MAKELONG((WORD)point.x,(WORD)point.y));
	}
	CWnd::OnLButtonDown(nFlags, point);
}


/***************************************************
* void CVcTab::OnMouseMove(UINT nFlags, CPoint point) 
* ����:��Ϣ��Ӧ��������������ȵ����ڣ�����¼�ȵ����ڱ�ǩ�������
* �����������MSDN
***************************************************/
void CVcTab::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnMouseMove(nFlags, point);
	CRect rect;
	GetClientRect(rect);
	if(!rect.PtInRect(point))
	{
		ReleaseCapture();
		return;
	}
	if(GetCapture()-this)
		SetCapture();
	int i=-1,nCount=GetItemCount();
	rect.right=rect.left+DISTWIDTH;
	while(++i<nCount)
	{
		//ѭ������ÿ����ǩ��Ŀռ�
		rect.left=rect.right-DISTWIDTH;
		rect.right+=m_arr[i].nWidth+DISTWIDTH;
		if(rect.PtInRect(point))
		{
			//�������ĳ����ǩ�������ƶ���������Ϊ������ǩ
			if(m_nTrack!=i)
			{
				m_nTrack=i;
				Invalidate(FALSE);
			}
			return;
		}

		
	}
}


/***************************************************
* void CVcTab::OnPaint()
* ����:��Ϣ��Ӧ�����������Զ���Tab�ؼ�
***************************************************/
void CVcTab::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.SelectObject(m_font);
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(m_pen);
	dc.SetTextColor(m_clText);

	CString szText;
	CRect rect,rc;
	GetClientRect(rc);
	rect=rc;
	rect.right=rect.left+DISTWIDTH;
	int i=-1,nCount=GetItemCount(),nSel=GetCurSel();

	while(++i<nCount)
	{
		rect.left=rect.right-DISTWIDTH;
		rect.right=rect.right+m_arr[i].nWidth+DISTWIDTH;

		//��ȡ��ǩ�����ε��ĸ�������
		POINT pt[4]={
			{rect.left,rect.top},				
			{rect.left+DISTWIDTH,rect.bottom},
			{rect.right-DISTWIDTH,rect.bottom},
			{rect.right,rect.top}				
			};	

		//�����ǩ��ͼ�ε��ĸ�������
		SLader slader;
		slader.m_TopLeft=pt[0];
		slader.m_BottomLeft=pt[1];
		slader.m_BottomRight=pt[2];
		slader.m_TopRight=pt[3];
		m_lader.InsertAt(i,slader);

		szText=GetItemText(i);
		if(nSel!=i)
		{
			//����̬��������������̬
			CBrush br(i==m_nTrack?m_clTrack:m_clNormal);
			CBrush* pOldBrush=dc.SelectObject(&br);
			dc.Polygon(pt,sizeof(pt)/sizeof(pt[0]));
			dc.DrawText(szText,szText.GetLength(),rect,
				DT_SINGLELINE|DT_VCENTER|DT_CENTER);
			dc.SelectObject(pOldBrush);
			br.DeleteObject();

		}
		else
		{
			//ѡ��̬
			CBrush br(m_clSel);
			CBrush* pOldBr=dc.SelectObject(&br);
	
			CFont* pOldFont=dc.SelectObject(&m_fontSel);
			dc.Polygon(pt,sizeof(pt)/sizeof(pt[0]));
			dc.DrawText(szText,szText.GetLength(),rect,
				DT_SINGLELINE|DT_VCENTER|DT_CENTER);

			dc.SelectObject(pOldFont);
			dc.SelectObject(pOldBr);

			
			for(int j=0;j<POINT_CNT;j++)
				m_pt[j]=pt[j];
			m_rtSel=rect;
			m_szSel=szText;
		}


		rect.top=rc.top;
		rect.bottom=rc.bottom;
	}
	//������ɫ���ʣ��ؼ����ֵĿؼ�
	rect.left=rect.right;
	rect.right=rc.right;
	rect.left=rect.left;
	dc.FillSolidRect(rect,RGB(200,200,200));

	//���»���ѡ�б�ǩ�ʹ���θ������ҵ�����
	CBrush br(m_clSel);
	CBrush* pOldBr=(CBrush*)dc.SelectObject(&br);
	CFont* pOldFont=(CFont*)dc.SelectObject(&m_fontSel);
	dc.Polygon(m_pt,sizeof(m_pt)/sizeof(m_pt[0]));
	dc.DrawText(m_szSel,m_szSel.GetLength(),m_rtSel,
		DT_SINGLELINE|DT_VCENTER|DT_CENTER);

	dc.SelectObject(pOldFont);
	dc.SelectObject(pOldBr);
		
}



/***********************************************************
* void CVcTab::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
* ���ܣ�������Delete��ʱ��ɾ��ѡ�еı�ǩ��
* �����������MSDN
*************************************************************/
void CVcTab::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
		static BOOL b=TRUE;
		switch(nChar)
		{
		case VK_DELETE:
			{
				if(IDYES==AfxMessageBox(_T("ȷ��Ҫɾ��ѡ������"),MB_YESNO))
				DeleteItem(GetCurSel());
				Invalidate(FALSE);
				return;
			}
		}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CVcTab::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd::OnLButtonDblClk(nFlags, point);
}



void CVcTab::GetFreeLab(CRect& rect)
{
	int nCount=GetItemCount();
	SLader slader;
	GetLaderPoint(nCount-1,slader);

	rect.left=slader.m_TopRight.x;
	rect.top=slader.m_TopRight.y;
	rect.right=rect.left+100;
	rect.bottom=slader.m_BottomLeft.y;

}
