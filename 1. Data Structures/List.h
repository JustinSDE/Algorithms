#pragma once
#include <iostream>
#include "errors.h"

#ifndef LIST_H
#define LIST_H               //线性表

template<class T>
class LinearList            //数组描述
{
private:
	int length;
	int MaxSize;
	T* element;
public:
	LinearList(int MaxListSize = 10);
	~LinearList() { delete[] element; }
	bool IsEmpty() const { return length == 0; }
	bool Find(int k, T & x) const;
	int Search(const T & x) const;
	int Length() const { return length; }
	LinearList<T> & Delete(int k, T& x);
	LinearList<T>& Insert(int k, const T& x);
	void Output(std::ostream & out) const;
};

template<class T>
LinearList<T>::LinearList(int MaxListSize) : MaxSize(MaxListSize)
{
	length = 0;
	element = new T[MaxSize];
}

template<class T>
bool LinearList<T>::Find(int k, T & x) const
{
	if(k<0 || k>length-1)
	return false;
	x = element[k];
	return true;
}
template<class T>
int LinearList<T>::Search(const T & x) const
{
	for (int i = 0; i < length; i++)
		if (element[i] == x)
			return i;
	return -1;
}
template<class T>
LinearList<T>& LinearList<T>::Delete(int k, T & x)
{
	if (Find(k, x))
	{
		for (int i = k; i < length-1; i++)
			element[i] = element[i + 1];
		length--;
		return *this;
	}
	else
		throw OutOfBounds();
}

template<class T>
LinearList<T>& LinearList<T>::Insert(int k, const T & x)
{
	if (k<0 || k>length) throw OutOfBounds();
	if (length == MaxSize) throw NoMem();
	for (int i = length - 1; i >= k; i--)
		element[i + 1] = element[i];
	element[k] = x;
	length++;
	return *this;
}

template<class T>
void LinearList<T>::Output(std::ostream & out) const
{
	for (int i = 0; i < length; i++)
	{
		out << element[i] << ' ';
		if (i % 10 == 9)
			out << '\n';
	}	
}

template<class T>
std::ostream& operator<<(std::ostream& out, const LinearList<T>& x)     //输出重载函数
{
	x.Output(out);
	return out;
}

template<class T> class Chain;                                           //链表描述

template<class T>
class ChainNode
{
	friend class Chain<T>;
private:
	T data;
	ChainNode<T>* link;
};

template<class T>
class Chain
{
private:
	ChainNode<T>* first;   //表头节点
public:
	Chain() { first = NULL; }
	~Chain();
	bool IsEmpty() const { return first == NULL; }
	int Length() const;
	bool Find(int k, T & x) const;
	int Search(const T& x) const;
	Chain<T>& Delete(int k, T& x);
	Chain<T>& Delete(T &x);
	Chain<T>& Insert(int k, const T& x);
	void Output(std::ostream& out) const;
};


template<class T>
Chain<T>::~Chain()
{
	ChainNode<T>* temp;
	while (first != NULL)
	{
		temp = first->link;
		delete first;
		first = temp;
	}
}

template<class T>
int Chain<T>::Length() const
{
	int res = 0;
	ChainNode<T>* temp=first;
	while (temp)
	{
		res++;
		temp = temp->link;
	}
	return res;
}

template<class T>
bool Chain<T>::Find(int k, T & x) const
{
	if (k < 0) return false;

	int i = 0;
	ChainNode<T>* temp = first;
	while (i < k && temp != NULL)
	{
		i++;
		temp = temp->link;
	}
	if (temp != NULL)
	{
		x = temp->data;
		return true;
	}

	return false;
}

template<class T>
int Chain<T>::Search(const T & x) const
{
	int i = 0;
	ChainNode<T>* temp = first;
	while (temp != NULL)
	{
		if (x == temp->data)
			return i;
		i++;
		temp = temp->link;
	}
	return -1;
}

template<class T>
Chain<T>& Chain<T>::Delete(int k, T & x)
{
	ChainNode<T>* q = first;
	if (k < 0 || first==NULL)
		throw OutOfBounds();
	ChainNode<T>* p = first;
	if (k == 0)
		first = first->link;
	else
		
	for (int index = 0; index < k - 1 && q; index++)
		q = q->link;
	if (!q || !q->link)
		throw OutOfBounds();
	p = q->link;
	q->link = p->link;
	x = p->data;
	delete p;
	return *this;
}

template<class T>
Chain<T>& Chain<T>::Insert(int k, const T & x)
{
	// TODO: insert return statement here
	if (k < 0)
		throw OutOfBounds();
	ChainNode<T>* p = first;
	for (int index = 0; index < k &&p; index++)
		p = p->link;
	if (k >= 0 && !p)
		throw OutOfBounds();
	ChainNode<T> *y = new ChainNode<T>;
	y->data = x;
	if (k)
	{
		y->link = p->link;
		p->link = y;
	}
	else 
	{
		y->link = first;
		first = y;
	}
	return *this;
}

template<class T>
Chain<T>& Chain<T>::Delete(T& x)
{
	ChainNode<T> *current = first, *trail = 0;

	while (current && current->data != x)
	{
		trail = current;
		current = current->link;
	}
	if (!current)
		throw OutOfBounds();
	x = current->data;

	if (trail) trail->link = current->link;
	else first = current->link;

	delete current;
	return *this;
}
template<class T>
void Chain<T>::Output(std::ostream & out) const
{
	ChainNode<T>* temp = first;
	int i = 0;
	while (temp != NULL)
	{
		out << temp->data<<' ';
		temp = temp->link;
		if (i++ / 10 == 9)
			out << '\n';
	}
}

template<class T>
std::ostream& operator<<(std::ostream & out, const Chain<T>& x)
{
	x.Output(out);
	return out;
}


template<class T>
class IndirectList                                                     //间接寻址表
{
private:
	T** table;
	int length, MaxSize;
public:
	IndirectList(int MaxListSize = 10);
	~IndirectList();
	bool IsEmpty() const { return length == 0; }
	int Length() const { return length; }
	bool Find(int k, T & x) const;
	int Search(const T& x) const;
	IndirectList<T>& Delete(int k, T& x);
	IndirectList<T>& Insert(int k, const T& x);
	void Output(std::ostream& out) const;
};

template<class T>
IndirectList<T>::IndirectList(int MaxListSize)
{
	table = new T*[MaxListSize];
	length = 0;
	MaxSize = MaxListSize;
}

template<class T>
IndirectList<T>::~IndirectList()
{
	for (int i = 0; i < length; i++)
		delete table[i];
	delete[] table;
}

template<class T>
bool IndirectList<T>::Find(int k, T & x) const
{
	if (k<0 || k> length - 1)
		return false;
	x = *table[k];
	return true;
}

template<class T>
int IndirectList<T>::Search(const T & x) const
{
	for (int i = 0; i < length; i++)
		if (*table[i] == x)
			return i;
	return -1;
}

template<class T>
IndirectList<T>& IndirectList<T>::Delete(int k, T & x)
{
	if (Find(k, x))
	{
		for (int i = k; i < length - 1; i++)
			table[i] = table[i + 1];
		length--;
		return *this;
	}
	else
		throw OutOfBounds();
}

template<class T>
inline IndirectList<T>& IndirectList<T>::Insert(int k, const T & x)
{
	// TODO: insert return statement here
	if (k<0 || k>length) throw OutOfBounds();
	if (length == MaxSize) throw NoMem();
	for (int i = length - 1; i >= k; i--)
		table[i + 1] = table[i];
	table[k] = new T;
	*table[k] = x;
	length++;
	return *this;
}

 //模拟指针
template<class T> class SimSpace;
template<class T>																	 //模拟指针空间节点
class SimNode
{
	friend SimNode<T>;
private:
	T data;
	int link;
};

template<class T>                                                                   //模拟指针空间
class SimSpace
{
private:
	int NumberOfNodes, first1,first2;
	SimNode<T>* Node;          // NODE数组
public:
	SimSpace(int MaxSapceSize = 100);
	~SimSpace() { delete[]Node; }
	int Allocate();
	void Deallocate(int& i);
};


template<class T>
SimSpace<T>::SimSpace(int MaxSapceSize)
{
	NumberOfNodes = MaxSpaceSize;
	Node = new SimNode<T>[NumberOfNodes];
	for (int i = 0; i < NumberOfNodes - 1; i++)
		Node[i].link = i + 1;
	Node[NumberOfNodes - 1].link = -1;
	first = 0;
}

template<class T>
int SimSpace<T>::Allocate()
{
	if (first == -1) throw NoMem();
	int i = first;
	first = Node[i].link;
	return i;
}

template<class T>
void SimSpace<T>::Deallocate(int & i)
{
	Node[i].link = first;
	first = i; 
	i = -1;
}

template<class T>
class SimChain
{
private:
	int first;
	static SimSpace<T> S;
public:
	SimChain()
	{
		first = -1;
	}
	~SimChain() { Destroy(); }
	void Destroy();
	int Length() const;
	bool Find(int k, T& x) const;
//	int Search(const T& x) const;
	SimChain<T>& Delete(int k, T & x);
	SimChain<T>& Insert(int k, const T& x);
//	void Output(ostream & out) const;
};

template<class T>
SimSpace<T> SimChain<T>::S = SimSpace<T>(100);

template<class T>
void SimChain<T>::Destroy()
{
	int next=0;
	while (first != -1)
	{
		next = S.Node[first].link;
		S.Deallocate(first);
		first = next;
	}
}

template<class T>
int SimChain<T>::Length() const
{
	int current = first;
	len = 0;
	while (current != -1)
	{
		current = S.Node[current].link;
		len++;
	}
	return len;
}

template<class T>
bool SimChain<T>::Find(int k, T & x) const
{
	if (k < 0) return false;
	int current = first;
	index = 1;
	while (index < k-1 && current != -1)
	{
		current = S.Node[current].link;
		index++;
	}
	if (current != -1)
	{
		x = S.Node[current].data;
		return true;
	}
	return false;
}

template<class T>
SimChain<T> & SimChain<T>::Delete(int k, T& x)
{
	if (k < 0 || first == -1)
		throw OutOfBounds();
	int p = first;
	if (k == 0)
		first = S.Node[first].link;
	else
	{
		int q = first;
		for (int index = 1; index < k - 1 && q != -1; index++)
			q = S.Node[q].link;
		if (q == -1 || S.Node[q].link == -1)
			throw OutOfBounds();
		p = S.Node[q].link;
		S.Node[q].link = S.Node[p].link;
	}
	x = S.Node[p].data;
	S.Deallocate(p);
	return *this;
}

template<class T>
SimChain<T>& SimChain<T>::Insert(int k, const T& x)
{
	if (k < 0) throw OutOfBounds();
	int p = first;
	for (int index = 1; index < k && p != -1; index++)
		p = S.Node[p].link;
	if (k > 0 && p == -1)
		throw OutOfBounds();
	int y = S.Allocate();
	S.Node[y].data = x;
	if (k)
	{
		S.Node[y].link = S.Node[p].link;
		S.Node[p].link = y;
	
	}
	else
	{
		S.Node[y].link = first;
		first = y;
	}
	return *this;
}

                                                             //箱子排序节点
class BoxNode 
{
	friend std::ostream& operator<<(std::ostream&, const BoxNode&);
	friend void BinSort(Chain<BoxNode>& X, int range);
private:
	int score;
	char* name;
public:
	operator int() const { return score; }
	int operator!=(const BoxNode& x) const
	{
		return(score != x.score || strcmp(name,x.name)!=0);
	}
};

std::ostream& operator<<(std::ostream& out, const BoxNode& x)
{
	out << x.score << ' '<<x.name[0]<<' ';
	return out;
}

void BinSort(Chain<BoxNode>& X, int range)                              //箱子排序方式  非成员函数
{
	int len = X.Length();
	BoxNode x;
	Chain<BoxNode>* bin;
	bin = new Chain<BoxNode>[range + 1];
	for (int i = 0; i < len; i++)              //将数据插入不同的BIN中
	{
		X.Delete(0, x);
		bin[x.score].Insert(0, x);
	}
	for(int j=range;j>=0;j--)
		while (!bin[j].IsEmpty())
		{
			bin[j].Delete(0, x);
			X.Insert(0, x);
		}
	delete[]bin;
}
#endif // !LIST_H