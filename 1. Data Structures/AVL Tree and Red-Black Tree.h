#pragma once
#include <iostream>
#include <iomanip>
//AVL Tree
#ifndef AVLTREE_H
#define AVLTREE_H

//AVL tree node
template<typename T>
class AVLTreeNode
{
public:
	T key;
	int height;
	AVLTreeNode * left;
	AVLTreeNode * right;

	AVLTreeNode(T value, AVLTreeNode *l, AVLTreeNode *r) :key(value), height(0), left(l), right(r) {}
};

//AVL tree
template<class T>
class AVLTree
{
private:
	AVLTreeNode<T> *mRoot;  //AVL tree root
public:
	AVLTree();
	~AVLTree();

	//Get tree height
	int height();
	// get tree height
	int max(int a, int b);

	//Preorder of AVL
	void preOrder() const;
	//InOrder of AVL
	void inOrder() const;
	//postOrder of AVL
	void postOrder() const;

	// recursive serach of k in AVL
	AVLTreeNode<T>* search(T key);
	// non recursive serach of k in avl
	AVLTreeNode<T>* iterativeSearch(T key);

	//Find minimum
	T minimum();
	//Find maximum
	T maximum();

	// Insert key
	void insert(T key);

	//delete key
	void remove(T key);

	// destroy AVL tree;
	void destroy();

	//print AVL tree
	void print();

	// Get tree height (recursive)
	int height(AVLTreeNode<T>* tree);

	//PreOrder (recursive)
	void preOrder(AVLTreeNode<T> *tree) const;
	// InOrder(recursive)
	void inOrder(AVLTreeNode<T> *tree) const;
	//postOrder(recursive)
	void postOrder(AVLTreeNode<T> *tree) const;

	// find key
	AVLTreeNode<T>* search(AVLTreeNode<T> *x, T key) const;
	//find key
	AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* x, T key) const;

	//find minimum node
	AVLTreeNode<T>* minimum(AVLTreeNode<T> *tree);
	AVLTreeNode<T>* maximum(AVLTreeNode<T> *tree);

	//LL rotation
	AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T> *k2);

	//RR rotation
	AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T> *k2);

	//LR rotation
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T> *k2);

	//RL rotation

	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T> *k4);

	// Insert node z into avl tree
	AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key);

	//delete node z in AVL tree
	AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);

	// destroy tree
	void destroy(AVLTreeNode<T>* &tree);
	// print tree
	void print(AVLTreeNode<T>* tree, T key, int direction);
};

template<class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree)
{
	if (0 == tree)
		return 0;
	return tree->height;
}

template<class T>
int AVLTree<T>::height()
{
	return height(mRoot);
}

template<class T>
int AVLTree<T>::max(int a, int b)
{
	return a > b ? a : b;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T> *k2)
{
	AVLTreeNode<T>* k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;

	return k1;
}

/*
* RR：右右对应的情况(右单旋转)。
*
* 返回值：旋转后的根节点
*/
template <class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* k1)
{
	AVLTreeNode<T>* k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;

	return k2;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T> * k3)
{
	k3->left = rightRightRotation(k3->left);

	return leftLeftRotation(k3);
}

/*
* RL：右左对应的情况(右双旋转)。
*
* 返回值：旋转后的根节点
*/
template <class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* k1)
{
	k1->right = leftLeftRotation(k1->right);

	return rightRightRotation(k1);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key)
{
	if (nullptr ==tree)
	{
		tree = new AVLTreeNode<T>(key, nullptr, nullptr);
	}
	if (tree == nullptr)
	{
		std::cout << "Error: Create AVL tree Failed!!" << endl;
		return nullptr;
	}
	else if (key < tree->key)
	{
		tree->left = insert(tree->left, key);
		if (height(tree->left) - height(tree->right) == 2)
		{
			if (key < tree->left->key)
				tree = leftLeftRotation(tree);
			else
				tree = leftRightRotation(tree);
		}
	}
	else if (key > tree->key)
	{
		tree->right = insert(tree->right, key);
		if (height(tree->right) - height(tree -> left) == 2)
		{
			if (key > tree->right->key)
				tree = rightRightRotation(tree);
			else
				tree = rightLeftRotation(tree);
		}
	}
	else
	{
		std::cout << "Same Node exists! Insertion failed" << endl;
	}

	tree->height = max(height(tree->left), height(tree->right)) + 1;

	return tree;
}

template<class  T>
void AVLTree<T>::insert(T key)
{
	insert(mRoot, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z)
{
	if (tree == nullptr || z == nullptr)
		return nullptr;
	if (z->key < tree->key)
	{
		tree->left = remove(tree->left, z);
		if (height(tree->right) - height(tree->left) == 2)
		{
			AVLTreeNode<T> *r = tree->right;
			if (height(r->left) > height(r->right))
				tree = rightLeftRotation(tree);
			else tree = rightRightRotation(tree);
		}
	}
	else if (z->key > tree->key)
	{
		tree->right = remove(tree->right, z);
		if (height(tree->left) - height(tree->right) == 2)
		{
			AVLTreeNode<T> *l = tree->left;
			if (height(l->right) > height(l->left))
				tree = leftRightRotation(tree);
			else
				tree = leftLeftRotation(tree);
		}
	}
	else  // tree is the node to be removed
	{
		if ((tree->left != nullptr) && (tree->right != nullptr))
		{
			if (height(tree->left) > height(tree->right))
			{
				AVLTreeNode<T> *max = maximum(tree->left);
				tree->key = max->key;
				tree->left = remove(tree->left, max);
			}
			else
			{
				AVLTreeNode<T> *min = maximum(tree->right);
				tree->key = min->key;
				tree->right = remove(tree->right, min);
			}
		}
		else
		{
			AVLTreeNode<T> *tmp = tree;
			tree = (tree->left != nullptr) ? tree->left : tree->right;
			delete tmp;
		}
	}
	return tree;
}

template<class T>
void AVLTree<T>::remove(T key)
{
	AVLTreeNode<T>* z;
	if ((z = search(mRoot, key)) != nullptr)
		mRoot = remove(mRoot, z);
}

template<class T>
AVLTree<T>::AVLTree() :mRoot(nullptr)
{

}

template<class T>
AVLTree<T>::~AVLTree()
{
	destroy(mRoot);
}

template<class T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* tree) const
{
	if (tree != nullptr)
	{
		std::cout << tree->key << " ";
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

template<class T>
void AVLTree<T>::preOrder() const
{
	preOrder(mRoot);
}

template<class T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* tree) const
{
	if (tree != nullptr)
	{
		inOrder(tree->left);
		std::cout << tree->key << " ";
		inOrder(tree->right);
	}
}

template<class T>
void AVLTree<T>::inOrder() const
{
	inOrder(mRoot);
}

template<class T>
void AVLTree<T>::postOrder(AVLTreeNode<T> *tree) const
{
	if (tree != nullptr)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		std::cout << tree->key << " ";
	}
}

template<class T>
void AVLTree<T>::postOrder() const
{
	postOrder(mRoot);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* x, T key) const
{
	if (x == nullptr || x->key == key)
		return x;
	if (key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::search(T key)
{
	return search(mRoot, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(AVLTreeNode<T>* x, T key) const
{
	while ((x != nullptr) && (x->key != key))
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(T key)
{
	return iterativeSearch(mRoot, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree)
{
	if (tree == nullptr)
		return nullptr;
	while (tree->left != nullptr)
		tree = tree->left;
	return tree;
}

template<class T>
T AVLTree<T>::minimum()
{
	AVLTreeNode<T>* p = (AVLTreeNode<T>*) minimum(this->mRoot);
	if (p != nullptr)
		return p->key;
	return (T)nullptr;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
	if (tree == nullptr)
		return nullptr;
	while (tree->right != nullptr)
		tree = tree->right;
	return tree;
}

template<class T>
T AVLTree<T>::maximum()
{
	AVLTreeNode<T> *p = maximum(this->mRoot);
	if (p != nullptr)
		return p->key;
	return (T)nullptr;
}

template<class T>
void AVLTree<T>::destroy(AVLTreeNode<T>* &tree)
{
	if (nullptr == tree)
		return;
	if (nullptr != tree->left)
		destroy(tree->left);
	if (nullptr != tree->right)
		destroy(tree->right);
	delete tree;
}

template<class T>
void AVLTree<T>::destroy()
{
	destroy(mRoot);
}

template<class T>
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction)
{
	if (nullptr != tree)
	{
		if (0 == direction)
			std::cout << std::setw(2) << tree->key << " is root" << endl;
		else
			std::cout<<std::setw(2)<<tree->key<<" is "<<std::setw(2)<<key<<"'s"<<std::setw(12)<< (direction == 1 ? "right child" : "left child") << endl;
		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}

template<class T>
void AVLTree<T>::print()
{
	if (nullptr != mRoot)
		print(mRoot, mRoot->key, 0);
}


enum Color{red, black};

template<typename T>
class RBTreeNode
{
	friend class RBTree<T>;
private:
	RBTreeNode<T>* p, left, right;
	Color color;
	T key;
public:
	RBTreeNode(T value, RBTreeNode<T> *l=nullptr, RBTreeNode<T>* r=nullptr, RBTreeNode<T>* prev = nullptr, Color c=red):
		key(value), p(prev),left(l),right(r),color(c){}
};

template<typename T>
class RBTree
{
private:
	RBTreeNode<T>* root;
	int size;
public:
	void Left_Rotate(RBTreeNode<T>* x);  //maybe private
	void Right_Rotate(RBTreeNode<T>* x);
	RBTreeNode<T>* Search(T k, RBTreeNode<T>* x);
	RBTreeNode<T>* Search(T k);
	RBTreeNode<T>* Minimum(RBTreeNode<T> *x);
	RBTreeNode<T>* Maximum(RBTreeNode<T> *x);

	void Insert(RBTreeNode<T>* z);
	void Insert_Fixup(RBTreeNode<T> *z);
	void Transplant(RBTreeNode<T> *u, RBTreeNode<T> *v);
	void Delete(RBTreeNode<T>* z);
	void Delete_Fixup(RBTreeNode<T> *z);
};

template<typename T>
void RBTree<T>::Left_Rotate(RBTreeNode<T> *x)
{
	RBTreeNode<T> *y;
	y = x->right;
	x->right = y->left;
	if (y->left != nullptr)
		y->left->p = x;
	y->p = x->p;
	if (nullptr == x->p)
		root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

template<typename T>
void RBTree<T>::Right_Rotate(RBTreeNode<T> *y)
{
	RBTreeNode<T> *x = y->left;
	y->left = x->right;
	if (nullptr != x->right)
		x->right->p = y;

	x->p = y->p;

	if (y->p == nullptr)
		root = x;
	else if (y == y->p->left)
		y->p->left = x;
	else
		y->p->right = x;

	x->right = y;
	y->p = x;
}

template<typename T>
RBTreeNode<T>* RBTree<T>::Search(T k, RBTreeNode<T>* x)
{
	if (nullptr == x || x->key == k)
		return x;
	if (x->key < k)
		return Search(k, x->right);
	else
		return Search(k, x->left);
}

template<typename T>
RBTreeNode<T>* RBTree<T>::Search(T k)
{
	return Search(k, root);
}

template<typename T>
void RBTree<T>::Insert(RBTreeNode<T> *z)
{
	RBTreeNode<T> *y = nullptr, x = root;
	while (x != nullptr)            //find the position to insert the new key;
	{
		y = x;                       //use y to store the x before change in while loop;
		if (z->key == x->key)
			return;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	z->p = y;                          

	if (y == nullptr)
		root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->left = nullptr;
	z->right = nullptr;
	z->color = red;
	Insert_Fixup(z);
}

template<typename T>
void RBTree<T>::Insert_Fixup(RBTreeNode<T>* z)
{
	RBTreeNode<T>* y;
	while (z->p != nullptr && z->p->color == red)
	{
		if (z->p == z->p->p->left)
		{
			y = z->p->p->right;
			if (y->color == red)
			{
				z->p->color = black;
				y->color = black;
				z->p->p->color = red;
				z = z->p->p;
			}
			else if (z == z->p->right)
			{
				z = z->p;
				Left_Rotate(z);
			}
			else
			{
				z->p->color = black;
				z->p->p->color = red;
				Right_Rotate(z->p->p);
			}
		}
		else
		{
			y = z->p->p->left;
			if (y->color == red)
			{
				z->p->color = black;
				y->color = black;
				z->p->p->color = red;
				z = z->p->p;
			}
			else if (z == z->p->left)
			{
				z = z->p;
				Right_Rotate(z);
			}
			else
			{
				z->p->color = black;
				z->p->p->color = red;
				Left_Rotate(z->p->p);
			}
		}
	}

	root->color = black;
}

template<typename T>
void RBTree<T>::Transplant(RBTreeNode<T>* u, RBTreeNode<T> *v)
{
	if (u->p == nullptr)
		root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}

template<typename T>
RBTreeNode<T>* RBTree<T>::Minimum(RBTreeNode<T> *x)
{
	RBTreeNode<T>* temp = x;
	while (temp->left != nullptr)
		temp = temp->left;
	return temp;
}

template<typename T>
RBTreeNode<T>* RBTree<T>::Maximum(RBTreeNode<T> *x)
{
	RBTreeNode<T> * temp = x;
	while (temp->right != nullptr)
		temp = temp->right;
	return temp;
}

template<typename T>
void RBTree<T>::Delete(RBTreeNode<T> *z)
{
	RBTreeNode<T> *y = z, *x;
	Color y_original_color = y->color;
	if (z->left == nullptr)
	{
		x = z->right;
		Transplant(z, z->right);
	}
	else if (z->right == nullptr)
	{
		x = z->left;
		Transplant(z, z->left);
	}
	else
	{
		y = Minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->p == z)
			x->p = y;
		else
		{
			Transplant(y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		Transplant(z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	if (y_original_color == black)
		Delete_Fixup(x);
}

template<typename T>
void RBTree<T>::Delete_Fixup(RBTreeNode<T> *x)
{
	RBTreeNode<T> *w;
	while (x != root && black == x->color)
	{
		if (x == x->p->left)
		{
			w = x->p->right;
			if (red == w->color)
			{
				w->color = black;
				x->p->color = red;
				Left_Rotate(x->p);
				w = x->p->right;
			}

			if (black == w->left->color && black == w->right->color)
			{
				w->color = red;
				x = x->p;
			}
			else if (black == w->right->color)
			{
				w->left->color = black;
				w->color = red;
				Right_Rotate(w);
				w = x->p->right;
			}
			else
			{
				w->color = x->p->color;
				x->p->color = black;
				w->right->color = black;
				Left_Rotate(x->p);
				x = root;
			}
		}
		else
		{
			w = x->p->left;
			if (red == w->color)
			{
				w->color = black;
				x->p->color = red;
				Right_Rotate(x->p);
				w = x->p->left;
			}

			if (black == w->right->color && black == w->left->color)
			{
				w->color = red;
				x = x->p;
			}
			else if (black == w->left->color)
			{
				w->right->color = black;
				w->color = red;
				Left_Rotate(w);
				w = x->p->left;
			}
			else
			{
				w->color = x->p->color;
				x->p->color = black;
				w->left->color = black;
				Right_Rotate(x->p);
				x = root;
			}
		}
	}
	x->color = black;
}
#endif //...AVLTREE_H!