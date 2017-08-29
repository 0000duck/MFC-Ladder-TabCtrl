#if !defined(AFX_VCTAB_H__A28D0B12_2607_4CDC_AB49_98C028571AB9__INCLUDED_)
#define AFX_VCTAB_H__A28D0B12_2607_4CDC_AB49_98C028571AB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VcTab.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVcTab window
#include <Afxtempl.h>

class CVcTab : public CWnd
{
// Construction
public:
	struct SItem
	{
		CString szText;	//ÿ������
		int nWidth;		//ÿ����
		int nImage;		//ÿ��ͼ������
	};
	struct SLader		//��ǩ���ε��ĸ���
	{
		POINT m_TopLeft;
		POINT m_BottomLeft;
		POINT m_BottomRight;
		POINT m_TopRight;
	};
	enum{POINT_CNT=4};			//��ǩ��״��ĸ���
	CArray<SItem,SItem> m_arr;	//��ǩ������ݼ���
	CArray<SLader,SLader> m_lader;	//��ǩ�����������
	int m_nCurSel,m_nTrack;		//ѡ��״̬�͸���״̬��������
	CFont m_font;				//��������
	CFont m_fontSel;			//ѡ�б�ǩ����
	static const CPen m_pen;	//ѡ��״̬�ı߿�
	static const COLORREF m_clNormal,m_clSel,m_clTrack;//��̬��ǩ��ı���ɫ
	static const COLORREF m_clText;		//���б�ǩ�ı�����ɫ
	POINT m_pt[POINT_CNT];				//ѡ��ı�ǩ�����ε�
	CRect m_rtSel;						//ѡ��ı�ǩ�ľ���(���ϱ�����Ϊ�ߵĴ���Σ�
	CString m_szSel;					//ѡ��ı�ǩ������
public:
	int GetTextWidth(CString szText);	//�������ֺ��������ÿ����
	void GetFreeLab(CRect& rect);		//��ȡTab�ؼ��ĵĲ�������ǩ���ʣ��ؼ�
	int GetCurSel()const
	{
		return m_nCurSel;
	}

	//��ȡ��ǩ����
	int GetItemCount()const
	{
		return m_arr.GetSize();
	}

	//��ȡ��ǩ�ı�
	CString GetItemText(int nItem)const
	{
		ASSERT(nItem<m_arr.GetSize());
		return m_arr[nItem].szText;
	}

	//���ñ�ǩ�ı�
	void SetItemText(int nItem,CString szText)
	{
		ASSERT(nItem<m_arr.GetSize()&&nItem>=0);
		m_arr[nItem].szText=szText;
	}

	//ɾ����ǩ��
	void DeleteItem(int nItem)
	{
		ASSERT(nItem < m_arr.GetSize()&&nItem>=0);
		m_arr.RemoveAt(nItem);
	}

	//��ȡ��ǩ������ε�����
	void GetLaderPoint(int nItem,SLader& slader)
	{
		ASSERT(nItem<m_lader.GetSize()&&nItem>=0);
		slader=m_lader[nItem];
	}

	BOOL InsertItem(int nItem,LPCTSTR szItem);
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void Register();
public:
	CVcTab();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVcTab)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CVcTab();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVcTab)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCTAB_H__A28D0B12_2607_4CDC_AB49_98C028571AB9__INCLUDED_)
