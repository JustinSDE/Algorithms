/*stack*/

template<typename T>
class Stack
{
private:
	int max_size;
	T *element;
	int top;
public:
	Stack(int size_max = 10) :max_size(size_max), top(-1)
	{
		element = new T[max_size];
	}
	~Stack() { delete[]element; }
	void Push(const T& value) {
		if (top >= max_size - 1)
			throw "stack already full";
		element[++top] = value;}
	void Pop(T & value)
	{
		if (top < 0) throw "stack already empty";
		value = element[top--];
	}
	const T& Pop() 
	{
		if (top < 0) throw "stack already empty";
		top--; return element[top + 1];
	}
	bool Empty() { return top<0; }
};


/*queues*/
template<typename T>
class Queue
{
private:
	int head;
	int tail;
	int max_size;
	T* element;
public:
	Queue(int size_max) :head(0), tail(1), max_size(size_max)
	{
		element = new T[size_max];
	}
	~Queue() { delete[]element; }
	void Enqueue(const T& value) { if (tail == head) throw "Queue is full";
	element[tail] = value;
	tail = (tail + 1) % max_size;
	}
	const T& Dequeue()
	{
		if ((head + 1) % max_size == tail)
			throw "Queue is empty";
		tail = (tail - 1) % max_size;
		return element[tail];
	}
	void Dequeue(T & value)
	{
		if ((head + 1) % max_size == tail)
			throw "Queue is empty";
		tail = (tail - 1) % max_size;
		value=element[tail];
	}
	bool Empty() const
	{
		return (head + 1) % max_size == tail;
	}
};

/*double linked list*/
template<typename T>
class DList
{
	class DListNode
	{
		friend DList;
	private:
		T value;
		DListNode *prev;
		DListNode *next;
	public:
		DListNode(const T& x=T(0), DListNode* p=nullptr, DListNode* n=nullptr)
			:value(x), prev(p),next(n){}
	};
private:
	DListNode *head;
	DListNode *tail;
public:
	DList() {
		head = new DListNode;
		tail = new DListNode;
		head->next = tail;
		tail->prev = head;
	}
	~DList()
	{
		delete head;
		delete tail;
	}
	bool Empty() const { return head->nex == tail; }
	
};