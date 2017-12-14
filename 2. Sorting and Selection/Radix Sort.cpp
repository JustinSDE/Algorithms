/*radix sort, used to sort integers*/
#include <iostream>

class Radix_Sort_Element
{
	friend void Radix_Sort(int a[], int n, int digits, int base = 10);
private:
	int base;
	int digits;
	int *data;
public:
	Radix_Sort_Element() { data = nullptr, base = 0; digits = 0; }
	~Radix_Sort_Element() { delete[]data; }
	void initialize(int d, int b = 10) 
	{ digits = d; base = b; data = new int[d]; }
	operator int() const;
	void Convert(int value);
	void Print(std::ostream& out) const;
	Radix_Sort_Element& operator=(const Radix_Sort_Element & v);
	Radix_Sort_Element& operator=(int value)
	{
		Convert(value);
		return *this;
	}
};

Radix_Sort_Element:: operator int() const
{
	int res=0;
	for (int i = 0; i < digits; i++)
		res = res*base + data[i];
	return res;
}
void Radix_Sort_Element::Convert(int value)
{
	for (int i = digits - 1; i >= 0; i--)
	{
		data[i] = value%base;
		value = value / base;
	}
}

void Radix_Sort_Element::Print(std::ostream& out) const
{
	out << '(';
	for (int i = 0; i < digits-1; i++)
	{
		out << data[i] << ',';
	}
	out << data[digits-1]<<')';
}

std::ostream& operator<<(std::ostream& os, Radix_Sort_Element v)
{
	v.Print(os);
	return os;
}

Radix_Sort_Element& Radix_Sort_Element::operator =(const Radix_Sort_Element & v)
{
	if (this == &v)
		return *this;
	for (int i = 0; i < digits; i++)
		data[i] = v.data[i];
	return *this;
}

void Radix_Sort(int a[], int n, int digits, int base)
{
	Radix_Sort_Element *b = new Radix_Sort_Element[n];
	Radix_Sort_Element *d = new Radix_Sort_Element[n];
	for (int i = 0; i < n; i++)
	{
		b[i].initialize(digits, base);
		d[i].initialize(digits, base);
		b[i] = a[i];
	}
	int *c = new int[base];
	for (int k = digits - 1; k >= 0; k--)
	{
		for (int i = 0; i < base; i++)
			c[i] = 0;
		for (int j = 0; j < n; j++)
			c[b[j].data[k]]++;
		for (int i = 1; i < base; i++)
			c[i] = c[i] + c[i-1];
		for (int j = n - 1; j >= 0; j--)
		{
			d[c[b[j].data[k]] - 1] = b[j];
			c[b[j].data[k]]--;
		}
		for (int j = 0; j < n; j++)
			b[j] = d[j];
	}
	for (int i = 0; i < n; i++)
		a[i] = b[i];
	delete[]b;
	delete[]d;
	delete[]c;
}
using namespace std;


void main()
{
	int a[] = { 765,453,236,798,776,774,895,795,462,354,563,987 };
	int size = sizeof(a) / sizeof(*a);
	for (int i = 0; i < size; i++)
		cout << a[i] << ' ';
	cout << endl;

	Radix_Sort(a, size, 3, 10);
	for (int i = 0; i < size; i++)
		cout << a[i] << ' ';
	cout << endl;
}