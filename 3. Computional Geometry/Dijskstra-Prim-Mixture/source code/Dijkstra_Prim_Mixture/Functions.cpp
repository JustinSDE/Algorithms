#include "Functions.h"
#include "stdafx.h"


void DotPlot(CClientDC &dc, CPoint point)
{
	dc.Rectangle(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
}

void DotPlot(CDC *pDC, CPoint point)
{
	pDC->Rectangle(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
}

int CalcDistance(const CPoint & p1, const CPoint & p2)
{
	int res;
	int x = p1.x - p2.x;
	int y = p1.y - p2.y;
	res =(int) sqrt(x*x + y*y);
	return res;
}