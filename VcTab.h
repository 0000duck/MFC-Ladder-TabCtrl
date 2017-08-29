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
		CString szText;	//每项文字
		int nWidth;		//每项宽度
		int nImage;		//每项图像索引
	};
	struct SLader		//标签梯形的四个点
	{
		POINT m_TopLeft;
		POINT m_BottomLeft;
		POINT m_BottomRight;
		POINT m_TopRight;
	};
	enum{POINT_CNT=4};			//标签形状点的个数
	CArray<SItem,SItem> m_arr;	//标签项的数据集合
	CArray<SLader,SLader> m_lader;	//标签项的梯形坐标
	int m_nCurSel,m_nTrack;		//选择状态和跟踪状态的项索引
	CFont m_font;				//文字字体
	CFont m_fontSel;			//选中标签字体
	static const CPen m_pen;	//选择状态的边框
	static const COLORREF m_clNormal,m_clSel,m_clTrack;//三态标签项的背景色
	static const COLORREF m_clText;		//所有标签文本的颜色
	POINT m_pt[POINT_CNT];				//选择的标签的梯形点
	CRect m_rtSel;						//选择的标签的矩形(以上边两点为边的大矩形）
	CString m_szSel;					//选择的标签的文字
public:
	int GetTextWidth(CString szText);	//根据文字和字体计算每项宽度
	void GetFreeLab(CRect& rect);		//获取Tab控件的的不包含标签项的剩余控件
	int GetCurSel()const
	{
		return m_nCurSel;
	}

	//获取标签总数
	int GetItemCount()const
	{
		return m_arr.GetSize();
	}

	//获取标签文本
	CString GetItemText(int nItem)const
	{
		ASSERT(nItem<m_arr.GetSize());
		return m_arr[nItem].szText;
	}

	//设置标签文本
	void SetItemText(int nItem,CString szText)
	{
		ASSERT(nItem<m_arr.GetSize()&&nItem>=0);
		m_arr[nItem].szText=szText;
	}

	//删除标签项
	void DeleteItem(int nItem)
	{
		ASSERT(nItem < m_arr.GetSize()&&nItem>=0);
		m_arr.RemoveAt(nItem);
	}

	//获取标签项的梯形点坐标
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
