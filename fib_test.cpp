#include <cstdio>
#include <cstdlib>
#include <utility>
#include <ctime>
#include <queue>
#include "fib.h"

template <class T>
using minPQ = std::priority_queue<T, std::vector<T>, std::greater<T> >;

template<template<class> class T>
std::pair<double, double> hillTestInt(int n) {
	T<std::pair<int, int> > f;
	//int last = -500000001;
	std::clock_t a = std::clock();
	for (int i = 0; i < n; i++) {
		f.push(std::make_pair(rand() % 1000000000 - 500000000, i));
	}
	std::clock_t b = std::clock();
	for (int i = 0; i < n; i++) {
		//if (f.top().first < last) {
		//	printf("\n\n\t!!!\n\t(int)\n\n");
		//}
		//last = f.top().first;
		f.pop();
	}
	std::clock_t c = std::clock();
	return std::make_pair(((double)(b - a))/CLOCKS_PER_SEC, ((double)(c - b))/CLOCKS_PER_SEC);
}

template<template<class> class T>
std::pair<double, double> hillTestDouble(int n) {
	T<std::pair<double, int> > f;
	//double last = -500000001;
	std::clock_t a = std::clock();
	for (int i = 0; i < n; i++) {
		f.push(std::make_pair((double)(rand() % 1000000000 - 500000000) / 10000, i));
	}
	std::clock_t b = std::clock();
	for (int i = 0; i < n; i++) {
		//if (f.top().first < last) {
		//	printf("\n\n\t!!!\n\t(double)\n\n");
		//}
		//last = f.top().first;
		f.pop();
	}
	std::clock_t c = std::clock();
	return std::make_pair(((double)(b - a))/CLOCKS_PER_SEC, ((double)(c - b))/CLOCKS_PER_SEC);
}

template<template<class> class T>
double sawTestInt(int t, int k) {
	T<std::pair<int, int> > f;
	std::clock_t a = std::clock();
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < t; j++) {
			f.push(std::make_pair(rand() % 1000000000 - 500000000, i * t + j));
		}
		f.pop();
	}
	std::clock_t b = std::clock();
	return ((double)(b - a))/CLOCKS_PER_SEC;
}

template<template<class> class T>
double sawTestDouble(int t, int k) {
	T<std::pair<double, int> > f;
	std::clock_t a = std::clock();
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < t; j++) {
			f.push(std::make_pair((double)(rand() % 1000000000 - 500000000) / 10000, i * t + j));
		}
		f.pop();
	}
	std::clock_t b = std::clock();
	return ((double)(b - a))/CLOCKS_PER_SEC;
}

int main() {
	Fib<int> a;
	a.push(103);
	a.push(102);
	a.push(101);
	printf("\n%d\n", a.top());
	a.pop();
	printf("%d\n", a.top());


	Fib<int> b;
	b.push(203);
	b.push(202);
	b.push(201);
	printf("\n%d\n", b.top());
	b.pop();
	printf("%d\n", b.top());

	b.unite(&a);
	printf("\n%d\n", b.top());
	b.pop();
	printf("%d\n", b.top());
	b.pop();
	printf("%d\n", b.top());
	b.pop();
	printf("%d\n", b.top());
	b.pop();

	Fib<double> c;
	c.push(1.03);
	c.push(1.02);
	Node<double>* FDP = c.mrp();
	c.push(1.01);
	printf("\n%f\n", c.top());
	c.decrease_key(FDP, 0.99);
	printf("%f\n", c.top());
	c.pop();
	printf("%f\n", c.top());
	c.pop();
	printf("%f\n", c.top());
	c.pop();

	std::pair<double, double> result;
	int n;
	for (int i = 1; i < 6; i++) {
		n = rand() % 10 + 1;
		printf("\nHill test № %d, n = %d\n", i, n);
		result = hillTestInt<Fib>(n);
		printf("Fib\t\tint: pushes - %f, pops - %f\n", result.first, result.second);		
		result = hillTestInt<minPQ>(n);
		printf("priority_queue\tint: pushes - %f, pops - %f\n", result.first, result.second);
		result = hillTestDouble<Fib>(n);
		printf("Fib\t\tdouble: pushes - %f, pops - %f\n", result.first, result.second);		
		result = hillTestDouble<minPQ>(n);
		printf("priority_queue\tdouble: pushes - %f, pops - %f\n", result.first, result.second);
	}
	for (int i = 6; i < 11; i++) {
		n = rand() % 100 + 1;
		printf("\nHill test № %d, n = %d\n", i, n);
		result = hillTestInt<Fib>(n);
		printf("Fib\t\tint: pushes - %f, pops - %f\n", result.first, result.second);		
		result = hillTestInt<minPQ>(n);
		printf("priority_queue\tint: pushes - %f, pops - %f\n", result.first, result.second);
		result = hillTestDouble<Fib>(n);
		printf("Fib\t\tdouble: pushes - %f, pops - %f\n", result.first, result.second);		
		result = hillTestDouble<minPQ>(n);
		printf("priority_queue\tdouble: pushes - %f, pops - %f\n", result.first, result.second);
	}
	for (int i = 11; i < 16; i++) {
		n = rand() % 10000 + 1;
		printf("\nHill test № %d, n = %d\n", i, n);
		result = hillTestInt<Fib>(n);
		printf("Fib\t\tint: pushes - %f, pops - %f\n", result.first, result.second);		
		result = hillTestInt<minPQ>(n);
		printf("priority_queue\tint: pushes - %f, pops - %f\n", result.first, result.second);
		result = hillTestDouble<Fib>(n);
		printf("Fib\t\tdouble: pushes - %f, pops - %f\n", result.first, result.second);		
		result = hillTestDouble<minPQ>(n);
		printf("priority_queue\tdouble: pushes - %f, pops - %f\n", result.first, result.second);
	}
	for (int i = 16; i < 21; i++) {
		n = rand() % 1000000 + 1;
		printf("\nHill test № %d, n = %d\n", i, n);
		result = hillTestInt<Fib>(n);
		printf("Fib\t\tint: pushes - %f, pops - %f\n", result.first, result.second);		
		result = hillTestInt<minPQ>(n);
		printf("priority_queue\tint: pushes - %f, pops - %f\n", result.first, result.second);
		result = hillTestDouble<Fib>(n);
		printf("Fib\t\tdouble: pushes - %f, pops - %f\n", result.first, result.second);		
		result = hillTestDouble<minPQ>(n);
		printf("priority_queue\tdouble: pushes - %f, pops - %f\n", result.first, result.second);
	}
	n = 20000000;
	printf("\nHill test X, n = %d\n", n);
	result = hillTestInt<Fib>(n);
	printf("Fib\t\tint: pushes - %f, pops - %f\n", result.first, result.second);		
	result = hillTestInt<minPQ>(n);
	printf("priority_queue\tint: pushes - %f, pops - %f\n", result.first, result.second);
	result = hillTestDouble<Fib>(n);
	printf("Fib\t\tdouble: pushes - %f, pops - %f\n", result.first, result.second);		
	result = hillTestDouble<minPQ>(n);
	printf("priority_queue\tdouble: pushes - %f, pops - %f\n", result.first, result.second);

	double res;
	int t, k;
	for (int i = 1; i < 6; i++) {
		t = rand() % 10 + 1;
		k = rand() % 10 + 1;
		printf("\nSaw test № %d, t = %d, k = %d\n", i, t, k);
		res = sawTestInt<Fib>(t, k);
		printf("Fib\t\tint: %f\n", res);		
		res = sawTestInt<minPQ>(t, k);
		printf("priority_queue\tint: %f\n", res);
		res = sawTestDouble<Fib>(t, k);
		printf("Fib\t\tdouble: %f\n", res);		
		res = sawTestDouble<minPQ>(t, k);
		printf("priority_queue\tdouble: %f\n", res);
	}
	for (int i = 6; i < 11; i++) {
		t = rand() % 10000 + 1;
		k = rand() % 10 + 1;
		printf("\nSaw test № %d, t = %d, k = %d\n", i, t, k);
		res = sawTestInt<Fib>(t, k);
		printf("Fib\t\tint: %f\n", res);		
		res = sawTestInt<minPQ>(t, k);
		printf("priority_queue\tint: %f\n", res);
		res = sawTestDouble<Fib>(t, k);
		printf("Fib\t\tdouble: %f\n", res);		
		res = sawTestDouble<minPQ>(t, k);
		printf("priority_queue\tdouble: %f\n", res);
	}
	for (int i = 11; i < 16; i++) {
		t = rand() % 10 + 1;
		k = rand() % 10000 + 1;
		printf("\nSaw test № %d, t = %d, k = %d\n", i, t, k);
		res = sawTestInt<Fib>(t, k);
		printf("Fib\t\tint: %f\n", res);		
		res = sawTestInt<minPQ>(t, k);
		printf("priority_queue\tint: %f\n", res);
		res = sawTestDouble<Fib>(t, k);
		printf("Fib\t\tdouble: %f\n", res);		
		res = sawTestDouble<minPQ>(t, k);
		printf("priority_queue\tdouble: %f\n", res);
	}
	for (int i = 16; i < 21; i++) {
		t = rand() % 100 + 1;
		k = rand() % 100 + 1;
		printf("\nSaw test № %d, t = %d, k = %d\n", i, t, k);
		res = sawTestInt<Fib>(t, k);
		printf("Fib\t\tint: %f\n", res);		
		res = sawTestInt<minPQ>(t, k);
		printf("priority_queue\tint: %f\n", res);
		res = sawTestDouble<Fib>(t, k);
		printf("Fib\t\tdouble: %f\n", res);		
		res = sawTestDouble<minPQ>(t, k);
		printf("priority_queue\tdouble: %f\n", res);
	}
	t = 6500;
	k = 6500;
	printf("\nSaw test X, t = %d, k = %d\n", t, k);
	res = sawTestInt<Fib>(t, k);
	printf("Fib\t\tint: %f\n", res);		
	res = sawTestInt<minPQ>(t, k);
	printf("priority_queue\tint: %f\n", res);
	res = sawTestDouble<Fib>(t, k);
	printf("Fib\t\tdouble: %f\n", res);
	res = sawTestDouble<minPQ>(t, k);
	printf("priority_queue\tdouble: %f\n", res);

	Fib<std::pair<int, int> > f;
	f.push(std::make_pair(1365080540, 0));
	f.push(std::make_pair(1540283426, 1));
	f.push(std::make_pair(303989172, 2));
	f.push(std::make_pair(1303355736, 3));
	f.push(std::make_pair(34905211, 4));
	f.push(std::make_pair(521495368, 5));
	f.push(std::make_pair(294602567, 6));
	f.push(std::make_pair(1726856429, 7));
	f.push(std::make_pair(336365782, 8));
	f.push(std::make_pair(860921530, 9));
	f.push(std::make_pair(278622862, 10));
	f.push(std::make_pair(233565123, 11));
	f.push(std::make_pair(2145074067, 12));
	f.push(std::make_pair(468603135, 13));
	f.push(std::make_pair(1101413929, 14));
	f.push(std::make_pair(1801879802, 15));
	f.push(std::make_pair(1315534022, 16));
	if (f.top().first != 34905211) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 233565123) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 278622862) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 294602567) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 303989172) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 336365782) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 468603135) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 521495368) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 860921530) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 1101413929) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 1303355736) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 1315534022) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 1365080540) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 1540283426) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 1726856429) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 1801879802) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();
	if (f.top().first != 2145074067) {
		printf("\n\n\t!!!\n\t(The Test of The 17)\n\n");
	}
	f.pop();


	return 0;
}
