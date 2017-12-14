
// ConvexHullDlg.h : header file
//

#pragma once
#include <vector>
#include <list>
#include "afxwin.h"
class CPlotView;
// CConvexHullDlg dialog
class CConvexHullDlg : public CDialogEx
{
	// Construction
public:
	CConvexHullDlg(CWnd* pParent = NULL);	// standard constructor
	void CalculateConvexHullMarch();
	void CalculateConvexHullScan();
	void CalculateConvexHullMerge();
	std::vector<CPoint> CalculateConvexHullQuick();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONVEXHULL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL m_AddPointChecked;
	CPlotView* m_pPlot;
	afx_msg void OnBnClickedAddpoint();
	std::vector<CPoint> m_Points;

	std::vector<CPoint> m_HullPts;
	afx_msg void OnClickedNext();
	bool m_CalcFinished;
	int m_iteration;

	CButton m_btnNext;
	CButton m_btnShowAll;
	afx_msg void OnClickedStartover();
	afx_msg void OnClickedShowall();
	BOOL m_KeepPointsChecked;
	afx_msg void OnClickedKeeppoints();
	CComboBox m_Method;

	afx_msg void OnCbnSelchangeMethod();
	int m_intMethod;
	bool m_GScanFixed;
	bool GrahamScanFixUp();
	void GrahamScanSort();
	void GrahamScanNextPoint();

	std::list<std::vector<CPoint>> m_MergeInterMediate;

	afx_msg void OnBnClickedAbout();
};
