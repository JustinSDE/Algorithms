#pragma once
#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H

float DP_max(float a, float b)
{
	if (a > b)
		return a;
	else return b;
}
//0/1±³°üÎÊÌâ
float F(int i, float y, float price[], float weight[], int n)
{
	if (i == n - 1)
		return (y >= weight[i]) ? price[i] : 0;
	if (y < weight[i])
		return F(i + 1, y, price, weight, n);
	else
		return DP_max(F(i + 1, y, price, weight, n), F(i + 1, y - weight[i],price,weight,n) + price[i]);
}



#endif // !DYNAMICPROGRAMMING_H
