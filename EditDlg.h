#if !defined(AFX_EDITDLG_H__C5ADE51C_9D91_4BF4_B8A0_038ED963846D__INCLUDED_)
#define AFX_EDITDLG_H__C5ADE51C_9D91_4BF4_B8A0_038ED963846D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditDlg dialog

class CEditDlg : public CDialog
{
// Construction
public:
	CString m_str;		//�Զ����ǩ�ؼ���ǩ���ı�
	CRect m_rtDlg;		//�Զ����ǩ���ڴ�С
	BOOL m_bType;		//�����öԻ�������ӱ�ǩ����޸ı�ǩ��
public:
	CEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditDlg)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDLG_H__C5ADE51C_9D91_4BF4_B8A0_038ED963846D__INCLUDED_)
