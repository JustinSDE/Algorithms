#pragma once
#include "Functions1.h"

#ifndef FUNCTIONS2_H
#define FUNCTIONS2_H

template<class T>
int SequentialSearch(T a[], const T & x, int n)  //˳������
{//��δ���������a [ 0 : n-1 ]������x
// ����ҵ����򷵻�����λ�ã����򷵻�- 1
	int i;
	for (i = 0; i < n&&a[i] != x; i++);
	if (i == n)
		return -1;
	return i;
}

template <class T>
T PolyEval(T coeff[], int n, const T& x)  //����ʽ��ֵ 
{
	//����n�ζ���ʽ��ֵ��coeff[0:n]Ϊ����ʽ��ϵ��  coeff[0]+coeff[1]*x+coeff[2]*x^2+...+coeff[n]*x^n
	T y = 1, value = coeff[0];
	for (int i = 1; i <= n; i++)
	{
		y *= x;
		value += y*coeff[i];
	}
	return value;
}

template<class T>
T Horner(T coeff[], int n, const T& x)  //Horner����������ʽֵ
{
	//����n�ζ���ʽ��ֵ��coeff[0:n]Ϊ����ʽ��ϵ��  coeff[0]+coeff[1]*x+coeff[2]*x^2+...+coeff[n]*x^n
	T value = coeff[n];
	for (int i = 1; i <= n; i++)
		value = value*x + coeff[n - i];
	return value;
}

template<class T>
void Rank(T a[], int n, int r[])  //��������
{//����a[0:n-1]��n��Ԫ�ص�����
	for (int i = 0; i < n; i++)
		r[i] = 0;
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
			if (a[j] <= a[i]) r[i]++;    //�㷨������
			else r[j]++;
}

template<class T>
void Rearrange2(T a[], int n, int r[])   //�����ν�������
{//������˳��������������
	Rank<T>(a, n, r);
	//ʹ�ø���������Ϊ��ʱ����
	T* u = new T[n];
	for (int i = 0; i < n; i++)
		u[r[i]] = a[i];
	for (int i = 0; i < n; i++)
		a[i] = u[i];
	delete[]u;

}

template<class T>
void Swap(T& a, T& b)  //��������
{
	T temp = b;
	b = a;
	a = temp;
}

template<class T>
void SelectionSort(T a[], int n)   //ѡ������
{
	bool sorted = false;  //��Ӽ�ʱ��ֹ����
	for (int size = n; !sorted && (size > 1); size--)
	{
		int pos = 0;
		sorted = true;
		for (int i = 1; i < size; i++)
			if (a[pos] <= a[i])
				pos = i;
			else
				sorted = false;
		Swap<T>(a[pos], a[size - 1]);
	}
}

template<class T>
bool Bubble(T a[], int n)   //һ��ð�ݹ��� ����Ƿ�����õļ���
{
	bool swapped = false;
	for (int i = 0; i < n - 1; i++)
		if (a[i] > a[i + 1])
		{
			Swap<T>(a[i], a[i + 1]);
			swapped = true;
		}
	return swapped;
}

template<class T>
void BubbleSort(T a[], int n)  //ð���������
{
	for (int i = n; i > 1 && Bubble<T>(a, i); i--);
}

template<class T>
void Insert(T a[], int & n, const T& x)  //����������a[0:n-1]�в���Ԫ��x
{
	int i;
	for (i = n - 1; i >= 0 && a[i] > x; i--)
	{
		a[i + 1] = a[i];
	}
	a[i + 1] = x;
	n++;
}

template<class T>
void Rearrange(T a[], int n, int r[])  //ԭ������������а���������
{
	for(int i=0;i<n;i++)
		while (r[i] != i)
		{
			int t = r[i];
			Swap(a[i], a[t]);
			Swap(r[i], r[t]);
		}
}

template<class T>
void InsertionSort(T a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		T t = a[i];
		Insert(a, i, t);
	}
}
#endif // !FUNCTIONS2_H