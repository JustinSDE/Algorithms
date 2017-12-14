
// Dijkstra_Prim_MixtureDlg.h : header file
//

#pragma once
#include "atltypes.h"
#include <vector>
using namespace std;
class PlotView;
class PtInfo;

// CDijkstra_Prim_MixtureDlg dialog
class CDijkstra_Prim_MixtureDlg : public CDialogEx
{
// Construction
public:
	CDijkstra_Prim_MixtureDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIJKSTRA_PRIM_MIXTURE_DIALOG };
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
public:  //methods
	void InitializePoints();
public:
	int m_intWeight;
	int m_numPts;
	afx_msg void OnBnClickedAbout();
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnEnKillfocusPtnum();
	bool m_calculated;
	int m_radius;
	CPoint m_center;
	PlotView* m_pPlotView;
	afx_msg void OnBnClickedData();
	vector<CPoint> m_Points;
	PtInfo* m_LinkedPts;

	void CalculateResult();
	afx_msg void OnBnClickedCalculate();
//	afx_msg void OnTRBNThumbPosChangingSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_totalCost;
	int m_maxLatency;
};
