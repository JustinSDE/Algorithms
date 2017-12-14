#include "Functions.h"
#include "stdafx.h"
#include <vector>
#include <cmath>
using namespace std;

void DotPlot(CClientDC &dc, CPoint point)
{
	dc.Rectangle(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
}

void DotPlot(CDC *pDC, CPoint point)
{
	pDC->Rectangle(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
}

double Angle(CPoint point1, CPoint point2, CPoint point3)
{
	int x1, y1, x2, y2, x3, y3;
	x1 = point2.x - point1.x;
	y1 = point2.y - point1.y;
	x2 = point3.x - point2.x;
	y2 = point3.y - point2.y;
	x3 = point3.x - point1.x;
	y3 = point3.y - point1.y;
	double e1, e2;
	e1 = sqrt(1.0*x1*x1 + y1*y1);
	e2 = sqrt(1.0*x2*x2 + y2*y2);
	double res = -1.0*(x1*x1 + y1*y1 + x2*x2 + y2*y2 - x3*x3 - y3*y3) / e1 / e2;
	return res;
}

int crossproduct(CPoint point1, CPoint point2, CPoint point3)
{
	int x1, y1, x2, y2;
	x1 = point2.x - point1.x;
	y1 = point2.y - point1.y;
	x2 = point3.x - point2.x;
	y2 = point3.y - point2.y;
	int res = x1*y2 - x2*y1;

	return res;
}

int dotproduct(CPoint point1, CPoint point2, CPoint point3)
{
	int x1, y1, x2, y2;
	x1 = point2.x - point1.x;
	y1 = point2.y - point1.y;
	x2 = point3.x - point2.x;
	y2 = point3.y - point2.y;
	int res = x1*x2 + y2*y1;

	return res;
}
void Swap(CPoint & a, CPoint & b)
{
	CPoint temp = b;
	b = a;
	a = temp;
}

void Swap(double & a, double & b)
{
	double temp = b;
	b = a;
	a = temp;
}

int Partition(vector<CPoint> &b, vector<double> &a, int p, int q)
{
	if (p == q)
		return p;
	int i = p, j = p;
	for (j; j < q; j++)
	{
		if (a[j] < a[q])
		{
			Swap(a[i], a[j]);
			Swap(b[i], b[j]);
			i++;
		}
	}
	Swap(a[q], a[i]);
	Swap(b[q], b[i]);
	return i;
}

void QuickSort(vector<CPoint> &b, vector<double> &a, int p, int q)
{
	int pos;
	if (p < q)
	{
		pos = Partition(b, a, p, q);
		QuickSort(b, a, p, pos - 1);
		QuickSort(b, a, pos + 1, q);
	}
}

double CalcSlope(const CPoint &input, const CPoint &base)
{
	double res;
	if (input.x != base.x)
		res = 1.0*(input.y - base.y) / (input.x - base.x);
	else
	{
		if (input.y < base.y)
			res = -2000.0;
		else
			res = 2000.0;
	}
	return res;
}

vector<CPoint> MergeVectors(vector<CPoint> &v1, vector<CPoint> &v2)
{
	if (v1[0].x > v2[0].x)
		v1.swap(v2);
	CPoint base = v1[0];
	int sz1 = v1.size(), sz2 = v2.size();
	for (int i = 0; i < sz1 - 1; i++)
		v1[i] = v1[i + 1];
	v1.pop_back();
	int index_max = 0, index_min = 0;
	double slope_max, slope_min, slope;
	slope_max = slope_min = CalcSlope(v2[0], base);
	for (int i = 1; i < sz2; i++)
	{
		slope = CalcSlope(v2[i], base);
		if (slope > slope_max)
		{
			index_max = i;
			slope_max = slope;
		}
		if (slope < slope_min)
		{
			index_min = i;
			slope_min = slope;
		}
	}
	vector<CPoint> temp1, temp2;
	if (index_max == index_min)
		temp1.push_back(v2[index_min]);
	else
	{
		for (int i = index_min; i != index_max;)
		{
			temp1.push_back(v2[i]);
			i = (i + 1) % sz2;
		}
		for (int i = index_min; i != index_max;)
		{
			i = (i - 1 + sz2) % sz2;
			temp2.push_back(v2[i]);
		}
	}
	int sz_temp1 = temp1.size(), sz_temp2 = temp2.size();
	vector<CPoint> temp4;
	int index_temp1 = 0, index_temp2 = 0;
	while (index_temp1 < sz_temp1 && index_temp2 < sz_temp2)
	{
		if (CalcSlope(temp1[index_temp1], base) < CalcSlope(temp2[index_temp2], base))
		{
			temp4.push_back(temp1[index_temp1]);
			index_temp1++;
		}
		else
		{
			temp4.push_back(temp2[index_temp2]);
			index_temp2++;
		}
	}
	for (; index_temp1 < sz_temp1; index_temp1++)
		temp4.push_back(temp1[index_temp1]);
	for (; index_temp2 < sz_temp2; index_temp2++)
		temp4.push_back(temp2[index_temp2]);

	temp1.swap(v1);
	temp2.swap(temp4);
	temp4.clear();
	temp4.push_back(base);

	sz_temp1 = temp1.size(), sz_temp2 = temp2.size();
	index_temp1 = 0, index_temp2 = 0;
	while (index_temp1 < sz_temp1 && index_temp2 < sz_temp2)
	{
		if (CalcSlope(temp1[index_temp1], base) < CalcSlope(temp2[index_temp2], base))
		{
			temp4.push_back(temp1[index_temp1]);
			index_temp1++;
		}
		else
		{
			temp4.push_back(temp2[index_temp2]);
			index_temp2++;
		}
	}
	for (; index_temp1 < sz_temp1; index_temp1++)
		temp4.push_back(temp1[index_temp1]);
	for (; index_temp2 < sz_temp2; index_temp2++)
		temp4.push_back(temp2[index_temp2]);

	return temp4;
}


vector<CPoint> MergeFixUp(vector<CPoint> &input)
{
	vector<CPoint> res;
	int sz_input = input.size();
	int sz_res;
	bool fixed;
	CPoint p1, p2, p3;
	int angle;
	for (int i = 0; i < sz_input; i++)
	{
		res.push_back(input[i]);
		sz_res = res.size();
		if (sz_res < 3)
			continue;
		else
		{
			fixed = false;
			do {
				//put the fix code here:
				sz_res = res.size();
				p1 = res[sz_res - 3];
				p2 = res[sz_res - 2];
				p3 = res[sz_res - 1];
				angle = crossproduct(p1, p2, p3);
				if (angle > 0)
					fixed = true;
				else if (angle < 0)
				{
					res.pop_back();
					res.pop_back();
					res.push_back(p3);
					continue;
				}
				else
				{
					if (dotproduct(p1, p2, p3) < 0)
					{
						res[sz_res - 2] = p3;
						res[sz_res - 1] = p2;
					}
					else
						fixed = true;
				}
			} while (fixed != true);
		}
	}
	return res;
}

