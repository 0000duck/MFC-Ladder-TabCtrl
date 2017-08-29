// EditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tb.h"
#include "EditDlg.h"

#include "TbDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog


CEditDlg::CEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDlg::IDD, pParent)
{
	m_bType=0;
	//{{AFX_DATA_INIT(CEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialog)
	//{{AFX_MSG_MAP(CEditDlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDlg message handlers

BOOL CEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//移动弹出模态对话框的位置，使其在要修改的标签项的表面
	this->MoveWindow(m_rtDlg);
	return TRUE;  
}

void CEditDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

/*************************************************************
* void CEditDlg::OnOK()
* 功能：模态对话框的回车键响应函数，将模态对话框中编辑框里的内容
		传送到父窗口中的m_tab类变量中,实现修改自定义Tab控件窗口的标签项内容
**************************************************************/
void CEditDlg::OnOK() 
{
	// TODO: Add extra validation here
	CTbDlg* pParent=(CTbDlg*)GetParent();
	CString str;
	this->GetDlgItemText(IDC_EDIT,str);
	if(str.IsEmpty())
	{
		CDialog::OnOK();
		return;
	}
	switch(m_bType)
	{
	case 0://修改标签项
		{
			int nItem=pParent->m_tab.GetCurSel();
			pParent->m_tab.SetItemText(nItem,str);
			pParent->m_tab.Invalidate(FALSE);
			CDialog::OnOK();
			return;
		}
	case 1://添加标签项
		{
			int nCount=pParent->m_tab.GetItemCount();
			pParent->m_tab.InsertItem(nCount,str);
			pParent->m_tab.Invalidate(FALSE);
			CDialog::OnOK();
			return;
		}
	default:
		{
			CDialog::OnOK();
			return;
		}
	}
}
