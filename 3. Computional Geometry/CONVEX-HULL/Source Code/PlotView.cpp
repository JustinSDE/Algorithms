// PlotView.cpp : implementation file
//

#include "stdafx.h"
#include "ConvexHull.h"
#include "PlotView.h"
#include "Functions.h"
#include "ConvexHullDlg.h"

// CPlotView

IMPLEMENT_DYNCREATE(CPlotView, CView)

CPlotView::CPlotView()
{
}

CPlotView::~CPlotView()
{
}

BEGIN_MESSAGE_MAP(CPlotView, CView)

	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CPlotView drawing

void CPlotView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

	CConvexHullDlg* pDlg = static_cast<CConvexHullDlg*>(GetParent());
	if (pDlg->m_intMethod == 0)
	{
		int sz_Hull = pDlg->m_HullPts.size(), sz_pts = pDlg->m_Points.size();
		for (int i = 0; i < sz_pts; i++)
		{
			DotPlot(pDC, pDlg->m_Points[i]);
		}
		CPen* oldpen;

		CPen m_pen(PS_SOLID, 2, RGB(255, 0, 0));
		oldpen = pDC->SelectObject(&m_pen);


		if (sz_Hull > 0)
			DotPlot(pDC, pDlg->m_HullPts[0]);
		for (int i = 0; i < sz_Hull - 1; i++)
		{
			pDC->MoveTo(pDlg->m_HullPts[i]);
			pDC->LineTo(pDlg->m_HullPts[i + 1]);
			DotPlot(pDC, pDlg->m_HullPts[i + 1]);
		}
		pDC->SelectObject(oldpen);
	}
	else if (pDlg->m_intMethod == 1)
	{
		int sz_Hull = pDlg->m_HullPts.size(), sz_pts = pDlg->m_Points.size();
		for (int i = 0; i < sz_pts; i++)
		{
			DotPlot(pDC, pDlg->m_Points[i]);
		}

		CPen m_pen2(PS_SOLID, 1, RGB(0, 255, 0));
		CPen* oldpen = pDC->SelectObject(&m_pen2);
		if (pDlg->m_iteration != 0)
			for (int i = pDlg->m_iteration; i < sz_pts; i++)
			{
				pDC->MoveTo(pDlg->m_Points[0]);
				pDC->LineTo(pDlg->m_Points[i]);
			}
		CPen m_pen(PS_SOLID, 2, RGB(255, 0, 0));
		pDC->SelectObject(&m_pen);
		if (sz_Hull > 0)
			DotPlot(pDC, pDlg->m_HullPts[0]);
		for (int i = 0; i < sz_Hull - 1; i++)
		{
			pDC->MoveTo(pDlg->m_HullPts[i]);
			pDC->LineTo(pDlg->m_HullPts[i + 1]);
			DotPlot(pDC, pDlg->m_HullPts[i + 1]);
		}
		pDC->SelectObject(oldpen);
	}
	else if (pDlg->m_intMethod == 2)
	{
		int sz_Hull = pDlg->m_HullPts.size(), sz_pts = pDlg->m_Points.size();
		for (int i = 0; i < sz_pts; i++)
		{
			DotPlot(pDC, pDlg->m_Points[i]);
		}
		if (pDlg->m_CalcFinished == false)
		{
			CPen m_pen2(PS_SOLID, 2, RGB(0, 255, 0));
			CPen* oldpen = pDC->SelectObject(&m_pen2);
			vector<CPoint> temp;
			int sz_temp;
			for (list<vector<CPoint>>::iterator it = pDlg->m_MergeInterMediate.begin();
				it != pDlg->m_MergeInterMediate.end(); it++)
			{
				temp = *it;
				sz_temp = temp.size();
				for (int i = 0; i < sz_temp - 1; i++)
				{
					pDC->MoveTo(temp[i]);
					pDC->LineTo(temp[i + 1]);
				}
				pDC->MoveTo(temp[sz_temp - 1]);
				pDC->LineTo(temp[0]);
			}
			pDC->SelectObject(oldpen);
		}
		else
		{
			CPen m_pen(PS_SOLID, 2, RGB(255, 0, 0));
			CPen *oldpen = pDC->SelectObject(&m_pen);
			if (sz_Hull > 0)
				DotPlot(pDC, pDlg->m_HullPts[0]);
			for (int i = 0; i < sz_Hull - 1; i++)
			{
				pDC->MoveTo(pDlg->m_HullPts[i]);
				pDC->LineTo(pDlg->m_HullPts[i + 1]);
				DotPlot(pDC, pDlg->m_HullPts[i + 1]);
			}
			pDC->SelectObject(oldpen);
		}
	}
	else if (pDlg->m_intMethod == 3)
	{
		int sz_Hull = pDlg->m_HullPts.size(), sz_pts = pDlg->m_Points.size();
		for (int i = 0; i < sz_pts; i++)
		{
			DotPlot(pDC, pDlg->m_Points[i]);
		}
		if (pDlg->m_CalcFinished == false)
		{
			CPen* oldpen;

			CPen m_pen(PS_SOLID, 2, RGB(0, 255, 0));
			oldpen = pDC->SelectObject(&m_pen);
			if (sz_Hull > 0)
				DotPlot(pDC, pDlg->m_HullPts[0]);
			for (int i = 0; i < sz_Hull - 1; i++)
			{
				pDC->MoveTo(pDlg->m_HullPts[i]);
				pDC->LineTo(pDlg->m_HullPts[i + 1]);
				DotPlot(pDC, pDlg->m_HullPts[i + 1]);
			}
			pDC->SelectObject(oldpen);
		}
		else
		{
			CPen* oldpen;

			CPen m_pen(PS_SOLID, 2, RGB(255, 0, 0));
			oldpen = pDC->SelectObject(&m_pen);
			if (sz_Hull > 0)
				DotPlot(pDC, pDlg->m_HullPts[0]);
			for (int i = 0; i < sz_Hull - 1; i++)
			{
				pDC->MoveTo(pDlg->m_HullPts[i]);
				pDC->LineTo(pDlg->m_HullPts[i + 1]);
				DotPlot(pDC, pDlg->m_HullPts[i + 1]);
			}
			pDC->SelectObject(oldpen);
		}
	}
	else
	{

	}
}


// CPlotView diagnostics

#ifdef _DEBUG
void CPlotView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPlotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG





void CPlotView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CConvexHullDlg* pDlg = static_cast<CConvexHullDlg*>(GetParent());
	if (pDlg->m_iteration == 0)
	{
		if (TRUE == pDlg->m_AddPointChecked)
		{
			CClientDC dc(this);
			DotPlot(dc, point);
			pDlg->m_Points.push_back(point);
		}
	}
	else
	{
		if (TRUE == pDlg->m_AddPointChecked)
			MessageBox("Click Start Over to add Points! \nif you want to keep data, please check keep data box!");
	}
	CView::OnLButtonDown(nFlags, point);
}
