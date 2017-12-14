/*randomize an array*/
#include <cstdlib>
#include <ctime>
int RANDOM(int a, int b)    //return a random number between a and b, inclusively
{
	static bool firstrun = true;
	if (true == firstrun)
		std::srand(std::time(nullptr));
	firstrun = false;
	return std::rand() % (b - a + 1) + a;
}

int RANDOM(int b)   //return a random number between 0 and b, inclusively
{
	return RANDOM(0, b);
}

template<class T>
void RANDOMIZE(T a[], int p, int q)        //shuffle an array between index a and b
{
	int j = 0;
	for (int i = p; i < q; i++)
	{
		j = RANDOM(i, q);
		Swap(a[j], a[i]);
	}
}

template<class T>
void RANDOMIZE(T a[], int size /*array size*/)          //shuffle a whole array;
{
	RANDOMIZE(a, 0, size - 1);
}
