#pragma once
#ifndef Array_H
#define Array_H
#include "errors.h"
template<class T>
class Array1D
{
public:
	Array1D(int size = 0);
	Array1D(const Array1D<T> &v);
	~Array1D() { delete[]element; }
	T& operator[](int i) const;
	int Size() { return size; }
	void ReSize(int newsz);
	Array1D<T>& operator =(const Array1D<T>& v);
	Array1D<T> operator+() const;
	Array1D<T> operator+(const Array1D<T>& v) const;
	Array1D<T> operator-() const;
	Array1D<T> operator-(const Array1D<T>& v) const;
	Array1D<T> operator*(const Array1D<T>& v) const;
	Array1D<T> operator+=(const T& x);
private:
	int size;
	T *element;
};

template<class T>
Array1D<T>::Array1D(int sz)
{
	if (sz < 0) throw OutOfBounds();
	size = sz;
	element = new T[sz];
}

template<class T>
Array1D<T>::Array1D(const Array1D<T>& v)
{
	size = v.size;
	element = new T[size];
	for (int i = 0; i < size; i++)
		element[i] = v.element[i];
}

template<typename T>
T& Array1D<T>::operator[](int i) const
{
	if (i < 0 || i >= size) throw OutOfBounds();
	return element[i];
}

template<typename T>
Array1D<T>& Array1D<T>::operator=(const Array1D<T> &v)
{
	if (this != &v)
	{
		size = v.size;
		delete[]element;
		element = new T[size];
		for (int i = 0; i < size; i++)
			element[i] = v.element[i];
	}
	return *this;
}

template<typename T>
void Array1D<T>::ReSize(int newsz)
{
	T* temp = element;
	size = newsz;
	element = new T[newsz];
	delete[]temp;
}
template<class T>
Array1D<T> Array1D<T>::operator-(const Array1D<T>& v) const
{
	if (size != v.size) throw OutOfBounds();
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = element[i] - v.element[i];
	return w;
}

template<class T>
Array1D<T> Array1D<T>::operator*(const Array1D<T>& v) const
{
	if (size != v.size) throw OutOfBounds();
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = element[i] * v.element[i];
	return w;
}
template<class T>
Array1D<T> Array1D<T>::operator+(const Array1D<T>& v) const
{
	if (size != v.size) throw OutOfBounds();
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = element[i] + v.element[i];
	return w;
}
template<class T>
Array1D<T> Array1D<T>::operator-() const
{
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = -element[i];
	return w;
}

template<class T>
Array1D<T> Array1D<T>::operator+() const
{
	Array1D<T> w(size);
	for (int i = 0; i < size; i++)
		w.element[i] = element[i];
	return w;
}

template<class T>
Array1D<T>& Array1D<T>::operator+=(const T& x)
{
	for (int i = 0; i < size; i++)
		element[i] += x;
	return *this;
}

template<typename T>
class Array2D
{
private:
	int rows, cols;
	Array1D<T> *row;
public:
	Array2D(int r = 0, int c = 0);
	Array2D(const Array2D<T>& m);
	~Array2D() { delete[]row; }
	int Rows() const { return rows; }
	int Columns() const { return cols; }
	Array1D<T>& operator[](int i) const;
	Array2D<T>& operator=(const Array2D<T>& m) {}
	Array2D<T> operator+() const {}
	Array2D<T> operator+(const Array2D<T>& m) const {}
	Array2D<T> operator-() const {}
	Array2D<T> operator-(const Array2D<T>& m) const;
	Array2D<T> operator*(const Array2D<T>& m) const;
	Array2D<T>& operator+=(const T&x) {}
};

template<class T>
Array2D<T>::Array2D(int r, int c)
{
	if (r < 0 || c < 0) throw OutOfBounds();
	if ((!r || !c) && (r || c)) throw OutOfBounds();
	rows = r;
	cols = c;
	row = new Array1D<T>[r];
	for (int i = 0; i < r; i++)
		row[i].ReSize(c);
}

template<class T>
Array2D<T>::Array2D(const Array2D<T>& m)
{
	row = m.rows;
	cols = m.cols;
	row = new Array1D<T>[rows];
	for (int i = 0; i < rows; i++)
		row[i] = m.row[i];
}

template<class T>
Array1D<T>& Array2D<T>::operator[](int i) const
{
	if (i <= 0 || i >= rows) throw OutOfBounds();
	return row[i];
}

template<class T>
Array2D<T> Array2D<T>::operator-(const Array2D<T>& m) const
{
	if (rows != m.rows || cols != m.cols)
		throw OutOfBounds();
	Array2D<T> w(rows, cols);
	for (int i = 0; i < rows; i++)
		w.row[i] = row[i] - m.row[i];
	return w;
}
template<class T>
Array2D<T> Array2D<T>:: operator*(const Array2D<T>& m) const
{// 矩阵乘，返回w = (*this) * m.
	if (cols != m.rows) throw OutOfBounds();
	// 创建存放结果的数组w
	Array2D<T> w(rows, m.cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < m.cols; j++) {
			T sum = (*this)[i][0] * m[0][j];
			for (int k = 1; k < cols; k++)
				sum += (*this)[i][k] * m[k][j];
			w[i][j] = sum;
		}
	return w;
}
#endif // !Array_H
