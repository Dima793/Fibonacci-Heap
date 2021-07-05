#ifndef _FIB_HPP_
#define _FIB_HPP_

#include <math.h>

template <class T>
Node<T>::Node(T* x) {
	key = *x;
	child = parent = NULL;
	right = left = this;
	degree = 0;
	mark = false;
}

template <class T>
Node<T>::~Node() {
	parent = NULL;
	if (child != NULL) {
		delete child;
	}
	if ((right != this) && (right->parent != NULL)) {
		delete right;
	}
}



template <class T>
Node<T>* Fib<T>::mrp() {//min root pointer, for desrease_key tests
	return m;
}

template <class T>
void Fib<T>::push(T key) {// insert
	Node<T> *x = new Node<T>(&key);
	if (m != NULL) {
		x->left = m;
		x->right = m->right;
		(m->right)->left = x;
		m->right = x;
	}
	else {
		x->right = x->left = x;// m = ...
	}
	if ((m == NULL) || (key < m->key)) {
		m = x;
	}
	degree++;
	s++;
}

template <class T>
T Fib<T>::top() {// min
/*
	if (m != NULL) return m->key;
	else return NULL;// maybe some error message
*/
	return m->key;
}

template <class T>
int Fib<T>::size() {
	return s;
}

template <class T>
void Fib<T>::unite(Fib* H) {	
	if (H->m == NULL) {
		//H->~Fib<T>();
		return;
	}
	if (m == NULL) {
		m = H-> m;
		degree = H->degree;
		//H->m = NULL;
		//H->~Fib<T>();
		return;
	}
	(m->right)->left = (H->m)->left;
	((H->m)->left)->right = m->right;
	m->right = H->m;
	(H->m)->left = m;
	if ((H->m)->key < m->key) {
		m = H->m;
	}
	degree += H->degree;
	s += H->s;
	//H->m = NULL;
	//H->~Fib<T>();
}

template <class T>
inline void Fib<T>::link(Node<T>* y, Node<T>* x) {//needed in the next function
	(y->left)->right = y->right;
	(y->right)->left = y->left;
	if ((x->degree)++) {
		((x->child)->right)->left = y;
		y->right = (x->child)->right;
		y->left = x->child;
		(x->child)->right = y;
	}
	else {
		x->child = y;
		y->right = y->left = y;
	}
	y->parent = x;
	y->mark = false;
	degree--;
}

template <class T>
void Fib<T>::consolidate(int Dn) {//needed in the next function
	Node<T>* a[Dn];
	for (int i = 0; i < Dn; i++) {
		a[i] = NULL;
	}
	Node<T>* curr = m;
	Node<T>* next;
	Node<T>* withSameDeg;
	int currDeg;
	int oldTreeDeg = degree;
	for (int i = 0; i < oldTreeDeg; i++) {
		next = curr->right;
		currDeg = curr->degree;
		while(a[currDeg] != NULL) {
			withSameDeg = a[currDeg];
			if (curr->key > withSameDeg->key) {
				Node<T>* tmp = curr;
				curr = withSameDeg;
				withSameDeg = tmp;
			}
			link(withSameDeg, curr);
			a[currDeg] = NULL;
			currDeg++;
		}
		a[currDeg] = curr;
		curr = next;
	}
	m = NULL;
	for (int i = 0; i < Dn; i++) {
		if (a[i] != NULL) {
			if (m != NULL) {
				(a[i])->right = m->right;
				(a[i])->left = m;
				(m->right)->left = a[i];
				m->right = a[i];
			}
			else {
				(a[i])->right = (a[i])->left = a[i];// m = ...
			}
			if ((m == NULL) || ((a[i])->key < m->key)) {
				m = a[i];
			}
		}
	}
}

template <class T>
void Fib<T>::pop() {// extract_min
	if (m == NULL) return;
	Node<T>* curr = m->child;
	if (m->child != NULL) {
		degree += m->degree;
		for (int i = 0; i < m->degree; i++) {
			curr->parent = NULL;
			curr = curr->right;
		}
		(m->right)->left = (m->child)->left;
		((m->child)->left)->right = m->right;
		(m->child)->left = m;
		m->right = m->child;
	}
	(m->right)->left = m->left;
	(m->left)->right = m->right;
	curr = m;
	if (m == m->right) {
		m = NULL;
	}
	else {
		m = m->right;
	}
	curr->child = NULL;
	delete curr;
	degree--;
	s--;
	consolidate(2 * log(s) + 1);
}

template <class T>
void Fib<T>::cut(Node<T>* x, Node<T>* y) {//needed in the two next functions
	if (--(y->degree)) {
		if (y->child == x) {
			y->child = x->right;
		}
		(x->left)->right = x->right;
		(x->right)->left = x->left;
	}
	else {
		y->child = NULL;
	}
	if (m != NULL) {
		(x)->right = m->right;
		(x)->left = m;
		(m->right)->left = x;
		m->right = x;
	}
	else {
		m = (x)->right = (x)->left = x;
	}
	x->parent = NULL;
	x->mark = false;
}

template <class T>
void Fib<T>::cascading_cut(Node<T>* y) {//needed in the next function
	if (y->parent != NULL) {
		Node<T>* p = y->parent;
		if (y->mark) {
			cut(y, p);
			cascading_cut(p);
		}
		else {
			y->mark = true;
		}
	}
}

template <class T>
void Fib<T>::decrease_key(Node<T>* x, T newKey) {
	if (newKey > x->key) {
		return;
	}
	x->key = newKey;
	Node<T>* p = x->parent;
	if ((p != NULL) && (x->key < p->key)) {
		cut(x, p);
		cascading_cut(p);
	}
	if (x->key < m->key) {
		m = x;
	}
}

template <class T>
void Fib<T>::delete_node(Node<T>* x) {// void delete(Node<T>* x)
	Node<T>* p = x->parent;
	cut(x, p);
	cascading_cut(p);
	m = x;
	pop();
}

template <class T>
Fib<T>::Fib() {
	m = NULL;
	s = 0;
	degree = 0;
}

template <class T>
Fib<T>::~Fib() {
	Node<T>* curr = m;
	while(degree--) {
		curr->parent = m;
		curr = curr->right;
	}
	delete m;
}

#endif
