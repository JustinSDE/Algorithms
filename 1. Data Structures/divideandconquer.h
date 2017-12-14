#pragma once
#ifndef NEAREASTPAIROFPHONTS_H
#define NEAREASTPAIROFPHONTS_H

#include <cmath>
extern void main();

template<typename T>
void MergeSort(T a[], int start, int end)
{
	if (start == end)                   // End of recursive call
		return;

	int pos = (start + end) / 2;        // Recursive call
	MergeSort(a, start, pos);
	MergeSort(a, pos + 1, end);
	//copy two parts into two diferent arrays
	int size1 = pos - start + 1, size2 = end - pos;
	T* temp1 = new T[size1];
	for (int i = 0; i < size1; i++)
		temp1[i] = a[start + i];
	T* temp2 = new T[size2];
	for (int i = 0; i < size2; i++)
		temp2[i] = a[pos + 1 + i];
	// merge two separate parts
	int index1 = 0, index2 = 0, index3 = start + 0;
	while (index1 < size1 && index2 < size2)
	{
		if (temp1[index1] > temp2[index2])
		{
			a[index3++] = temp2[index2++];
		}
		else
		{
			a[index3++] = temp1[index1++];
		}
	}
	for (; index1 < size1; index1++)
	{
		a[index3++] = temp1[index1];
	}
	for (; index2 < size2; index2++)
	{
		a[index3++] = temp2[index2];
	}
	//delete new allocated spaces
	delete[]temp1;
	delete[]temp2;

	return;
}

template<typename T>
void MergeSort(T a[], int size)
{
	MergeSort(a, 0, size - 1);
}

class Point2;

class Point1
{
	friend float dist(const Point1&, const Point1&);
	friend void close(Point1*, Point2*, Point2*, int, int, Point1&, Point1&, float&);
	friend bool closest(Point1 *, int, Point1&, Point1&, float&);
private:
	int ID;
	float x, y;
public:
	int operator<=(Point1 a) const { return (x <= a.x); }
	int operator>(Point1 a) const { return (x > a.x); }
};

class Point2
{
	friend float dist(const Point2&, const Point2&);
	friend void close(Point1*, Point2*, Point2*, int, int, Point1&, Point1&, float&);
	friend bool closest(Point1 *, int, Point1&, Point1&, float&);
	friend void main();
public:
	int operator<=(Point2 a) const
	{
		return (y <= a.y);
	}
	int operator>(Point2 a) const
	{
		return (y > a.y);
	}
private:
	int p;       //数组X中相同的索引点
	float x, y;
};

template<class T>
inline float dist(const Point1& u, const Point1& v)
{
	float dx = u.x - v.x;
	float dy = u.y - v.y;
	return std::sqrtf(dx*dx + dy*dy)
}

template<class T>
inline float dist(const Point2& u, const Point2& v)
{
	float dx = u.x - v.x;
	float dy = u.y - v.y;
	return std::sqrtf(dx*dx + dy*dy)
}

template<typename T>
void Merge(T c[], T d[], int l, int m, int r)
{
	int i = l, j = m + 1, k = l;
	while ((i <= m) && (j <= r))
	{
		if (c[i] <= c[j]) d[k++] = c[i++];
		else d[k++] = c[j++];
	}
		
		
	if (i > m) for (int q = j; q < r; q++)
		d[k++] = c[q]++;
	else for (int q = i; q <= m; q++)
		d[k++] = c[q];

}
void close(Point1* X, Point2 *Y, Point2* Z, int l, int r, Point1 &a, Point1& b, float& d)
{
	if (r - l == 1)           //two points in between;
	{
		a = X[l];
		b = X[r];
		d = dist(a, b);
		return;
	}

	if (r - l == 2)             //three points in between
	{
		float d1 = dist(X[l], X[l + 1]);
		float d2 = dist(X[l + 1], X[r]);
		float d3 = dist(X[l], X[r]);
		if (d1 <= d2 && d1 <= d3)
		{
			a = X[l];
			b = X[l + 1];
			d = d1;
			return;
		}
		if (d2 <= d3)
		{
			a = X[l + 1];
			b = X[r];
			d = d2;
			return;
		}
		else
		{
			a = X[l];
			b = X[r];
			d = d3;
			return;
		}
	}


	//more than three points;
	// This divide and conquer is the key here becasue it uses linear time solve the problem
	int m = (l + r) / 2;
	int f = l,   //iterator for Z[l:m] 
		g = m + 1;  //iterator for Z[m+1:r]
	for (int i = l; i <= r; i++) {
		if (Y[i].p > m) Z[g++] = Y[i];
		else Z[f++] = Y[i];
	}

	close(X, Z, Y, l, m, a, b, d);
	float dr;
	Point1 ar, br;
	close(X, Z, Y, m + 1, r, ar, br, dr);

	if (dr < d)
	{
		a = ar; b = br; d = dr;
	}

	Merge(Z, Y, l, m, r);   //reconstuct Y

	int k = l;
	for (int i = l; i <= r; i++)
		if (fabs(Y[m].x - Y[i].x) < d)  Z[k++] = Y[i];
	for (int i = l; i < k; i++) {
		for (int j = i + 1; j < k && Z[j].y - Z[i].y < d; j++)
		{
			float dp = dist(Z[i], Z[j]);
			if (dp < d)
			{// 较近的点对
				d = dp;
				a = X[Z[i].p];
				b = X[Z[j].p];
			}
		}

	}
}

bool closest(Point1 *X, int n, Point1 & a, Point1 & b, float &d)
{
	if (n < 2)
		return false;
	MergeSort(X, n);

	Point2 *Y = new Point2[n];

	for (int i = 0; i < n; i++)
	{
		Y[i].p = i;
		Y[i].x = X[i].x;
		Y[i].y = X[i].y;
	}

	MergeSort(Y, n);

	Point2 *Z = new Point2[n];

	close(X, Y, Z, 0, n - 1, a, b, d);

	delete[]Y;
	delete[]Z;
}



#endif // !NEAREASTPAIROFPHONTS_H

