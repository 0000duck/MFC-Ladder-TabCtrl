// tbDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tb.h"
#include "tbDlg.h"
#include "EditDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTbDlg dialog

CTbDlg::CTbDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTbDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTbDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTbDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTbDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE,IDC_TAB,OnSelChangeTab)
	//{{AFX_MSG_MAP(CTbDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTbDlg message handlers

BOOL CTbDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_tab.Create(WS_VISIBLE,CRect(0,0,500,30),this,IDC_TAB);
	m_tab.InsertItem(0,_T("Build"));
	m_tab.InsertItem(1,_T("Debug"));
	m_tab.InsertItem(2,_T("Find in Files1"));
	m_tab.InsertItem(3,_T("Find in Files2"));

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTbDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTbDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


/***********************************************************************
* void CTbDlg::OnSelChangeTab(NMHDR *pNMHDR, LRESULT *pResult)
* 功能：接收自定义Tab子窗口在OnLButtonDown（）中发来的消息，根据选中的标签项
		设置对话框标题
* 参数：请参数MSDN
***********************************************************************/
void CTbDlg::OnSelChangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nSel=m_tab.GetCurSel();
	CString str;
	str.Format("第%d页",nSel+1);
	str+=m_tab.GetItemText(nSel);
	SetWindowText(str);
	*pResult=0;
}


/***********************************************
* void CTbDlg::OnOK()
* 功能:主窗口按回车键的消息响应函数，弹出模态对话框,焦点随着自定义Tab窗口上，
		但按回车键仍然是响应主窗口的的OnOk()函数
		而没有响应自定义CVcTab Tab类里的WM_KEYDOWN消息，即没有调用m_tab.OnKeyDown()函数
		如果是按其他键（ESC除外），则会响应焦点所在窗口的WM_KeyDown消息，即会调用m_tab.OnKeyDown()函数
**********************************************/
void CTbDlg::OnOK() 
{
	// TODO: Add extra validation here
	CEditDlg dlg;
	CRect rc=m_tab.m_rtSel;
	ClientToScreen(&rc);
	dlg.m_bType=0;
	dlg.m_rtDlg=rc;
	dlg.DoModal();
//	CDialog::OnOK();
}


/*****************************************
* void CTbDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
* 功能：因为焦点在自定义的Tab窗口上面，而不是在主窗口上面，所以主窗口的不会收到WM_KEYDOWN消息，
		所以这个函数不会被调用
*****************************************/
void CTbDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}


/*************************************************************
void CTbDlg::OnLButtonDown(UINT nFlags, CPoint point) 
* 功能：接收自定义Tab子窗口在OnLButtonDown（）函数里发来的鼠标左键按下的消息
		弹出对话框让使用者输入新标签项的文本，按回车键结束
* 参数：请参阅MSDN
************************************************************/
void CTbDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	AfxMessageBox("Test");
	CVcTab* pWnd=(CVcTab*)GetDlgItem(IDC_TAB);
	CRect rect,rc;
	pWnd->GetClientRect(&rect);
	if(rect.PtInRect(point))
	{
		CEditDlg dlg;
		dlg.m_bType=1;
		m_tab.GetFreeLab(rc);
		
		m_tab.GetClientRect(&rect);
		if(rc.left>=rect.right)
			return;
		ClientToScreen(&rc);
		dlg.m_rtDlg=rc;
		dlg.DoModal();
	}
	CDialog::OnLButtonDown(nFlags, point);
}
