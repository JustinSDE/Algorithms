#ifndef GREEDY_H
#define GREEDY_H
#include <iostream>
#include <iomanip>


const int numberofpoints = 5;

int matrix[numberofpoints + 1][numberofpoints + 1];

int S[numberofpoints + 1];
int dist[numberofpoints + 1];
int pre[numberofpoints + 1];
int sz = 0;

int Add(int a, int b)
{
	if (a >= 100 || b >= 100)
		return 100;
	else
		return a + b;
}

void Initialize()
{
	for (int i = 1; i <= numberofpoints; i++)
	{
		S[i] = pre[i] = 0;
		dist[i] = 100;
		for (int j = 1; j <= numberofpoints; j++)
			matrix[i][j] = 100;
	}
	matrix[1][2] = 4;
	matrix[1][3] = 2;
	matrix[3][4] = 1;
	matrix[2][4] = 4;
	matrix[2][5] = 5;
	matrix[4][5] = 3;
	matrix[1][5] = 8;
}
void UpdateDist()
{
	for (int i = 1; i <= numberofpoints; i++)
	{
		for (int j = 1; j <= sz; j++)
		{
			if (dist[i] > dist[S[j]] + matrix[S[j]][i])
			{
				dist[i] = dist[S[j]] + matrix[S[j]][i];
				pre[i] = S[j];
			}
		}
	}
}

int FindMin()
{
	int index = 0;
	int Min = 100;
	int preIndex;
	for (int i = 1; i <= numberofpoints; i++)
	{
		if (dist[i] < Min)
		{
			preIndex = index;
			index = i;
			Min = dist[i];
			for (int j = 1; j <= sz; j++)
			{
				if (S[j] == i)
				{
					index = preIndex;
					if (index == 0)
						Min = 100;
					else
						Min = dist[index];
				}
			}
		}
	}
	return index;
}
void FindLeastPath()
{
	int next;
	sz = 1;
	S[1] = 1;
	dist[1] = 0;
	pre[1] = 1;
	while (sz < numberofpoints)
	{
		UpdateDist();
		next = FindMin();
		S[++sz] = next;
	}
}

void OutputResult()
{
	using namespace std;
	int point;
	for (int i = 2; i <= numberofpoints; i++)
	{
		cout << dist[i] << "\t" << i;
		point = pre[i];
		while (point != 1)
		{
			cout << "<-" << point;
			point = pre[point];
		}
		cout << "<-" << point << endl;
	}
}
void PrintMatrix()
{
	using namespace std;
	for (int i = 1; i <= numberofpoints; i++)
	{
		for (int j = 1; j <= numberofpoints; j++)
		{
			if (matrix[i][j] <100)
				cout << setw(8) << matrix[i][j];
			else
				cout << setw(8) << "INF";
		}
		cout << endl;
	}
}

void FindShortestPaths()
{
	Initialize();
	PrintMatrix();
	FindLeastPath();
	OutputResult();
}
#endif // !GREEDY_H


