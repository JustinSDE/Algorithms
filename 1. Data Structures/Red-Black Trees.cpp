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