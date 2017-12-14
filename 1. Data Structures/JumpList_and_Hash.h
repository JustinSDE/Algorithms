#pragma once
#include "errors.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
template<class E, class K>
class SortedChainNode
{
	friend class SortedChain<E, K>;
private:
	E data;
	SortedChainNode* link;
};

template<class E, class K>
class SortedChain {
private:
	SortedChainNode<E, K>* first;
public:
	SortedChain() { first = NULL; }
//	~SortedChain()();
	bool IsEmpty() const { return first == 0; }
//	int Length() const;
	bool Search(const K &k, E& e) const;
	SortedChain<E, K>& Delete(const K&k, E& e);
//	SortedChain<E, K>& Insert(const E& e);
	SortedChain<E, K>& DistinctInsert(const E& e);
};

template<class E, class K>
bool SortedChain<E, K>::Search(const K& k, E& e) const
{
	SortedChainNode<E, K>* p = first;
	for (; p && p->data < k; p = p->link);
	if (p&&p->data == k)
	{
		e = p->data;
		return true;
	}
	return false;
}

template<class E, class K>
SortedChain<E, K>& SortedChain<E, K>::Delete(const K& k, E& e)
{
	SortedChainNode<E, K> * p = first, *tp = 0;
	for (; p&&p->data < k; tp = p, p = p->link);
	if (p&& p->data == k)
	{
		e = p->data;
		if (tp)
			tp->link = p->link;
		else
			first = p->link;
		delete p;
		return *this;
	}
	throw OutOfBounds();
}

template<class E, class K>
SortedChain<E, K>& SortedChain<E, K>::DistinctInsert(const E& e)
{
	SortedChainNode<E, K>* p = first, *tp = NULL;
	for (; p&&p->data < e; tp = p, p = p->link);
	if (p&&p->data == e) throw OutOfBounds();
	SortedChainNode<E, K> *q = new SortedChainNode<E, K>;
	q->data = e;
	q->link = p;
	if (tp) tp->link = q;
	else first = q;
	return *this;
}

template<class E, class K>
class SkipNode {
	friend class SkipList<E, K>;
private:
	SkipNode(int size)
	{
		link = new SkipNode<E, K> *[size];
	}
	~SkipNode() { delete[]link; }
	E data;
	SkipNode<E, K> **link;
};

template<class E, class K>
class SkipList {
private:
	int Level();
	SkipNode<E, K>* SaveSearch(const K& k);
	int MaxLevel;
	int Levels;
	int CutOff;
	K TailKey;
	SkipNode<E, K> *head;
	SkipNode<E, K>* tail;
	SkipNode<E, K> **last;
public:
	SkipList(K Large, int MaxE = 10000, float p = 0.5);
	~SkipList();
	bool Search(const K& k, E& e) const;
	SkipList<E, K>& Insert(const E& e);
	SkipList<E, K>& Delete(const K& k, E& e);
};

template<class E, class K>
SkipList<E, K>::SkipList(K Large, int MaxE, float p)
{
	CutOff = p*RAND_MAX;
	MaxLevel = ceil(log(maxE) / log(1 / p)) - 1;
	TailKey = Large;
	srand(time(0));
	Levels = 0;

	head = new SkipNode<E, K>(MaxLevel + 1);
	tail = new SkipNode<E, K>(0);
	last = new SkipNode<E, K>*[MaxLevel + 1];
	tail->data = Large;

	for (int i = 0; i <= MaxLevel; i++)
		head->link[i] = tail;
}

template<class E, class K>
SkipList<E, K>::~SkipList()
{
	SkipNode<E, K> *next;
	while (head != tail)
	{
		next = head->link[0];
		delete head;
		head = next;
	}
	delete tail;
	delete[]last;
}

template<class E, class K>
bool SkipList<E, K>::Search(const K& k, E& e) const
{
	if (k >= TailKey) return false;
	SkipNode<E, K>* p = head;
	for (int i = Levels; i >= 0; i--)
		while (p->link[i]->data < k)
			p = p->link[i];
	e = p->link[0]->data;
	return (e == k);
}

template<class E, class K>
SkipNode<E, K>* SkipList<E, K>::SaveSearch(const K& k)
{
	SkipNode<E, K>*p = head;
	for (int i = Levels; i >= 0; i--)
	{
		while (p->link[i]->data < k)
			p = p->link[i];
		last[i] = p;
	}
	return (p->link[0]);
}

template<class E,class K>
int SkipList<E, K>::Level()
{
	int lev = 0;
	while (rand() <= CutOff)
		lev++;
	return (lev <= MaxLevel) ? lev : MaxLevel;
}

template<class E, class K>
SkipList<E, K>& SkipList<E, K>::Insert(const E& e)
{
	K k = e;
	if (k >= TailKey) throw OutOfBounds();
	SkipNode<E, K>* p = SaveSerach(k);
	if (p->data == e) throw OutOfBounds();
	int lev = Level();
	if (lev > Levels) 
	{
		lev = ++Levels; 
		last[lev] = head;
	}
	SkipNode<E, K> * y = new SkipNode<E, K>(lev + 1);
	y->data = e;
	for (int i = 0; i <= lev; i++)
	{
		y->link[i] = last[i]->link[i];
		last[i]->link[i] = y;
	}
	return *this;
}

template<class E, class K>
SkipList<E, K>& SkipList<E, K>::Delete(const K& k, E& e)
{
	if (K >= TailKey) throw OutOfBounds();

	SkipNode<E, K> *p = SaveSearch(k);
	if (p->data != k) throw OutOfBounds();
	for (int i = 0; i <= Levels && last[i]->link[i] == p; i++)
		last[i]->link[i] = p->link[i];
	while (Levels > 0 && head->link[Levels] == tail)
		Levels--;
	e = p->data;
	delete p;
	return *this;
}

class element {
private:
	int data;
	long key;
public:
	operator long() const { return key; }
	element& operator=(long y)
	{
		key = y;
		return *this;
	}
};

template<class E, class K>
class HashTable
{
private:
	int hSearch(const K& k) const;
	int D;
	E *ht;
	bool *empty;
public:
	HashTable(int divisor = 11);
	~HashTable()
	{
		delete[]dt;
		delete[]empty;
	}
	bool Search(const K& k, E& e) const;
	HashTable<E, K>& Insert(const E& e);
};

template<class E, class K>
HashTable<E, K>::HashTable(int divisor)
{
	D = divisor;
	ht = new E[D];
	empty = new bool[D];
	for (int i = 0; i < D; i++)
		empty[i] = true;
}

template<class E, class K>
int HashTable<E, K>::hSearch(const K& k) const
{
	int i = k%D;
	int j = i;
	do {
		if (empty[j] || ht[j] == k) return j;
		j = (j + 1) % D;
	} while (j != i);
	return j;
}

template<class E, class K>
bool HashTable<E, K>::Search(const K& k, E& e) const
{
	int b = hSearch(k);
	if (empty[b] || ht[b] != k) return false;
	e = ht[b];
	return true;
}

template<class E, class K>
HashTable<E, K>& HashTable<E, K>::Insert(const E& e)
{
	K k = e;
	int b = hSearch(k);
	if (empty[b])
	{
		empty[b] = false;
		ht[b] = e;
		return *this;
	}
	if (ht[b] == k)
		throw OutOfBounds();
	throw NoMem();
}


