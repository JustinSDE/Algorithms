#include <iostream>
#include <queue>
template<class T>
class BinaryTreeNode
{
	friend void Visit(BinaryTreeNode<T> *);
	friend void InOrder(BinaryTreeNode<T> *);
	friend void PreOrder(BinaryTreeNode<T> *);
	friend void PostOrder(BinaryTreeNode<T> *);
	friend void LevelOrder(BinaryTreeNode<T> *);
private:
	T data;
	BinaryTreeNode<T> *LeftChild, *RightChild;
public:
	BinaryTreeNode()
	{
		LeftChild = RightChild = 0;
	}
	BinaryTreeNode(const T& e)
	{
		data = e;
		LeftChild = RightChild = NULL;
	}
	BinaryTreeNode(const T& e, BinaryTreeNode *l, BinaryTreeNode *r)
	{
		data = e;
		LeftChild = l;
		RightChild = r;
	}
};

template<typename T>
void Visit(BinaryTreeNode<T> *t)
{
	std::cout << t->data;
}
template<typename T>
void PreOrder(BinaryTreeNode<T> *t)
{
	if (t)
	{
		Visit(t);
		PreOrder(t->LeftChild);
		PreOrder(t->RightChild);
	}
}

template<typename T>
void InOrder(BinaryTreeNode<T> *t)
{
	if (t)
	{
		InOrder(t->LeftChild);
		Visit(t);
		InOrder(t->RightChild);
	}
}

template<typename T>
void PostOrder(BinaryTreeNode<T> *t)
{
	if (t)
	{
		PostOrder(t->LeftChild);
		PostOrder(t->RightChild);
		Visit(t);
	}
}

template<typename T>
void LevelOrder(BinaryTreeNode<T> *t)
{
	std::queue<BinaryTreeNode<T>*> Q;
	while (t)
	{
		Visit(t);
		if (t->LeftChild) Q.push(t->LeftChild);
		if (t->RightChild) Q.push(t->RightChild);
		try {
			t = Q.front();
			Q.pop();
		}
		catch (...) { return; }
	}
}

template<typename T>
class BinaryTree
{
private:
	BinaryTreeNode<T> *root;
	void PreOrder(void(*Visit) (BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);
	void InOrder(void(*Visit) (BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);
	void PostOrder(void(*Visit) (BinaryTreeNode<T> *u), BinaryTreeNode<T> *t);
	int Height(BinaryTreeNode<T> *t) const;
public:
	BinaryTree() { root = NULL; }
	~BinaryTree() {};
	bool IsEmpty() const
	{
		return root ? false : true;
	}
	bool Root(T& x) const;
	void MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right);
	void BreakTree(T& element, BinaryTree<T>& left, BinaryTree<T>& right);
	void PreOrder(void(*Visit)(BinaryTreeNode<T>* u))
	{
		PreOrder(Visit, root);
	}
	void InOrder(void(*Visit)(BinaryTreeNode<T>* u))
	{
		InOrder(Visit, root);
	}
	void PostOrder(void(*Visit)(BinartyTreeNode<T>* u))
	{
		PostOrder(Visit, root);
	}
	//	void LevelOrder(void(*Visit)(BinaryTreeNode<T>* u));
	int Height() const;
};

template<typename T>
bool BinaryTree<T>::Root(T& x) const
{
	if (root)
	{
		x = root->data;
		return true;
	}
	else return false;
}

template<typename T>
void BinaryTree<T>::MakeTree(const T& element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	root = new BinaryTreeNode<T>(element, left.root, right.root);
	left.root = right.root = 0;
}

template<typename T>
void BinaryTree<T>::BreakTree(T& element, BinaryTree<T>& left, BinaryTree<T>& right)
{
	if (!root) throw OutOfBounds();
	element = root->data;
	left.root = root->LeftChild;
	right.root = root->RightChild;
	delete root;
	root = 0;
}

template<class T>
void BinaryTree<T>::PreOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T> *t)
{
	if (t)
	{
		Visit(t);
		PreOrder(Visit, t->LeftChild);
		PreOrder(Visit, t->RightChild);
	}
}

template<class T>
void BinaryTree<T>::InOrder(void(*Visit)(BinaryTreeNode<T>* u), BinaryTreeNode<T> *t)
{
	if (t)
	{
		InOrder(Visit, t->LeftChild);
		Visit(t);
		InOrder(Visit, t->RightChild);
	}
}

template<class T>
void BinaryTree<T>::PostOrder(void(*Visit)(BinaryTreeNode<T> *u), BinaryTreeNode<T> *t)
{
	if (t)
	{
		PostOrder(Visit, t->LeftChild);
		PostOrder(Visit, t->RightChild);
		Visit(t);
	}
}

template<class T>
int BinaryTree<T>::Height(BinaryTreeNode<T> *t) const
{
	if (!t)
		return 0;
	int hl = Height(t->LeftChild);
	int rl = Height(t->RightChild);
	if (hl > hr) return ++hl;
	else return ++hr;
}

template<class T>
int BinaryTree<T>::Height() const
{
	return Height(root);
}