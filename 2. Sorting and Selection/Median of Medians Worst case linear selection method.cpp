template<typename T>
void InsertionSort(T a[], int p, int q)               //insertion sort for a subarray
{
	int j;
	for (int i = p + 1; i <= q; i++)
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

template<typename T>
T Pick(T a[], int p, int q, int ith)   // using median of median method to pick the ith smallest element from the array
{
	if (q - p + 1 <= 5)
	{
		InsertionSort(a, p, q);
		return a[p + ith - 1];
	}
	int i = p + 0, j = p + 4;
	while (j <= q)
	{
		InsertionSort(a, j - 4, j);
		Swap(a[i], a[j - 2]);
		i++;
		j += 5;
	}
	j = j - 4;
	if (j <= q)
	{
		InsertionSort(a, j, q);
		Swap(a[i], a[j + (q - j) / 2]);
		i++;
	}
	i--;
	int newindex = (i - p + 1) / 2;
	T median = Pick(a, p, i, newindex);
	for (int k = p; k <= q; k++)
	{
		if (a[k] == median)
		{
			Swap(a[k], a[q]);
			break;
		}
	}
	int pos = QS_partition(a, p, q);
	if (pos - p + 1 == ith)
		return median;
	else if (pos - p + 1 > ith)
		return Pick(a, p, pos - 1, ith);
	else
		return Pick(a, pos + 1, q, ith + p - pos - 1);
}