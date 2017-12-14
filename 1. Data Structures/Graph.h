#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "errors.h"
#include "Queue.h"
#include "List.h"
template<typename T>
class AdjacencyWDigraph
{
protected:
	T NoEdge;
	int n;
	int e;
	T **a;
public:
	AdjacencyWDigraph(int Vertices = 10, T noEdge = 0);
	~AdjacencyWDigraph() { Delete2DArray(a, n + 1); }
	bool Exist(int i, int j) const;
	int Edges() const { return e; }
	int Vertices() const { reutrn n; }
	AdjacencyWDigraph<T>& Add(int i, int j, const T& w);
	AdjacencyWDigraph<T>& Delete(int i, int j);
	int OutDegree(int i) const;
	int InDegree(int i) const;
};

template<class T>
AdjacencyWDigraph<T>::AdjacencyWDigraph(int Vertices, T noEdge)
{
	n = Vertices;
	e = 0;
	NoEdge = noEdge;
	Make2DArray(a, n + 1, n + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] = NoEdge;
}

template<typename T>
bool AdjacencyWDigraph<T>::Exist(int i, int j) const
{
	if (i<1 || j<1 || i>n || j>n || a[i][j] == NoEdge) return false;
	return true;
}

template<class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph<T>::Add(int i, int j, const T& w)
{
	if (i<1 || j<1 || i>n || j>n||i==j||a[i][j]!=NoEdge)
		throw OutOfBounds();
	a[i][j] = w;
	e++;
	return *this;
}

template<class T>
AdjacencyWDigraph<T>& AdjacencyWDigraph<T>::Delete(int i, int j)
{
	if (i<1 || j<1 || i>n || j>n || a[i][j] == NoEdge)
		throw OutOfBounds();
	a[i][j] = NoEdge;
	e--;
	return *this;
}

template<typename T>
int AdjacencyWDigraph<T>::OutDegree(int i) const
{
	if (i<1 || i>n)
		throw OutOfBounds();
	int sum = 0;
	for (int j = 1; j <= n; j++)
		if (a[i][j] != NoEdge) sum++;
	return sum;
}

template<typename T>
int AdjacencyWDigraph<T>::InDegree(int i) const
{
	if (i<1 || i>n)
		throw OutOfBounds();
	int sum = 0;
	for (int j = 1; j <= n; j++)
		if (a[j][i] != NoEdge) sum++;
	return sum;
}

template<typename T>
class AdjacencyWGraph :public AdjacencyWDigraph<T>
{
public:
	AdjacencyWGraph(int Vertices = 10, T noEdge = 0) :AdjacencyWDigraph<T>(Vertices, noEdge) {}
	AdjacencyWGraph<T>& Add(int i, int j, const T& w)
	{
		AdjacencyWDigraph<T>::Add(i, j, w);
		a[j][i] = w;
		return *this;
	}
	AdjacencyWGraph<T>& Delete(int i, int j)
	{
		AdjacencyWDigraph<T>::Delete(i, j);
		a[j][i] = NoEdge;
		return *this;
	}
	int Degree(int i) const { return OutDegree(i); }
};

class AdjacencyDigraph:public AdjacencyWDigraph<int>
{
public:
	AdjacencyDigraph(int Vertices=10):AdjacencyWDigraph<int>(Vertices,0){}
	AdjacencyDigraph& Add(int i, int j)
	{
		AdjacencyWDigraph<int>::Add(i, j, 1);
		return *this;
	}
	AdjacencyDigraph& Delete(int i, int j)
	{
		AdjacencyWDigraph<int>::Delete(i, j);
		return *this;
	}
};

class AdjacencyGraph : public AdjacencyWGraph<int>
{
public:
	AdjacencyGraph(int Vertices = 10) :AdjacencyWGraph<int>(Vertices, 0) {}
	AdjacencyGraph& Add(int i, int j)
	{
		AdjacencyWGraph<int>::Add(i, j, 1);
		return *this;
	}
	AdjacencyGraph& Delete(int i, int j)
	{
		AdjacencyWGraph<int>::Delete(i, j);
		return *this;
	}
};

template<typename T>
class LinkedBase
{
protected:
	int n;
	int e;
	Chain<T> *h;
public:
	LinkedBase(int Vertices = 10)
	{
		n = Vertices;
		e = 0;
		h = new Chain<T>[n + 1];
	}
	~LinkedBase()
	{
		delete[]h;
	}
	int Edges() const
	{
		return e;
	}
	int Vertices() const
	{
		return n;
	}
	int OutDegree(int i) const
	{
		if (i<1 || i>n)
			throw OutOfBounds();
		return h[i].Lenghth();
	}
};

class LinkedDigraph :public LinkedBase<int>
{
public:
	LinkedDigraph(int Vertices=10) :LinkedBase<int> (Vertices){}
	bool Exist(int i, int j) const;
	LinkedDigraph& Add(int i, int j);
	LinkedDigraph& Delete(int i, int j);
	int InDegree(int i) const;
protected:
	LinkedDigraph& AddNoCheck(int i, int j);
};

bool LinkedDigraph::Exist(int i, int j) const
{
	if (i<1 || i>n) throw OutOfBounds();
	return (h[i].Search(j)) ? true : false;
}

LinkedDigraph& LinkedDigraph::Add(int i, int j)
{
	if (i<1 || j<1 || i>n || j>n || i == j || Exist(i, j))
		throw OutOfBounds();
	return AddNoCheck(i, j);
}

LinkedDigraph& LinkedDigraph::AddNoCheck(int i, int j)
{
	h[i].Insert(0, j);
	e++;
	return *this;
}

LinkedDigraph& LinkedDigraph::Delete(int i, int j)
{
	if (i<1 || i>n)
		throw OutOfBounds();
	h[i].Delete(j);
	e--;
	return *this;
}

int LinkedDigraph::InDegree(int i) const
{
	if (i<1 || i>n)
		throw OutOfBounds();
	int sum = 0;
	for (int j = 1; j <= n; j++)
		if (h[j].Search(i)) sum++;
	return sum;
}

class LinkedGraph : public LinkedDigraph
{
protected:
	LinkedGraph& AddNoCheck(int i, int j);
public:
	LinkedGraph(int Vertices=10):LinkedDigraph(Vertices){}
	LinkedGraph& Add(int i, int j);
	LinkedGraph& Delete(int i, int j);
	int Degree(int i) const { return LinkedDigraph::InDegree(i); }
	int OutDegree(int i) const { return LinkedDigraph::InDegree(i); }
};

LinkedGraph&  LinkedGraph::Add(int i, int j)
{
	if (i<1 || j<1 || i>n || j>n || i == j || Exist(i, j)) throw OutOfBounds();
	return AddNoCheck(i, j);
}

LinkedGraph& LinkedGraph::AddNoCheck(int i, int j)
{
	h[i].Insert(0, j);
	try { h[j].Insert(0, i); }
	catch (...) { h[i].Delete(j); throw; }
	e++;
	return *this;
}

LinkedGraph& LinkedGraph::Delete(int i, int j)
{
	LinkedDigraph::Delete(i, j);
	e++;
	LinkedDigraph::Delete(j, i);
	return *this;
}

template<class T>
class GraphNode
{
	friend LinkedWDigraph<T>;
	friend LinkedWGraph<T>;
	friend Chain<T>;
private:
	int vertex;
	T weight;
public:
	int operator!=(GraphNode y) const
	{
		return vertex != y.vertex;
	}
	bool operator==(GraphNode y) const
	{
		return vertex==y.vertex;
	}
	void Output(std::ostream& out) const
	{
		out << vertex << ' ' << weight << ' ';
	}
	

};

template<class T>
class LinkedWDigraph :public LinkedBase<GraphNode<T>>
{
protected:
	LinkedWDigraph<T>& AddNoCheck(int i, int j, const T& w);
public:
	LinkedDigraph(int Vertices=10):LinkedBase<GraphNode<T>>(Vertices){}
	bool Exist(int i, int j) const;
	LinkedWDigraph<T>& Add(int i, int j, const T& w);
	LinkedWDigraph<T>& Delete(int i, int j);
	int InDegree(int i) const;
};

template<class T>
bool LinkedWDigraph<T>::Exist(int i, int j) const
{
	if (i<1 || i>n) throw OutOfBounds();
	GraphNode<T> x;
	x.vertex = j;
	return h[i].Search(x);
}

template<class T>
LinkedWDigraph<T>& LinkedWDigraph<T>::Add(int i, int j, const T& w)
{
	if (i<1 || j<1 || i>n || j>n || i == j || Exist(i, j))
		throw OutOfBounds();
	return AddNoCheck(i, j, w);
}


template<class T>
LinkedWDigraph<T>& LinkedWDigraph<T>::AddNoCheck(int i, int j, const T& w)
{
	GraphNode<T> x;
	x.vertex = j;
	x.weight = w;
	h[i].Insert(0, x);
	e++;
	return *this;
}

template<class T>
LinkedWDigraph<T>& LinkedWDigraph<T>::Delete(int i, int j)
{
	if (i<1 || i>n)
		throw OutOfBounds();
	GraphNode<T> x;
	x.vertex = j;
	h[i].Delete(x);
	e--;
	return *this;
}

template<typename T>
int LinkedWDigraph<T>::InDegree(int i) const
{
	if (i<1 || i>n) throw OutOfBounds();
	int sum = 0;
	GraphNode<T> x;
	x.vertex = i;
	for (int j = 1; j <= n; j++)
		if (h[i].Search(x)) sum++;
	return sum;
}

template<class T>
ostream& operator<<(ostream& out, GraphNode<T> x)
{
	x.Output(out); return out;
}


class NetWork
{
public:
	virtual int Begin(int i) = 0;
	virtual int NextVertex(int i) = 0;
	virtual void InitializePos() = 0;
	virtual void DeactivatePos() = 0;
	void BSF(int v, int reach[], int label);
	void DSF(int v, int reach[], int label);
	void dfs(int v, int reach[], int label);
	bool NetWork::Topological(int v[]);
};

void NetWork::BSF(int v, int reach[], int label)
{
	LinkedQueue<int> Q;
	InitializePos();
	reach[v] = label;
	Q.Add(v);
	while (!Q.IsEmpty())
	{
		int w;
		Q.Delete(w);
		int u = Begin(w);
		while (u)
		{
			if (!reach[u]) {
				Q.Add(u);
				reach[u] = label;
			}
			u = NextVertex(w);
		}
	}
	DeactivatePos();
}

void NetWork::DSF(int v, int reach[], int label)
{
	InitializePos();
	dfs(v, reach, label);
	DeactivatePos();
}

void NetWork::dfs(int v, int reach[], int label)
{
	reach[v] = label;
	int u = Begin(v);
	while (u)
	{
		if (!reach[u]) dfs(u, reach, label);
		u = NextVertex(v);
	}
}

bool NetWork::Topological(int v[])
{
	int n = Vertices();

	int *InDegree = new int[n + 1];
	InitializePos();
	for (int i = 1; i <= n; i++)
		InDegree[i] = 0;
	for (int i = 1; i <= n; i++)
	{
		int u = Begin(i);
		while (u)
		{
			InDegree[u]++;
			u = NextVertex(i);
		}
	}

	LinkedStack<int> S;
	for (int i = 1; i <= n; i++)
		if (!InDegree[i]) S.Add(i);

	i = 0;
	while (!S.IsEmpty())
	{
		int w;
		S.Delete(w);
		v[i++] = w;
		int u = Begin(w);
		while (u)
		{
			InDegree[u]--;
			if (!InDegree[u]) S.Add(u);
			u = NextVertex(w);
		}
	}
	DeactivatePos();
	delete[]InDegree;
	return (i == n);
}
#endif // !GRAPH_H
