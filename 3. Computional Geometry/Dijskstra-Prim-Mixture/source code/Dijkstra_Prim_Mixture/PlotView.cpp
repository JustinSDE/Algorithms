// PlotView.cpp : implementation file
//

#include "stdafx.h"
#include "Dijkstra_Prim_Mixture.h"
#include "PlotView.h"
#include "Dijkstra_Prim_MixtureDlg.h"
#include "Functions.h"
#include "PtInfo.h"


// PlotView

IMPLEMENT_DYNCREATE(PlotView, CView)

PlotView::PlotView()
{

}

PlotView::~PlotView()
{
}

BEGIN_MESSAGE_MAP(PlotView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// PlotView drawing

void PlotView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

	CDijkstra_Prim_MixtureDlg* pDlg = static_cast<CDijkstra_Prim_MixtureDlg*> (GetParent());
	int sz = pDlg->m_Points.size();
	CPen pen(PS_SOLID, 3, RGB(255, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen);
	for (int i = 0; i < sz; i++)
	{
		DotPlot(pDC, pDlg->m_Points[i]);
	}
	if (pDlg->m_calculated == true)
	{
		CPen mypen(PS_SOLID, 2, RGB(0, 255, 0));
		pDC->SelectObject(&mypen);
		int prevID;
		CString str;
		str.Format("%d%%    total cost = %d    max latency = %d", pDlg->m_intWeight,pDlg->m_totalCost,pDlg->m_maxLatency);
		pDC->TextOutA(2, 2, str);
		for (int i = 0; i < sz; i++)
		{
			prevID = pDlg->m_LinkedPts[i].PrevPointID;
			pDC->MoveTo(pDlg->m_Points[i]);
			pDC->LineTo(pDlg->m_Points[prevID]);
		}
	}
	pDC->SelectObject(oldpen);
}


// PlotView diagnostics

#ifdef _DEBUG
void PlotView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void PlotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// PlotView message handlers


void PlotView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);
}
