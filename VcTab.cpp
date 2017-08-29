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

#define VC_TAB _T("__VC_TAB__")			//自定义窗口类名
#define DISTWIDTH	10					//标签梯形的上边和下边差的1/2
#define IDC_NEWLAB		2010			//修改标签项文本时创建的编辑框控件ID

const COLORREF CVcTab::m_clNormal
=GetSysColor(COLOR_BTNFACE),
CVcTab::m_clSel=GetSysColor(COLOR_WINDOW),
CVcTab::m_clTrack=GetSysColor(COLOR_GRADIENTINACTIVECAPTION),
CVcTab::m_clText=RGB(0,0,0);
const CPen CVcTab::m_pen(0,1,RGB(0,0,0));		//标签边框画笔

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
* 功能：创建自定义的窗口
* 参数：请参阅MSDN
* 返回值：是否创建成功
*************************************************/
BOOL CVcTab::Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID)
{
	static BOOL b=TRUE;
	if(b)
	{
		//只执行一次
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
* 功能:插入新的标签项
* 参数：nItem,标签项的索引
		szItem,标签项的文本
* 返回值：是否插入成功
*******************************************************/
BOOL CVcTab::InsertItem(int nItem, LPCTSTR szItem)
{
	SItem item;
	item.szText=szItem;
	item.nImage=-1;//保留
	item.nWidth=GetTextWidth(szItem)+15;
	m_arr.InsertAt(nItem,item);
	return TRUE;
}


/******************************************************
* int CVcTab::GetTextWidth(CString szText)
* 功能：//根据文字和字体计算每项宽度
* 参数：要计算宽度的文本
* 返回值：文本的宽度
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
* 功能：消息相应函数，绘制背景,直接返回TRUE,使背景不刷新，防止闪烁
* 参数：设备DC
* 返回值：是否刷新成功
***************************************************/
BOOL CVcTab::OnEraseBkgnd(CDC* pDC) 
{
	//去除背景绘图可以减少闪烁
	return TRUE;
}


/***************************************************
* void CVcTab::OnLButtonDown(UINT nFlags, CPoint point) 
* 功能:消息相应函数，判断鼠标点击是否在标签项内并记录被选中标签项的索引,
		模拟向父窗口发送SELCHANGE消息
* 参数：请参阅MSDN
***************************************************/
void CVcTab::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(rect);
	rect.right=rect.left+DISTWIDTH;
	int i=-1,nCount=GetItemCount();
	BOOL flag=TRUE;		//如果点击位置不再任何标签项内，=TRUE;
	while(++i<nCount)
	{
		//循环测试每个标签项的空间
		rect.left=rect.right-DISTWIDTH;
		rect.right+=m_arr[i].nWidth+DISTWIDTH;
		if(rect.PtInRect(point))
		{
			flag=FALSE;
			//若单击某个标签区域内，则设置为选择标签
			m_nCurSel=i;
			Invalidate(FALSE);

			//模拟发送CTabCtrl的TCN_SELCHANGE反射型消息
			NMHDR hdr={m_hWnd,GetDlgCtrlID(),TCN_SELCHANGE};
			GetParent()->SendMessage(WM_NOTIFY,(WPARAM)m_hWnd,(LPARAM)&hdr);
			return;
		}
	
	}

	//项父窗口发送消息
	GetClientRect(&rect);
	if(flag&&rect.PtInRect(point))
	{
		GetParent()->SendMessage(WM_LBUTTONDOWN,(WPARAM)nFlags,(LPARAM)MAKELONG((WORD)point.x,(WORD)point.y));
	}
	CWnd::OnLButtonDown(nFlags, point);
}


/***************************************************
* void CVcTab::OnMouseMove(UINT nFlags, CPoint point) 
* 功能:消息相应函数，检索鼠标热点所在，并记录热点所在标签项的索引
* 参数：请参阅MSDN
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
		//循环测试每个标签项的空间
		rect.left=rect.right-DISTWIDTH;
		rect.right+=m_arr[i].nWidth+DISTWIDTH;
		if(rect.PtInRect(point))
		{
			//若光标在某个标签区域内移动，则设置为加量标签
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
* 功能:消息相应函数，绘制自定义Tab控件
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

		//获取标签项梯形的四个点坐标
		POINT pt[4]={
			{rect.left,rect.top},				
			{rect.left+DISTWIDTH,rect.bottom},
			{rect.right-DISTWIDTH,rect.bottom},
			{rect.right,rect.top}				
			};	

		//保存标签项图形的四个点坐标
		SLader slader;
		slader.m_TopLeft=pt[0];
		slader.m_BottomLeft=pt[1];
		slader.m_BottomRight=pt[2];
		slader.m_TopRight=pt[3];
		m_lader.InsertAt(i,slader);

		szText=GetItemText(i);
		if(nSel!=i)
		{
			//跟踪态（加量）和正常态
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
			//选择态
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
	//用正常色填充剩余控件部分的控件
	rect.left=rect.right;
	rect.right=rc.right;
	rect.left=rect.left;
	dc.FillSolidRect(rect,RGB(200,200,200));

	//重新绘制选中标签项，使梯形覆盖左右的梯形
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
* 功能：当按下Delete键时，删除选中的标签项
* 参数：请参阅MSDN
*************************************************************/
void CVcTab::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
		static BOOL b=TRUE;
		switch(nChar)
		{
		case VK_DELETE:
			{
				if(IDYES==AfxMessageBox(_T("确定要删除选中项吗"),MB_YESNO))
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
