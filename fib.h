#ifndef _FIB_H_
#define _FIB_H_

template <class T>
struct Node {
	T key;
	Node<T> *parent, *child;
	Node<T> *left, *right;
	int degree;
	bool mark;
	Node(T* x);
	~Node();
};

template <class T>
struct Fib {
private:
	Node<T>* m;
	int s;
	int degree;
public:
	Node<T>* mrp();//min root pointer, for desrease_key tests
	void push(T key);// insert
	T top();// min
	int size();
	void unite(Fib* H);
	inline void link(Node<T>* y, Node<T>* x);//needed in the next function
	void consolidate(int Dn);//needed in the next function
	void pop();// extract_min
	void cut(Node<T>* x, Node<T>* y);//needed in the two next functions
	void cascading_cut(Node<T>* y);//needed in the next function
	void decrease_key(Node<T>* x, T newKey);
	void delete_node(Node<T>* x);// void delete(Node<T>* x)
	Fib();
	~Fib();
};

#include "fib.hpp"

#endif
