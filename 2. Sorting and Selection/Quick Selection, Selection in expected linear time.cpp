template<typename T>
int QS_partition(T a[], int p, int q)
{
	if (p == q)
		return p;
	int i = p;
	int j = p;
// to make this randomized version
/*	int k=Randomize(p,q);
	swap(a[k],a[q]);*/
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
T QuickSelect(T a[], int start, int end, int index)
{
	if (start == end)
		return a[start];
	int pos = QS_partition(a, start, end);
	int k = pos - start + 1;
	if (index == k)
		return a[pos];
	else if (k > index)
		return QuickSelect(a, start, pos - 1, index);
	else if (k < index)
		return QuickSelect(a, pos + 1, end, index - k);
}