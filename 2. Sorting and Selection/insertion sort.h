template<typename T>
void InsertionSort(T a[], int n)
{
	int j;
	for (int i = 1; i < n; i++)
	{
		j = i - 1;
		int key = a[i];
		while (j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
	return;
}
