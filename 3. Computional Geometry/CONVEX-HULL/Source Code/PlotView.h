#pragma once

// CPlotView view

class CPlotView : public CView
{
	DECLARE_DYNCREATE(CPlotView)

public:
	CPlotView();           // protected constructor used by dynamic creation
	virtual ~CPlotView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


