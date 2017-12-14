#pragma once
#include "errors.h"

template<class T>
class WinnerTree
{
private:
	int MaxSize;
	int n;
	int LowExt;
	int offset;
	int *t;
	T *e;
	void Play(int p, int lc, int rc, int(*Winner)(T a[], int b, int c));
public:
	WinnerTree(int TreeSize = 10);
	~WinnerTree() { delete[]t; }
	void Initialize(T a[], int size, int(*winner)(T a[], int b, int c));
	int Winner(int i) const { return (i < n) ? t[i] : 0; }
	int Winner() const { return (n) ? t[1] : 0; }
	void Replay(int i, int(*winner)(T a[], int b, int c));
	
};

template<class T>
WinnerTree<T>::WinnerTree(int TreeSize)
{
	MaxSize = TreeSize;
	t = new int[MaxSize];
	n = 0;
}

template<class T>
void WinnerTree<T>::Initialize(T a[], int size, int(*winner)(T a[], int b, int c))
{
	if (size > MaxSize || size < 2)
		throw OutOfBounds();
	n = size;
	e = a;
	int i, s;
	for (s = 1; 2 * s < n - 1; s += s);
	LowExt = 2 * (n - s);
	offset = 2 * s - 1;

	for (i = 2; i <= LowExt; i += 2)
		Play((offset + i) / 2, i - 1, i, winner);
	if (n % 2)
	{
		play(n / 2, t[n - 1], LowExt + 1, winner);
		i = LowExt + 3;
	}
	else i = LowExt + 2;
	for (; i <= n; i += 2)
		play((i - LowExt + n - 1) / 2, i - 1, i, winner);
}

template<class T>
void WinnerTree<T>::Play(int p, int lc, int rc, int(*winner)(T a[], int b, int c))
{
	t[p] = winner(e, lc, rc);
	while (p > 1 && p % 2)
	{
		t[p / 2] = winner(e, t[p - 1], t[p]);
		p /= 2;
	}
}

template<class T>
void WinnerTree<T>::Replay(int i, int(*winner)(T a[], int b, int c))
{
	if (i <= 0 || i > n)
		throw OutOfBounds();
	int p, lc, rc;
	if (i <= LowExt)
	{
		p = (offset + i) / 2;
		lc = 2 * p - offset;
		rc = lc + 1;
	}
	else
	{
		p = (i - LowExt + n - 1) / 2;
		if (2 * p == n - 1)
		{
			lc = t[2 * p];
			rc = i;
		}
		else
		{
			lc = 2 * p - n + 1 + LowExt;
			rc = lc + 1;
		}
	}
	t[p] = winner(e, lc, rc);
	p /= 2;
	for (; p >= 1; p /= 2)
		t[p] = winner(e, t[2 * p], t[2 * p + 1]);

}