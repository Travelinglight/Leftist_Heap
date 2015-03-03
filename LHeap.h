#ifndef LHEAP_H
#define LHEAP_H

#include "TreeNode.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class LHeapERR {
public :
	std::string error;
	LHeapERR();
	LHeapERR(std::string info) {
		error = info;
	}
};

template<class T1, class T2 = NULLT>
class LHeap {

private :
	Node<T1, T2> *root;
	int size;
	int(*cmp)(const T1 &a, const T1 &b);
	bool allowRpt; // allow repetition of id in a heap

	int calcSize(const Node<T1, T2> * const node) const;
public :
	// constructors and destructor
	LHeap(bool rpt = true);
	LHeap(int(*compare)(const T1 &a, const T1 &b), bool rpt = true);
	LHeap(const T1 &rootID, const T2 * const rootRcd = NULL, int(*compare)(const T1 &a, const T1 &b) = dCmp, bool rpt = true);
	LHeap(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b) = dCmp, bool rpt = true);
	LHeap(const LHeap<T1, T2> &Old);
	~LHeap();
	bool setCmp(int(*compare)(const T1 &a, const T1 &b));
	bool setRpt(bool rpt);

	Node<T1, T2> * Top();
	bool Pop();
	bool empty();
	bool Insert(const T1 &id, const T2 * rcd = NULL);

	int getSize() const { return size; }
	bool print() const;
};

////////////////////////////////////////////////////////////////////////////////
//        NAME: LHeap
// DESCRIPTION: Constructor of LHeap class.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
LHeap<T1, T2>::LHeap(bool rpt) {
	root = NULL;
	size = 0;
	allowRpt = rpt;
	cmp = dCmp;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: LHeap
// DESCRIPTION: Constructor of LHeap class.
//   ARGUMENTS: int(*compare)(const T1 &a, const T1 &b) - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
LHeap<T1, T2>::LHeap(int(*compare)(const T1 &a, const T1 &b), bool rpt) {
	root = NULL;
	size = 0;
	allowRpt = rpt;
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: LHeap
// DESCRIPTION: Constructor of LHeap class.
//   ARGUMENTS: const T1 &rootID - the ID of the root node
//				const T2 * const rootRcd = NULL - the initial root record
//				int(*compare)(const T1 &a, const T1 &b) = dCmp - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
LHeap<T1, T2>::LHeap(const T1 &rootID, const T2 * const rootRcd, int(*compare)(const T1 &a, const T1 &b), bool rpt) {
	root = new Node<T1, T2>(rootID, rootRcd);
	size = 1;
	allowRpt = rpt;
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: LHeap
// DESCRIPTION: Constructor of LHeap class.
//   ARGUMENTS: const T1 &rootID - the ID of the root node
//				const T2 &rootRcd - the initial root record
//				int(*compare)(const T1 &a, const T1 &b) = dCmp - the compare function
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
LHeap<T1, T2>::LHeap(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b), bool rpt) {
	root = new Node<T1, T2>(rootID, rootRcd);
	size = 1;
	allowRpt = rpt;
	cmp = compare;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: LHeap
// DESCRIPTION: Copy constructor of LHeap class.
//   ARGUMENTS: const LHeap<T1, T2> &Old - the LHeap that is to be copied
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
LHeap<T1, T2>::LHeap(const LHeap<T1, T2> &Old) {
	size = Old.size;
	cmp = Old.cmp;
	allowRpt = Old.allowRpt;
	root = new Node<T1, T2>;
	root->copy(Old.root);
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: LHeap
// DESCRIPTION: Destructor of LHeap class.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size, cmp;
//     RETURNS: none
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
LHeap<T1, T2>::~LHeap() {
	//cout << "Destructor: ";
	//if (root != NULL)
	//	cout << root->getID();
	//cout << endl;
	delete root;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: calcSize
// DESCRIPTION: To calculate the size of the tree with the root "node".
//   ARGUMENTS: const Node<T1, T2> * const node - the root the of tree
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: int
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
int LHeap<T1, T2>::calcSize(const Node<T1, T2> * const node) const {
	if (node == NULL)
		return 0;
	else
		return calcSize(node->getLft()) + calcSize(node->getRgt()) + 1;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: setCmp
// DESCRIPTION: To assign the compare function to the member function pointer.
//   ARGUMENTS: int(*compare)(const T1 &a, const T1 &b) - the compare function
// USES GLOBAL: none
// MODIFIES GL: cmp
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool LHeap<T1, T2>::setCmp(int(*compare)(const T1 &a, const T1 &b)) {
	cmp = compare;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: setRpt
// DESCRIPTION: To set the allowance of repetition in a heap.
//   ARGUMENTS: bool rpt - the value of allowRpt
// USES GLOBAL: none
// MODIFIES GL: allowRpt
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-03-03
//							KC 2015-03-03
////////////////////////////////////////////////////////////////////////////////
bool LHeap<T1, T2>::setRpt(bool rpt) {
	allowRpt = rpt;
	return true;
}


template<class T1, class T2>
bool LHeap<T1, T2>::Pop() {
	
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: Top
// DESCRIPTION: To get the top element in a heap without deleting it.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: Node<T1, T2>
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-03-03
//							KC 2015-03-03
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2> LHeap<T1, T2>::Top() {
	return root;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: empty
// DESCRIPTION: To delete all the nodes in the LHeap.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool LHeap<T1, T2>::empty() {
	if (root == NULL)
		return true;
	delete root;
	root = NULL;
	size = 0;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: print
// DESCRIPTION: print a heap with inorder traversal.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-11
//							KC 2015-02-11
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool LHeap<T1, T2>::print() const {
	if (root != NULL) {
		root->print();
		return true;
	}
	else
		return false;
}

#endif
