/*brute method
just try every possible subarrays and solve it
this will take O(n^3)*/

template<typename T>
T maximum_subarray_brute(T a[], int n, int& start, int& end)
{
	T max = a[0], sum;   //initialzie with the first value;
	start = 0;
	end = 0;

	for(int i=0;i<n;i++)
		for (int j = i; j < n; j++)
		{
			sum = 0;
			for (int k = i; k <= j; k++)
				sum += a[k];
			if (sum > max)
			{
				start = i;
				end = j;
				max = sum;
			}
		}
	return max;
}

/*in the brute method, the calculation of sum takes too many time, therefore the method can 
be improved to O(n^2) by reducing unnecessary sums by calculate culumative values
the sum(i,j)=c(j)-c(i)*/

template<typename T>
T maximum_subarray_dp(T a[], int n, int & start, int& end)
{
	T *c = new T[n + 1];
	c[1] = 0;
	for (int i = 0; i < n; i++)
		c[i + 1] = c[i] + a[i];
	T max = a[1], sum;
	for(int i=1;i<n+1;i++)
		for (int j = i; j < n + 1; j++)
		{
			sum = c[j] - c[i - 1];
			if (sum > max)
			{
				max = sum;
				start = i - 1;
				end = j - 1;
			}
		}
	return max;
}

/*divide and conquer method, divide the array into two part, 
the maximum subarray must be the at left part, right part,
or cross the middle*/
template<typename T>
struct subarray_class
{
	T sum;
	int left;
	int right;
public:
	subarray_class(T value=0, int start=0, int end=0):sum(value),left(start),right(end){}
	void assign_value(T value, int start, int end) 
	{
		sum = value;
		left = start; 
		right = end;
	}
	const subarray_class<T>& operator=(const subarray_class& b)
	{
		this->sum = b.sum;
		this->left = b.left;
		this->right = b.right;
		return *this;
	}
};

template<typename T>
subarray_class<T> Find_max_crossing_subarray(T a[], int low, int mid, int high)
{
	T left_sum = a[mid];
	T sum = 0;
	int start=mid, end=mid;
	subarray_class<T> temp;
	for (int i = mid; i >= low; i--)
	{
		sum = sum + a[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			start = i;
		}
	}
	T right_sum = a[mid];
	sum = 0;
	for (int i = mid; i <= high; i++)
	{
		sum += a[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			end = i;
		}
	}
	temp.assign_value(left_sum + right_sum - a[mid], start, end);
	return temp;
}

template<typename T>
subarray_class<T> maximum_subarray_divideandconquer(T a[], int low, int high)
{
	int mid,start=low,end=high, left_low, left_high, right_low,right_high, cross_low, cross_high;
	subarray_class<T> temp;
	T leftsum = 0;
	T rightsum = 0;
	T crosssum = 0;
	if (high == low)
	{
		start = end = low;
		temp.assign_value(a[low], start, end);
		return temp;
	}
	else
	{
		mid = (low + high) / 2;
		temp = maximum_subarray_divideandconquer(a, low, mid);
		left_low = temp.left;
		left_high = temp.right;
		leftsum = temp.sum;
		
		temp = maximum_subarray_divideandconquer(a, mid + 1, high);
		right_low = temp.left;
		right_high = temp.right;
		rightsum = temp.sum;

		temp = Find_max_crossing_subarray(a, low, mid, high);
		cross_low = temp.left;
		cross_high = temp.right;
		crosssum = temp.sum;

		if (leftsum >= rightsum && leftsum >= crosssum)
		{
			temp.assign_value(leftsum, left_low, left_high);
			return temp;
		}
		else if (rightsum >= leftsum && rightsum >= crosssum)
		{
			temp.assign_value(rightsum, right_low, right_high);
			return temp;
		}
		else
		{
			temp.assign_value(crosssum, cross_low, cross_high);
			return temp;
		}
	}
		
}


/*Linear time method, for any maxiumsubarray, the prefix cannot have a sum 
less than 0, whenever the sum is less than zero, just assign it to 0 and neglate it.*/

template<typename T>
T maximum_subarray_linear(T a[], int n, int& start, int& end)
{
	start = end = 0;
	int current_start = 0, current_end = 0;
	T max = 0, max_temp = 0;
	while (current_end < n)
	{
		max_temp += a[current_end];
		if (max_temp > max)
		{
			max = max_temp;
			start = current_start;
			end = current_end;
		}
		if (max_temp <= 0)
		{
			max_temp = 0;
			current_start = current_end + 1;
		}
		current_end++;
	}
	return max;
}

// test the functionality of the above codes
#include<iostream>
using namespace std;

template<typename T>
void Print_Array(T a[], int start, int end)
{
	for (int i = start; i < end + 1; i++)
		cout << a[i] << ' ';
	cout << endl;
}

int main()
{
	int a[] = { 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };
	cout << "the input array is: ";
	int n = sizeof(a) / sizeof(*a);
	Print_Array(a, 0, n - 1);
	cout << "the length of array is: " << n << endl << endl;

	int start, end;
	int sum;

	cout << "cubic time method" << endl;
	sum=maximum_subarray_brute(a, n, start, end);
	cout << "The maximum subarray is: ";
	Print_Array(a, start, end);
	cout << "The sum is: " << sum << endl;

	start = end = sum = 0;
	cout << "\n\nquadratic time method" << endl;
	sum = maximum_subarray_dp(a, n, start, end);
	cout << "The maximum subarray is: ";
	Print_Array(a, start, end);
	cout << "The sum is: " << sum << endl;


	start = end = sum = 0;
	cout << "\n\nlinear time method" << endl;
	sum = maximum_subarray_linear(a, n, start, end);
	cout << "The maximum subarray is: ";
	Print_Array(a, start, end);
	cout << "The sum is: " << sum << endl;

	start = end = sum = 0;
	cout << "\n\ndivide and conquer method" << endl;
	subarray_class<int> temp;
	temp=maximum_subarray_divideandconquer(a,0,n-1);
	cout << "The maximum subarray is: ";
	start = temp.left;
	end = temp.right;
	sum = temp.sum;
	Print_Array(a, start, end);
	cout << "The sum is: " << sum << endl;
}
