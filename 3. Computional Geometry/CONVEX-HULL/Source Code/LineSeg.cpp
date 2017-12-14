#include "stdafx.h"
#include "LineSeg.h"


LineSeg::LineSeg()
{
	start = CPoint(0, 0);
	end = CPoint(0, 0);
}

LineSeg::LineSeg(const CPoint& p1, const CPoint& p2)
{
	start = p1;
	end = p2;
}

LineSeg::~LineSeg()
{
}
const LineSeg& LineSeg::operator=(const LineSeg& v)
{
	if (&v != this)
	{
		start = v.start;
		end = v.end;
	}
	return *this;
}
void LineSeg::SetValue(const CPoint & point1, const CPoint & point2)
{
	start = point1;
	end = point2;
}
