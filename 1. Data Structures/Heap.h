#pragma once
#include "errors.h"
#include "Functions2.h"
#include "Queue.h"
#include <iostream>
template<typename T>
class MaxHeap
{
private:
	int CurrentSize, MaxSize;
	T *heap;
public:
	MaxHeap(int MaxHeapSize = 10);
	~MaxHeap() { delete[]heap; }
	int Size() const { return CurrentSize; }
	T Max() {
		if (CurrentSize == 0)
			throw OutOfBounds();
		return heap[1];
	}
	MaxHeap<T>& Insert(const T& x);
	MaxHeap<T>& DeleteMax(T& x);
	void Initialize(T a[], int size, int ArraySize);
};

template<typename T>
MaxHeap<T>::MaxHeap(int MaxHeapSize)
{
	MaxSize = MaxHeapSize;
	heap = new T[MaxSize + 1];
	CurrentSize = 0;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x)
{
	if (CurrentSize == MaxSize)
		throw NoMem();
	int i = ++CurrentSize;
	while (i != 1 & x > heap[i / 2])
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = x;
	return *this;
}

template<class T>
MaxHeap<T> & MaxHeap<T>::DeleteMax(T& x)
{
	if (CurrentSize == 0)
		throw OutOfBounds();
	x = heap[1];
	T y = heap[CurrentSize--];
	int i = 1, ci = 2;
	while (ci <= CurrentSize)
	{
		if (ci < CurrentSize && heap[ci] < heap[ci + 1])
			ci++;
		if (y >= heap[ci])
			break;
		heap[i] = heap[ci];
		i = ci;
		ci *= 2;
	}
	heap[i] = y;
	return *this;
}

template<class T>
void MaxHeap<T>::Initialize(T a[], int size, int ArraySize)
{
	delete[] heap;
	heap = a;
	CurrentSize = size;
	MaxSize = ArraySize;
	for (int i = CurrentSize / 2; i >= 1; i--)
	{
		T y = heap[i];
		int c = 2 * i;
		while (c <= CurrentSize)
		{
			if (c < CurrentSize && heap[c] < heap[c + 1])
				c++;
			if (y >= heap[c]) break;

			heap[c / 2] = heap[c];
			c *= 2;
		}
		heap[c / 2] = y;
	}
}

template<typename T>
class HBLTNode
{
private:
	int s;
	T data;
	HBLTNode<T> *LeftChild, *RightChild;
public:
	friend MaxHBLT<T>;
	HBLTNode(const T& e, const int sh):data(e),s(sh)
	{
		LeftChild = RightChild = 0;
	}
};

template<class T>
class MaxHBLT
{
private:
	void Free(HBLTNode<T> *t);
	void Meld(HBLTNode<T>* &x, HBLTNode<T>* y);
	HBLTNode<T> *root;
public:
	MaxHBLT() { root = 0; }
	~MaxHBLT() { Free(root); }
	T Max()
	{
		if (!root) throw OutOfBounds();
		return root->data;
	}
	MaxHBLT<T>& Insert(const T& x);
	MaxHBLT<T>& DeleteMax(T& x);
	MaxHBLT<T>& Meld(MaxHBLT<T>& x)
	{
		Meld(root, x.root);
		x.root = 0;
		return *this;
	}
	void Initialize(T a[], int n);
};

template<class T>
void MaxHBLT<T>::Meld(HBLTNode<T>* &x, HBLTNode<T>* y)
{//合并两棵要分别为*x和*y的左高树
	//返回指向新根x的指针
	if (!y) return; //y为空
	if (!x) //x为空
	{
		x = y;
		return;
	}
	if (x->data < y->data)
		Swap(x, y);
	Meld(x->RightChild, y);
	if (!x->LeftChild)  //左子树为空
	{
		x->LeftChild = x->RightChild;
		x->RightChild = 0;
		x->s = 1;
	}
	else
	{
		if (x->LeftChild->s < x->RightChild->s)
			Swap(x->LeftChild, x->RightChild);
		x->s = x->RightChild->s + 1;
	}

}

template<class T>
MaxHBLT<T>& MaxHBLT<T>::Insert(const T& x)
{
	HBLTNode<T>* q = new HBLTNode<T>(x, 1);
	Meld(root, q);
	return *this;
}

template<class T>
MaxHBLT<T>& MaxHBLT<T>::DeleteMax(T& x)
{
	if (!root) throw OutOfBounds();
	x = root->data;
	HBLTNode<T> *L = root->LeftChild, *R=root->RightChild;
	delete root;
	root = L;
	Meld(root, R);
	return *this;
}

template<class T>
void MaxHBLT<T>::Initialize(T a[], int n)
{
	LinkedQueue<HBLTNode<T>*> Q;
	Free(root);
	for (int i = 1; i <= n; i++)
	{
		HBLTNode<T> *q = new HBLTNode<T>(a[i], 1);
		Q.Add(q);
	}
	HBLTNode<T> *b, *c;
	for (i = 1; i <= n - 1; i++)
	{
		Q.Delete(b).Delete(c);
		Meld(b, c);
		Q.Add(b);
	}
	if (n) Q.Delete(root);
}


template<class T>
void HeapSort(T a[], int n)
{
	MaxHeap<T> H(1);
	H.Initialize(a, n, n);

	T x;
	for (int i = n - 1; i >= 1; i--)
	{
		H.DeleteMax(x);
		a[i + 1] = x;
	}
}

