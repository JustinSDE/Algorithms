
// ConvexHullDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConvexHull.h"
#include "ConvexHullDlg.h"
#include "afxdialogex.h"
#include "Functions.h"
#include <vector>
#include <list>
#include "PlotView.h"
#include "LineSeg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConvexHullDlg dialog



CConvexHullDlg::CConvexHullDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONVEXHULL_DIALOG, pParent)
	, m_pPlot(NULL)
	, m_AddPointChecked(FALSE)
	, m_CalcFinished(false)
	, m_iteration(0)
	, m_KeepPointsChecked(FALSE)
	, m_intMethod(0)
	, m_GScanFixed(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Points.clear();
	m_HullPts.clear();
	m_MergeInterMediate.clear();
}

void CConvexHullDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_ADDPOINT, m_AddPointChecked);
	DDX_Control(pDX, IDC_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_SHOWALL, m_btnShowAll);
	DDX_Check(pDX, IDC_KEEPPOINTS, m_KeepPointsChecked);
	DDX_Control(pDX, IDC_METHOD, m_Method);
	//  DDX_CBString(pDX, IDC_METHOD, m_strMethod);
	DDX_CBIndex(pDX, IDC_METHOD, m_intMethod);
}

BEGIN_MESSAGE_MAP(CConvexHullDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADDPOINT, &CConvexHullDlg::OnBnClickedAddpoint)
	ON_BN_CLICKED(IDC_NEXT, &CConvexHullDlg::OnClickedNext)
	ON_BN_CLICKED(IDC_STARTOVER, &CConvexHullDlg::OnClickedStartover)
	ON_BN_CLICKED(IDC_SHOWALL, &CConvexHullDlg::OnClickedShowall)
	ON_BN_CLICKED(IDC_KEEPPOINTS, &CConvexHullDlg::OnClickedKeeppoints)
	ON_CBN_SELCHANGE(IDC_METHOD, &CConvexHullDlg::OnCbnSelchangeMethod)
	ON_BN_CLICKED(IDC_ABOUT, &CConvexHullDlg::OnBnClickedAbout)
END_MESSAGE_MAP()


// CConvexHullDlg message handlers

BOOL CConvexHullDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rect;
	m_pPlot = new CPlotView();
	GetDlgItem(IDC_REGION)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_pPlot->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, this, 9999);
	m_pPlot->ShowWindow(SW_SHOW);

	m_Method.InsertString(0, "Jarvis March");
	m_Method.InsertString(1, "Graham Scan");
	m_Method.InsertString(2, "MergeHull");
	m_Method.InsertString(3, "QuickHull");
	m_Method.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CConvexHullDlg::OnPaint()
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
HCURSOR CConvexHullDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CConvexHullDlg::CalculateConvexHullMarch()
{
	int sz = m_Points.size();
	if (true == m_CalcFinished)
	{
		return;
	}

	m_iteration++;
	if (1 == m_iteration)
	{
		int x_min = m_Points[0].x, index = 0;
		for (int i = 0; i < sz; i++)
		{
			if (x_min > m_Points[i].x)
			{
				x_min = m_Points[i].x;
				index = i;
			}
		}
		CPoint pt = m_Points[index];
		m_HullPts.push_back(pt);
	}
	else if (2 == m_iteration)
	{
		CPoint pt = m_HullPts[0];
		double slope_max = -3000.0, slope;
		int index = 0;
		for (int i = 0; i < sz; i++)
		{
			if (pt != m_Points[i])
			{
				if (m_Points[i].x == pt.x)
				{
					index = i;
					break;
				}
				slope = -1.0*(m_Points[i].y - pt.y) / (m_Points[i].x - pt.x);
				if (slope > slope_max)
				{
					index = i;
					slope_max = slope;
				}
			}
		}
		pt = m_Points[index];
		m_HullPts.push_back(pt);
	}
	else
	{
		CPoint pt1 = m_HullPts[m_iteration - 3], pt2 = m_HullPts[m_iteration - 2], pt3;
		double angle_max = -10.0, angle_current;
		int index = 0;
		for (int i = 0; i < sz; i++)
		{
			pt3 = m_Points[i];
			if (pt3 != pt1&&pt3 != pt2)
			{
				angle_current = Angle(pt1, pt2, pt3);
				if (angle_current > angle_max)
				{
					angle_max = angle_current;
					index = i;
				}
			}
		}
		pt3 = m_Points[index];
		m_HullPts.push_back(pt3);
	}
	if (m_iteration > 2 && m_HullPts[m_iteration - 1] == m_HullPts[0])
	{
		m_CalcFinished = true;
		m_btnNext.EnableWindow(false);
		m_btnShowAll.EnableWindow(false);
	}
}

void CConvexHullDlg::OnBnClickedAddpoint()
{
	// TODO: Add your control notification handler code here
	UpdateData();
}


void CConvexHullDlg::OnClickedNext()
{
	// TODO: Add your control notification handler code here
	if (m_Points.size() < 3)
	{
		MessageBox("Please add more points", "Warning!",MB_OK);
		return;
	}
	else
	{
		switch (m_intMethod)
		{
		case 0:    //Javis March
			CalculateConvexHullMarch();
			Invalidate();
			break;
		case 1:    //Graham Scan
			CalculateConvexHullScan();
			Invalidate();
			break;
		case 2:
			CalculateConvexHullMerge();
			Invalidate();
			break;
		case 3:
			m_HullPts = CalculateConvexHullQuick();
			Invalidate();
			break;
		default:
			return;
		}
	}
}


void CConvexHullDlg::OnClickedStartover()
{
	// TODO: Add your control notification handler code here
	m_CalcFinished = false;
	m_btnNext.EnableWindow(true);
	m_btnShowAll.EnableWindow(true);
	m_HullPts.clear();
	m_iteration = 0;
	m_MergeInterMediate.clear();
	if (false == m_KeepPointsChecked)
		m_Points.clear();
	Invalidate();
}


void CConvexHullDlg::OnClickedShowall()
{
	// TODO: Add your control notification handler code here
	if (m_Points.size() < 3)
	{
		MessageBox("Please add more points", "Warning!",MB_OK);
		return;
	}

	switch (m_intMethod)
	{
	case 0:
		while (m_CalcFinished != true)
			CalculateConvexHullMarch();
		Invalidate();
		break;
	case 1:
		while (m_CalcFinished != true)
			CalculateConvexHullScan();
		Invalidate();
		break;
	case 2:
		while (m_CalcFinished != true)
			CalculateConvexHullMerge();
		Invalidate();
		break;
	case 3:
		while (m_CalcFinished != true)
			m_HullPts = CalculateConvexHullQuick();
		Invalidate();
		break;
	default:
		return;
	}

}


void CConvexHullDlg::OnClickedKeeppoints()
{
	// TODO: Add your control notification handler code here
	UpdateData();
}


void CConvexHullDlg::OnCbnSelchangeMethod()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	BOOL temp = m_KeepPointsChecked;
	m_KeepPointsChecked = TRUE;
	OnClickedStartover();
	m_KeepPointsChecked = temp;
}

bool CConvexHullDlg::GrahamScanFixUp()
{
	//TODO: Enter FixUp Code Here This function fixes all the sharpe angles

	int sz = m_HullPts.size();
	if (sz < 3)
	{
		return true;
	}
	CPoint p1 = m_HullPts[sz - 3], p2 = m_HullPts[sz - 2], p3 = m_HullPts[sz - 1];
	int angle = crossproduct(p1, p2, p3);
	if (angle > 0)
		return true;
	else if (angle < 0)
	{
		m_HullPts.pop_back();
		m_HullPts.pop_back();
		m_HullPts.push_back(p3);
		return false;
	}
	else
	{
		if (dotproduct(p1, p2, p3) < 0)
		{
			m_HullPts[sz - 2] = p3;
			m_HullPts[sz - 1] = p2;
			return false;
		}
		return true;
	}

	return true;
}

void CConvexHullDlg::GrahamScanSort()
{

	int sz = m_Points.size(), index = 0;
	CPoint leftbottom = m_Points[0];
	//Put the leftmost point to the first place of the array;
	for (int i = 1; i < sz; i++)
	{
		if (m_Points[i].x < leftbottom.x || (m_Points[i].x == leftbottom.x && m_Points[i].y > leftbottom.y))
		{
			index = i;
			leftbottom = m_Points[i];
		}
	}
	m_Points[index] = m_Points[0];
	m_Points[0] = leftbottom;
	vector<double> Slopes;
	Slopes.push_back(-100.0);   //take the first postion;

	for (int i = 1; i < sz; i++)
	{
		Slopes.push_back(1.0*(m_Points[i].y - leftbottom.y) / (m_Points[i].x - leftbottom.x));
	}

	QuickSort(m_Points, Slopes, 1, sz - 1);
}

void CConvexHullDlg::GrahamScanNextPoint()
{
	m_HullPts.push_back(m_Points[m_iteration]);
	m_iteration++;
}

void CConvexHullDlg::CalculateConvexHullScan()
{
	if (m_iteration == 0)
		GrahamScanSort();
	m_GScanFixed = GrahamScanFixUp();
	if (false == m_GScanFixed)
	{
		return;
	}
	else if (m_iteration != m_Points.size())
		GrahamScanNextPoint();
	else
	{
		m_CalcFinished = true;
		m_HullPts.push_back(m_Points[0]);
		m_btnNext.EnableWindow(false);
		m_btnShowAll.EnableWindow(false);
	}
}

void CConvexHullDlg::CalculateConvexHullMerge()
{
	if (m_iteration == 0)
	{
		vector<CPoint> temp;
		int sz = m_Points.size();
		for (int i = 0; i < sz; i++)
		{
			temp.push_back(m_Points[i]);
			if (i % 2 == 1)
			{
				if (temp[1].x < temp[0].x || (temp[1].x == temp[0].x && temp[0].y > temp[1].y))
					Swap(temp[0], temp[1]);
				m_MergeInterMediate.push_back(temp);
				temp.clear();
			}
		}
		if (temp.empty() != true)
		{
			m_MergeInterMediate.push_back(temp);
		}
	}
	else if (m_MergeInterMediate.size() > 1)
	{
		vector<CPoint> temp1, temp2;
		temp1 = m_MergeInterMediate.front();
		m_MergeInterMediate.pop_front();
		temp2 = m_MergeInterMediate.front();
		m_MergeInterMediate.pop_front();
		vector<CPoint> temp3 = MergeVectors(temp1, temp2);
		vector<CPoint> temp4 = MergeFixUp(temp3);
		m_MergeInterMediate.push_back(temp4);
	}
	else
	{
		m_HullPts = m_MergeInterMediate.front();
		m_HullPts.push_back(m_HullPts[0]);
		m_CalcFinished = true;
		m_btnNext.EnableWindow(false);
		m_btnShowAll.EnableWindow(false);
	}
	m_iteration++;
}

std::vector<CPoint> CConvexHullDlg::CalculateConvexHullQuick()
{
	static list<LineSeg> ln_list;
	static list<vector<CPoint>> pts_list;
	if (m_iteration == 0)
	{
		ln_list.clear();
		pts_list.clear();

		int sz_Pts = m_Points.size();
		CPoint left, right;
		left = right = m_Points[0];
		int index_left = 0, index_right = 0;

		for (int i = 1; i < sz_Pts; i++)
		{
			if (m_Points[i].x < left.x)
			{
				index_left = i;
				left = m_Points[i];
			}
			else if (m_Points[i].x > right.x)
			{
				index_right = i;
				right = m_Points[i];
			}
		}

		LineSeg l1(left, right), l2(right, left);
		ln_list.push_back(l1);
		ln_list.push_back(l2);

		vector<CPoint> v_points1, v_points2;
		int cp;
		for (int i = 0; i < sz_Pts; i++)
		{
			cp = crossproduct(left, m_Points[i], right);
			if (cp > 0)
				v_points1.push_back(m_Points[i]);
			else if (cp < 0)
				v_points2.push_back(m_Points[i]);
		}

		pts_list.push_back(v_points1);
		pts_list.push_back(v_points2);
	}
	else
	{
		list<vector<CPoint>>::iterator it_pt = pts_list.begin();
		list<LineSeg>::iterator it_ln = ln_list.begin();
		while (it_pt != pts_list.end() && (*it_pt).empty())
		{
			it_pt++;
			it_ln++;
		}
		if (it_pt == pts_list.end())
		{
			m_CalcFinished = true;
			m_btnNext.EnableWindow(false);
			m_btnShowAll.EnableWindow(false);
		}
		else
		{
			vector<CPoint> pt_current, pt_sub1, pt_sub2;
			pt_current = *it_pt;
			LineSeg ln_current, ln_sub1, ln_sub2;
			ln_current = *it_ln;
			int maxArea = -10, curArea;
			int sz_pt_current = pt_current.size();
			CPoint maxPoint;
			for (int i = 0; i < sz_pt_current; i++)
			{
				curArea = crossproduct(ln_current.start, pt_current[i], ln_current.end);
				if (curArea > maxArea)
				{
					maxPoint = pt_current[i];
					maxArea = curArea;
				}
			}
			ln_sub1.SetValue(ln_current.start, maxPoint);
			ln_sub2.SetValue(maxPoint, ln_current.end);

			for (int i = 0; i < sz_pt_current; i++)
			{
				if (crossproduct(ln_sub1.start, pt_current[i], ln_sub1.end) > 0)
					pt_sub1.push_back(pt_current[i]);
				else if (crossproduct(ln_sub2.start, pt_current[i], ln_sub2.end) > 0)
					pt_sub2.push_back(pt_current[i]);
			}

			pts_list.insert(it_pt, pt_sub1);
			pts_list.insert(it_pt, pt_sub2);
			it_pt = pts_list.erase(it_pt);

			ln_list.insert(it_ln, ln_sub1);
			ln_list.insert(it_ln, ln_sub2);
			it_ln = ln_list.erase(it_ln);
		}
	}

	m_iteration++;
	vector<CPoint> res;
	list<LineSeg>::iterator it_ln = ln_list.begin();
	LineSeg temp;
	for (; it_ln != ln_list.end(); it_ln++)
	{
		temp = *it_ln;
		res.push_back(temp.start);
	}
	temp = *(ln_list.begin());
	res.push_back(temp.start);
	return res;
}


void CConvexHullDlg::OnBnClickedAbout()
{
	// TODO: Add your control notification handler code here
	MessageBox("Developped by Shiliang Ma from University of Virginia\n", "About...",MB_OK);
}
