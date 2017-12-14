template<typename T>
void Max_Heapify(T a[], int i, int size)
{
	int l, r, largest;

	while (2 * i + 1 < size)
	{
		l = 2 * i + 1;
		r = l + 1;
		largest = i;
		if (a[l] > a[i])
			largest = l;
		if (r<size && a[r]>a[largest])
			largest = r;
		if (largest == i)
			break;
		else
		{
			Swap(a[i], a[largest]);
			i = largest;
		}
	}
}

template<typename T>
void Max_Heapify(T a[], int size)
{
	for (int i = (size - 2) / 2; i >= 0; i--)
		Max_Heapify(a, i, size);
}

template<typename T>
void MaxHeapSort(T a[], int size)
{
	Max_Heapify(a, size);
	for (int i = size - 1; i > 0; i--)
	{
		Swap(a[i], a[0]);
		Max_Heapify(a, 0, i);
	}
}