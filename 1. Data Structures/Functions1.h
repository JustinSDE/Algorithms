#pragma once
#include <iostream>

#ifndef FUNCTIONS1_H
#define FUNCTIONS1_H



int Factorial(int n)   //求阶剩
{
	if (n <= 1)
		return 1;
	else
		return n*Factorial(n - 1);
}



template<class T>
void SecondOrderRoots(T a, T b, T c)  //二次方程求根
{
	T d = b*b - 4 * a*c;
	if (d > 0)
	{
		float sqrtd = sqrt(d);
		std::cout << "There are two real roots " << (-b + sqrtd) / 2.0 / a <<
			" and " << (-b - sqrtd) / 2.0 / a << std::endl;
	}
	if (0 == d)
		std::cout << "There is only one distinct root " << -b / 2.0 / a << std::endl;
	if (d < 0)
	{
		float sqrtd = sqrt(-d);
		std::cout << "There are two complex roots " << -b / 2.0 / a << "+" << sqrtd / 2.0 / a << "i and "
			<< -b / 2.0 / a << "-" << sqrtd / 2.0 / a << "i" << std::endl;
	}
}

template<class T>
int Max(T a[], int n)  //求取数组中最大元素位置
{
	int pos = 0;
	for (int i = 1; i < n; i++)
		if (a[pos] < a[i])
			pos = i;
	return pos;
}


#endif // !FUNCTIONS1_H

