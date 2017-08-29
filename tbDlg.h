// tbDlg.h : header file
//

#if !defined(AFX_TBDLG_H__7F6ED09C_2DFA_43ED_8CEE_31E233208AA0__INCLUDED_)
#define AFX_TBDLG_H__7F6ED09C_2DFA_43ED_8CEE_31E233208AA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTbDlg dialog
#include "VcTab.h"
class CTbDlg : public CDialog
{
// Construction
public:
	enum{IDC_TAB=1234};			//控件ID
	CVcTab m_tab;				//控件类对象

public:
	//用于作为TCN_SELCHANGE的消息反射函数
	void OnSelChangeTab(NMHDR* pNMHDR,LRESULT* pResult);
	CTbDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTbDlg)
	enum { IDD = IDD_TB_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTbDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTbDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TBDLG_H__7F6ED09C_2DFA_43ED_8CEE_31E233208AA0__INCLUDED_)
