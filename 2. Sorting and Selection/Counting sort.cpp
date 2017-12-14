/*couting sort, which makes it stable*/
template<typename T>
void Counting_Sort(T a[], int n, int k)
{
	int *c = new int[k];
	for (int i = 0; i < k; i++)
		c[i] = 0;
	T *b = new T[n];
	for (int i = 0; i < n; i++)
		c[a[i]]++;
	for (int i = 1; i < k; i++)
		c[i] = c[i] + c[i - 1];
	for (int j = n - 1; j >= 0; j--)
	{
		b[c[a[j]]-1] = a[j];
		c[a[j]]--;
	}
	for (int i = 0; i < n; i++)
		a[i] = b[i];
	delete[]c;
	delete[]b;
}

#include <iostream>

using namespace std;

int a[] = { 9,3,6,2,7,5,8,1,4,0 };
int n = 10;
void main()
{
	Counting_Sort(a, 10, 10);
	for (int i = 0; i < 10; i++)
		cout << a[i] << ' ';
}