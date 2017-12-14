template<typename T>
int QS_partition(T a[], int p, int q)
{
	if (p == q)
		return p;
	int i = p;
	int j = p;
	for (j; j < q; j++)
	{
		if (a[j] < a[q])
		{
			Swap(a[i], a[j]);
			i++;
		}
	}
	Swap(a[q], a[i]);
	return i;
}

template<typename T>
void QuickSort(T a[], int p, int q)
{
	int pos;
	if (p < q)
	{
		pos = QS_partition(a, p, q);
		QuickSort(a, p, pos - 1);
		QuickSort(a, pos + 1, q);
	}
}

template<typename T>
void QuickSort(T a[], int sz)
{
	QuickSort(a, 0, sz - 1);
}