#pragma once
#include <vector>

using namespace std;
#define COLORRED RGB(255,0,0)
#define COLORGREEN RGB(0,255,0)
#define COLORBLUE RGB(0,0,255)

void DotPlot(CClientDC &dc, CPoint point);
void DotPlot(CDC *pDC, CPoint point);

double Angle(CPoint point1, CPoint point2, CPoint point3);          //Javis March  wrapping method


																	//Graham Scan
int crossproduct(CPoint point1, CPoint point2, CPoint point3);
int dotproduct(CPoint point1, CPoint point2, CPoint point3);

void Swap(CPoint & a, CPoint & b);

void Swap(double & a, double & b);


int Partition(vector<CPoint> &b, vector<double> &a, int p, int q);
void QuickSort(vector<CPoint> &b, vector<double> &a, int p, int q);
//MergeHull
double CalcSlope(const CPoint &input, const CPoint &base);
vector<CPoint> MergeVectors(vector<CPoint> &v1, vector<CPoint> &v2);
vector<CPoint> MergeFixUp(vector<CPoint> &v);



