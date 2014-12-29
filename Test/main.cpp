#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include <windows.h>

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void print(int i)
{
	std::cout << " " << i;
}

int main(int argc, char* argv[])
{ 
	std::cout << "Hello World!" << std::endl;

	int N(1e8);
	std::vector<double> v;
	v.reserve(N);
	for (int i(0); i < N; ++i)
	{
		v.push_back(i*i);
	}

	//for_each(v.begin(), v.end(), print);
	//std::cout << std::endl;

	std::vector<double> w(N, 0);

	
	StartCounter();
	std::adjacent_difference(v.begin(), v.end(), v.begin());
	double t1(GetCounter());
	std::cout << "adjacent_difference : " << t1 << std::endl;

	StartCounter();
	//w[0] = v[0];
	for (int i(1); i < v.size(); ++i)
	{
		//w[i] = v[i] - v[i-1];
		v[i] = v[i+1] - v[i];
	}
	double t2(GetCounter());
	std::cout << "for_loop            : " << t2 << std::endl;

	//for_each(v.begin(), v.end(), print);
	//std::cout << std::endl;

	std::cin.get();

	return EXIT_SUCCESS;
}
