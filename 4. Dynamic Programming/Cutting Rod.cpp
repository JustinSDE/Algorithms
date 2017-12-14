#include <iostream>
#include <stack>
using namespace std;

void Bottom_Up_Cutting_Rods(int price[], int s[], int r[]);
void Print_Cuts(int n, int s[]);

void main()
{
	int price[] = { 0,1,5,8,9,10,17,17,20,24,30 };
	int s[11] = { 0 };
	int r[11] = { 0 };

	for (int i = 0; i < 11; i++)
		cout << price[i] << ' ' << s[i] << ' ' << r[i] << endl;
	cout << "hello world!" << endl;
	Bottom_Up_Cutting_Rods(price, s, r);
	for (int i = 1; i <= 10; i++)
		Print_Cuts(i, s);
}



void Bottom_Up_Cutting_Rods(int price[], int s[], int r[])
{
	for (int i = 1; i < 11; i++)
	{
		r[i] = price[i];
		s[i] = i;
		for (int j = 1; j < i; j++)
		{
			if (r[i] < r[j] + r[i - j])
			{
				r[i] = r[j] + r[i - j];
				s[i] = i - j;
			}
		}
	}
}

void Print_Cuts(int n, int s[])
{
	cout << "A rod with length of " << n << " should be cut into£º";
	stack<int> q;
	q.push(n);
	int x;
	while (!q.empty())
	{
		x = q.top();
		q.pop();
		if (x == s[x])
			cout << x << ' ';
		else
		{
			q.push(s[x]);
			q.push(x - s[x]);
		}
	}
	cout << endl;
}