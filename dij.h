#ifndef _DIJ_H_
#define _DIJ_H_

#include <utility>
#include <float.h>
#include <ctime>

template<template<class> class T>
double dijkstra(double* dist, int* p, int* deg, int** inc, double** w, int s, int n) {
	bool was[n];
	std::clock_t a = std::clock();
	T<std::pair<double, int> > heap;
	for (int i = 0; i < n; i++) {
		dist[i] = DBL_MAX - i;
		was[i] = false;
	}
	dist[s] = 0;
	p[s] = s;
	int notVisited = n;
	for (int i = 0; i < n; i++) {
		heap.push(std::make_pair(dist[i], i));
	}
	int curr, currInc;
	while(--notVisited > 0) {
		do {
			curr = heap.top().second;	
			heap.pop();
		} while (was[curr]);
		was[curr] = true;
		for (int i = 0; i < deg[curr]; i++) {
			currInc = inc[curr][i];
			if ((!was[currInc]) && (dist[currInc] > dist[curr] + w[curr][i])) {
				dist[currInc] = dist[curr] + w[curr][i];
				heap.push(std::make_pair(dist[currInc], currInc));
				p[currInc] = curr;
			}
		}
	}
	std::clock_t b = std::clock();
	return ((double)(b - a))/CLOCKS_PER_SEC;
}

#endif
