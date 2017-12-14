
// Dijkstra_Prim_MixtureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Dijkstra_Prim_Mixture.h"
#include "Dijkstra_Prim_MixtureDlg.h"
#include "afxdialogex.h"
#include "PlotView.h"
#include <math.h>
#include "PtInfo.h"
#include <limits>
#include "Functions.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDijkstra_Prim_MixtureDlg dialog



CDijkstra_Prim_MixtureDlg::CDijkstra_Prim_MixtureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIJKSTRA_PRIM_MIXTURE_DIALOG, pParent)
	, m_intWeight(0)
	, m_numPts(2)
	, m_calculated(false)
	, m_pPlotView(nullptr)
	, m_radius(0)
	, m_center(0)
	, m_LinkedPts(nullptr)
	, m_totalCost(0)
	, m_maxLatency(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Points.clear();
}

void CDijkstra_Prim_MixtureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLIDER1, m_intWeight);
	DDV_MinMaxInt(pDX, m_intWeight, 0, 100);
	DDX_Text(pDX, IDC_PTNUM, m_numPts);
	DDV_MinMaxInt(pDX, m_numPts, 2, 60);
}

BEGIN_MESSAGE_MAP(CDijkstra_Prim_MixtureDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ABOUT, &CDijkstra_Prim_MixtureDlg::OnBnClickedAbout)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CDijkstra_Prim_MixtureDlg::OnNMReleasedcaptureSlider1)
	ON_EN_KILLFOCUS(IDC_PTNUM, &CDijkstra_Prim_MixtureDlg::OnEnKillfocusPtnum)
	ON_BN_CLICKED(IDC_DATA, &CDijkstra_Prim_MixtureDlg::OnBnClickedData)
	ON_BN_CLICKED(IDC_CALCULATE, &CDijkstra_Prim_MixtureDlg::OnBnClickedCalculate)
//	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER1, &CDijkstra_Prim_MixtureDlg::OnTRBNThumbPosChangingSlider1)
END_MESSAGE_MAP()


// CDijkstra_Prim_MixtureDlg message handlers

BOOL CDijkstra_Prim_MixtureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	UpdateData(false);

	CRect rect;
	GetDlgItem(IDC_PLOTFRM)->GetWindowRect(&rect);
	m_pPlotView = new PlotView();
	ScreenToClient(&rect);
	m_pPlotView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, this, 9999);
	m_radius = rect.Height() / 2;
	if (rect.Width() < rect.Height())
	{
		m_radius = rect.Width() / 2;
	}
	m_radius =(int)( 0.85*m_radius);
	m_center = rect.CenterPoint();
	InitializePoints();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDijkstra_Prim_MixtureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDijkstra_Prim_MixtureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDijkstra_Prim_MixtureDlg::OnBnClickedAbout()
{
	// TODO: Add your control notification handler code here
	MessageBox("Developped by Shiliang Ma from UVa!", "About...", MB_OK);
}



void CDijkstra_Prim_MixtureDlg::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	UpdateData();
	InitializePoints();
	CalculateResult();
}





void CDijkstra_Prim_MixtureDlg::OnEnKillfocusPtnum()
{
	// TODO: Add your control notification handler code here
	int oldnum = m_numPts;
	UpdateData();
	if (m_numPts != oldnum)
	{
		InitializePoints();
		m_calculated = false;
	}
}


void CDijkstra_Prim_MixtureDlg::OnBnClickedData()
{
	// TODO: Add your control notification handler code here
//	MessageBox("Data Initialization Finished");
	Invalidate();
}


void CDijkstra_Prim_MixtureDlg::InitializePoints()
{
	m_Points.clear();
	if (m_LinkedPts != nullptr)
	{
		delete[]m_LinkedPts;
		m_LinkedPts = nullptr;
	}
	m_Points.push_back(m_center);
	double delta = 2 * 3.1415926 / m_numPts;
	CPoint temp;
	for (int i = 0; i < m_numPts; i++)
	{
		temp.x = m_center.x + static_cast<int>(m_radius*cos(delta*i));
		temp.y = m_center.y + static_cast<int>(m_radius*sin(delta*i));
		m_Points.push_back(temp);

	}
	int sz = m_Points.size();
	m_LinkedPts = new PtInfo[sz];
	for (int i = 0; i < sz; i++)
	{
		m_LinkedPts[i].PointID = i;
		m_LinkedPts[i].PrevPointID = NOTCONNECTED;
		m_LinkedPts[i].TotalDistanceToSource = INT_MAX;
	}
	m_LinkedPts[0].PrevPointID = 0;
	m_LinkedPts[0].TotalDistanceToSource = 0;
}

void CDijkstra_Prim_MixtureDlg::CalculateResult()
{
	int sz = m_Points.size();
	int index_in, index_out;
	int LeastDistance;
	int currentDistance;
	int medRes;
	m_totalCost = 0;
	m_maxLatency = 0;
	for (int iteration = 1; iteration < sz; iteration++)
	{
		LeastDistance = INT_MAX;
		for (int in = 0; in < sz; in++)
		{
			if (m_LinkedPts[in].PrevPointID != NOTCONNECTED)
			{
				for (int out = 0; out < sz; out++)
				{
					if (m_LinkedPts[out].PrevPointID == NOTCONNECTED)
					{
						medRes = CalcDistance(m_Points[in], m_Points[out]);
						currentDistance = (100-m_intWeight)*medRes + m_intWeight*(m_LinkedPts[in].TotalDistanceToSource + medRes);
						if (currentDistance <= LeastDistance)
						{
							LeastDistance = currentDistance;
							index_in = in;
							index_out = out;
						}
					}
				}
			}
		}
		m_LinkedPts[index_out].PrevPointID = index_in;
		medRes = CalcDistance(m_Points[index_in], m_Points[index_out]);
		m_LinkedPts[index_out].TotalDistanceToSource = m_LinkedPts[index_in].TotalDistanceToSource + medRes;
		m_totalCost += medRes;
		if (m_LinkedPts[index_out].TotalDistanceToSource > m_maxLatency)
			m_maxLatency = m_LinkedPts[index_out].TotalDistanceToSource;
	}
	m_calculated = true;
	Invalidate();
}


void CDijkstra_Prim_MixtureDlg::OnBnClickedCalculate()
{
	// TODO: Add your control notification handler code here
	if(m_calculated==false)
		CalculateResult();
}


//void CDijkstra_Prim_MixtureDlg::OnTRBNThumbPosChangingSlider1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// This feature requires Windows Vista or greater.
//	// The symbol _WIN32_WINNT must be >= 0x0600.
//	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//	int oldnum = m_numPts;
//	UpdateData();
//	if (m_numPts != oldnum)
//	{
//		InitializePoints();
//		m_calculated = false;
//	}
//}
