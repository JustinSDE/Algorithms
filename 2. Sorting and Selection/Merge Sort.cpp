template<typename T>
void MergeSort(T a[], int start, int end)
{
	if (start == end)                   // End of recursive call
		return;

	int pos = (start + end) / 2;        // Recursive call
	MergeSort(a, start, pos);
	MergeSort(a, pos + 1, end);
	//copy two parts into two diferent arrays
	int size1 = pos - start + 1, size2 = end - pos;
	T* temp1 = new T[size1];
	for (int i = 0; i < size1; i++)
		temp1[i] = a[start + i];
	T* temp2 = new T[size2];
	for (int i = 0; i < size2; i++)
		temp2[i] = a[pos + 1 + i];
	// merge two separate parts
	int index1 = 0, index2 = 0, index3 = start + 0;
	while (index1 < size1 && index2 < size2)
	{
		if (temp1[index1] > temp2[index2])
		{
			a[index3++] = temp2[index2++];
		}
		else
		{
			a[index3++] = temp1[index1++];
		}
	}
	for (; index1 < size1; index1++)
	{
		a[index3++] = temp1[index1];
	}
	for (; index2 < size2; index2++)
	{
		a[index3++] = temp2[index2];
	}
	//delete new allocated spaces
	delete[]temp1;
	delete[]temp2;

	return;
}

template<typename T>
void MergeSort(T a[], int size)
{
	MergeSort(a, 0, size - 1);
}