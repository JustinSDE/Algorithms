#pragma once
#include "atltypes.h"
class LineSeg
{
public:
	LineSeg();
	LineSeg(const CPoint& point1, const CPoint& point2);
	~LineSeg();
	CPoint start;
	CPoint end;
	const LineSeg& operator=(const LineSeg& v);
	void SetValue(const CPoint & point1, const CPoint & point2);
};

