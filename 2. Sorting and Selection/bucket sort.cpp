/*bucket sort*/
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;
template<typename T>
void Bucket_Sort(T a[], int n, T min, T max, int buckets = 10)
{
	T gap = (max - min) / buckets;
	vector<T> *c = new vector<T>[buckets];
	int index;
	for (int i = 0; i < n; i++)
	{
		index = (a[i] - min) / gap;
		if (index >= buckets)
			index = buckets - 1;
		c[index].push_back(a[i]);
	}
	index = 0;
	int size;
	for (int i = 0; i < buckets; i++)
	{
		sort(c[i].begin(), c[i].end());
		size = c[i].size();
		for (int j = 0; j < size; j++)
		{
			a[index++] = c[i][j];
		}
	}
	delete[]c;
}

void main() {
	int a[300];
	int size = sizeof(a) / sizeof(*a);
	srand(time(nullptr));
	for (int i = 0; i < size; i++)
	{
		a[i] = rand() % 100;
	}
	Bucket_Sort(a, size, 0, 99, 10);
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << ' ';
		if (i % 20 == 19)
			cout << endl;
	}
		
}