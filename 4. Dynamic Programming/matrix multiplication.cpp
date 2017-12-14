#include <iostream>

template<typename T>
class matrix
{
private:
	int cols;
	int rows;
	T* element;
public:
	matrix(int r, int c) : cols(c), rows(r)
	{
		element = new T[c*r];
	}
	T& operator()(int a, int b)
	{
		if (a >= rows || a < 0 || b >= cols || b < 0)
			throw "Out of Boundary";
		else
		{
			return element[cols*a + b];
		}
	}
	void Print(std::ostream& os) const
	{
		for (int i = 0; i < cols*rows; i++)
		{
			os << element[i] << ' ';
			if ((i + 1) % cols == 0)
				os << '\n';
		}
	}
	int getrows() const { return rows; }
	int getcols() const { return cols; }
};


template<typename T>
std::ostream& operator<<(std::ostream& os, const matrix<T>& m)
{
	m.Print(os);
	return os;
}

template<typename T>
void Square_matrix_multiply( matrix<T>& a, matrix<T>& b, matrix<T> & c)
{
	int n = a.getcols();
	for(int i=0;i<n;i++)
		for (int j = 0; j < n; j++)
		{
			c(i, j) = 0;
			for (int k = 0; k < n; k++)
				c(i, j) += a(i, k)*b(k, j);
		}
}

void main()
{
	matrix<int> a(4, 4),b(4,4),c(4,4);
	int k = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			a(i, j) = b(i,j)=k;
			k++;
		}
	std::cout <<"matrix A is: \n"<<a<<"\n\nmatrix b is: \n"<<b<<"\n\n\n";
	std::cout << "multiple a*b to get c: c=a*b\n";
	Square_matrix_multiply(a, b, c);
	std::cout << "matrix C is:\n" << c << std::endl;
}



