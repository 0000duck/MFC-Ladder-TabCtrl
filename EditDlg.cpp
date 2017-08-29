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

	//�ƶ�����ģ̬�Ի����λ�ã�ʹ����Ҫ�޸ĵı�ǩ��ı���
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
* ���ܣ�ģ̬�Ի���Ļس�����Ӧ��������ģ̬�Ի����б༭���������
		���͵��������е�m_tab�������,ʵ���޸��Զ���Tab�ؼ����ڵı�ǩ������
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
	case 0://�޸ı�ǩ��
		{
			int nItem=pParent->m_tab.GetCurSel();
			pParent->m_tab.SetItemText(nItem,str);
			pParent->m_tab.Invalidate(FALSE);
			CDialog::OnOK();
			return;
		}
	case 1://��ӱ�ǩ��
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
