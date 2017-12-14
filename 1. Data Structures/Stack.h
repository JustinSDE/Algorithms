#pragma once
#include "errors.h"
 template<class T>
 class Stack {
 private:
	 int top;   //栈顶
	 int MaxTop; //最大的栈顶值 
	 T* stack; //栈元素数组
 public:
	 Stack(int MaxStackSize = 10);
	 ~Stack() { delete[]stack; }
	 bool IsEmpty() const {return top==-1}
	 bool IsFull() const { return top == MaxTop; }
	 T Top() const;
	 Stack<T>& Add(const T& x);
	 Stack<T>& Delete(T& x);
 };

 template<class T>
 Stack<T>::Stack(int MaxStackSize)
 {
	 MaxTop = MaxStackSize-1;
	 stack = new T[MaxStackSize];
	 top = -1;
 }

 template<class T>
 T Stack<T>::Top() const
 {
	 if (top == -1)
		 throw OutOfBounds();
	 else
		 return stack[top];
 }

 template<class T>
 Stack<T>& Stack<T>::Add(const T&x)
 {
	 if (IsFull())
		 throw NoMem();
	 stack[++top] = x;
	 return *this;
 }

 template<class T>
 Stack<T>& Stack<T>::Delete(T& x)
 {
	 if (IsEmpty())
		 throw OutOfBounds();
	 x = stack[top--];
	 return *this;
 }

 template<class T>
 class Node {
	 friend Linkedstack<T>;
	 friend LinkedQueue<T>;
 private:
	 T data;
	 Node<T>* link;
 };

 template<class T>
 class LinkedStack
 {
 private:
	 Node<T>* top;
 public:
	 LinkedStack() { top = NULL; }
	 ~LinkedStack();
	 bool IsEmpty() const { return top == NULL; }
	 bool IsFull() const;
	 T Top() const;
	 LinkedStack<T>& Add(const T&x);
	 LinkedStack<T>& Delete(T& x);
 };

 template<class T>
 LinkedStack<T>::~LinkedStack()
 {
	 Node<T>* next;
	 while (top != NULL)
	 {
		 next = top->link;
		 delete top;
		 top = next;
	 }
 }

 template<class T>
 bool LinkedStack<T>::IsFull() const
 {
	 try {
		 Node<T> *p = new Node<T>;
		 delete p;
		 return false;
	 }
	 catch (NoMem)
	 {
		 return true;
	 }
 }

 template<class T>
 T LinkedStack<T>::Top() const
 {
	 if (IsEmpty()) throw OutOfBounds();
	 return top->data;
 }

 template<class T>
 LinkedStack<T> & LinkedStack<T>::Add(const T& x)
 {
	 Node<T>* p = new Node<T>;
	 p->data = x;
	 p->link = top;
	 top = p;
	 return *this;
 }

 template<class T>
 LinkedStack<T>& LinkedStack<T>::Delete(T& x)
 {
	 if (IsEmpty())
		 throw OutOfBounds();
	 x = top->data;
	 Node<T>* temp = top;
	 top = top->link;
	 delete temp;
	 return *this;
 }