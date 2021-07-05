#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <queue>
#include "fib.h"
#include "dij.h"

template <class T>
using minPQ = std::priority_queue<T, std::vector<T>, std::greater<T> >;

int createGraph(int n, int pD, int pE, int pl, int* deg, int** inc, double** w) {
	int curr = 0;
	int firstFree = 1;
	double weight;
	int parent[n];
	parent[0] = 0;
	for (int i = 0; i < n; i++) {
		deg[i] = 0;
	}
	while ((firstFree < n) && (curr < firstFree)) {// create a tree
		while (((deg[curr] < pl + (curr != 0)) || (rand() % 100 < pD)) && (firstFree < n)) {
			inc[curr][deg[curr]] = firstFree;
			inc[firstFree][deg[firstFree]] = curr;
			weight = (rand() % 1000000) / 1000;
			w[curr][deg[curr]++] = weight;
			w[firstFree][deg[firstFree]++] = weight;
			parent[firstFree++] = curr;
		}
		curr++;
	}
	n = firstFree;
	for (int i = 0; i < n; i++) {// add some edges
		for (int j = i + 1; j < n; j++) {
			if ((parent[j] != i) && (rand() % 100 < pE)) {
				inc[i][deg[i]] = j;
				inc[j][deg[j]] = i;
				weight = (rand() % 1000000) / 1000;
				w[i][deg[i]++] = weight;
				w[j][deg[j]++] = weight;
			}
		}
	}
	return n;// number of vertexes in graph
}

int main() {
	int n = 5000;
	int s;
	double dist[n];
	int p[n];
	int deg[n];
	int* inc[n];
	double* w[n];
	for (int i = 0; i < n; i++) {
		inc[i] = new int[n];
		w[i] = new double[n];
	}
	double answer;

	n = 5, s = 1;
	deg[0] = 1;
	deg[1] = 2;
	deg[2] = 1;
	deg[3] = 3;
	deg[4] = 1;
	inc[0][0] = 3;
	w[0][0] = 1;
	inc[1][0] = 3;
	w[1][0] = 1;
	inc[1][1] = 2;
	w[1][1] = 1;
	inc[2][0] = 1;
	w[2][0] = 1;
	inc[3][0] = 0;
	w[3][0] = 1;
	inc[3][1] = 1;
	w[3][1] = 1;
	inc[3][2] = 4;
	w[3][2] = 1;
	inc[4][0] = 3;
	w[4][0] = 1;

	answer = dijkstra<Fib>(dist, p, deg, inc, w, s, n);
	printf("\nFib:\t%f\n", answer);
	for (int i = 0; i < n; i++) {
		printf("p[%d] = %d,   dist[%d] = %f\n", i, p[i], i, dist[i]);
	}
	answer = dijkstra<minPQ>(dist, p, deg, inc, w, s, n);
	printf("\npriority_queue:\t%f\n", answer);
	for (int i = 0; i < n; i++) {
		printf("p[%d] = %d,   dist[%d] = %f\n", i, p[i], i, dist[i]);
	}
	printf("\n");

	for (int i = 0; i < 5; i++) {
		n = rand() % 5000 + 1;
		n = createGraph(n, (i + 5) * 10, (i + 5) * 10, 1, deg, inc, w);
		s = rand() % n;
		printf("\nTest № %d\t(pD = %d%, pE = %d%, pl = 1, n = %d)\n", i, (i + 5) * 10, (i + 5) * 10, n);
		answer = dijkstra<Fib>(dist, p, deg, inc, w, s, n);
		printf("Fib:\t%f\n", answer);
		answer = dijkstra<minPQ>(dist, p, deg, inc, w, s, n);
		printf("priority_queue:\t%f\n", answer);
	}
	for (int i = 5; i < 10; i++) {
		n = rand() % 5000 + 1;
		n = createGraph(n, i * 10, i - 5, 1, deg, inc, w);
		s = rand() % n;
		printf("\nTest № %d\t(pD = %d%, pE = %d%, pl = 1, n = %d)\n", i, i * 10, i - 5, n);
		answer = dijkstra<Fib>(dist, p, deg, inc, w, s, n);
		printf("Fib:\t%f\n", answer);
		answer = dijkstra<minPQ>(dist, p, deg, inc, w, s, n);
		printf("priority_queue:\t%f\n", answer);
	}
	for (int i = 10; i < 16; i++) {
		n = rand() % 5000 + 1;
		n = createGraph(n, i - 10, (i - 5) * 10, 1, deg, inc, w);
		s = rand() % n;
		printf("\nTest № %d\t(pD = %d%, pE = %d%, pl = 1, n = %d)\n", i, i - 10, (i - 5) * 10, n);
		answer = dijkstra<Fib>(dist, p, deg, inc, w, s, n);
		printf("Fib:\t%f\n", answer);
		answer = dijkstra<minPQ>(dist, p, deg, inc, w, s, n);
		printf("priority_queue:\t%f\n", answer);
	}
	for (int i = 16; i < 21; i++) {
		n = rand() % 5000 + 1;
		n = createGraph(n, 75 + i, 75 + i, 7, deg, inc, w);
		s = rand() % n;
		printf("\nTest № %d\t(pD = %d%, pE = %d%, pl = %d, n = %d)\n", i, 75 + i, 75 + i, 7, n);
		answer = dijkstra<Fib>(dist, p, deg, inc, w, s, n);
		printf("Fib:\t%f\n", answer);
		answer = dijkstra<minPQ>(dist, p, deg, inc, w, s, n);
		printf("priority_queue:\t%f\n", answer);
	}
	n = 5000;
	n = createGraph(n, 90, 90, 5, deg, inc, w);
	s = 0;
	printf("\nTest X\t(pD = %d%, pE = %d%, pl = %d, n = %d)\n", 90, 90, 5, n);
	answer = dijkstra<Fib>(dist, p, deg, inc, w, s, n);
	printf("Fib:\t%f\n", answer);
	answer = dijkstra<minPQ>(dist, p, deg, inc, w, s, n);
	printf("priority_queue:\t%f\n", answer);
	n = createGraph(n, 0, 100, 1, deg, inc, w);
	s = 0;
	printf("\nTest full\t(pD = %d%, pE = %d%, pl = %d, n = %d)\n", 0, 100, 1, n);
	answer = dijkstra<Fib>(dist, p, deg, inc, w, s, n);
	printf("Fib:\t%f\n", answer);
	answer = dijkstra<minPQ>(dist, p, deg, inc, w, s, n);
	printf("priority_queue:\t%f\n", answer);
	n = 5000;
	n = createGraph(n, 0, 0, 1, deg, inc, w);
	s = 0;
	printf("\nTest bamboo\t(pD = %d%, pE = %d%, pl = %d, n = %d)\n", 0, 0, 1, n);
	answer = dijkstra<Fib>(dist, p, deg, inc, w, s, n);
	printf("Fib:\t%f\n", answer);
	answer = dijkstra<minPQ>(dist, p, deg, inc, w, s, n);
	printf("priority_queue:\t%f\n", answer);


	n = 5000;
	for (int i = 0; i < n; i++) {
		delete inc[i];
		delete w[i];
	}

	return 0;
}
