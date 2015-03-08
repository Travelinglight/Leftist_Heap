#ifndef LHEAP_H
#define LHEAP_H

#include "HeapNode.h"
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

template<typename T1>
int dCmp(const T1 &a, const T1 &b) {	// default compare function
	if (a > b)
		return 1;
	if (a < b)
		return -1;
	return 0;
}

template<class T1, class T2 = NULLT>
class LHeap {

private :
	
	int size;
	int(*cmp)(const T1 &a, const T1 &b);

	int calcSize(const Node<T1, T2> * const node) const;
	int calcNpl(const Node<T1, T2> * const node) const;
	Node<T1, T2>* merge(Node<T1, T2> *H1, Node<T1, T2> *H2);
public :
	Node<T1, T2> *root;
	// constructors and destructor
	LHeap();
	LHeap(int(*compare)(const T1 &a, const T1 &b));
	LHeap(const T1 &rootID, const T2 * const rootRcd = NULL, int(*compare)(const T1 &a, const T1 &b) = dCmp);
	LHeap(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b) = dCmp);
	LHeap(const LHeap<T1, T2> &Old);
	~LHeap();

	// operations
	bool setCmp(int(*compare)(const T1 &a, const T1 &b));
	Node<T1, T2> * Top();
	Node<T1, T2> * Pop();
	bool empty();
	bool Insert(const T1 &id, const T2 * rcd = NULL);
	bool Merge(LHeap * lhp);

	// get info of the heap
	int getSize() const { return size; }
	bool print() const;

	friend LHeap<T1, T2> * operator+(LHeap<T1, T2> &a, LHeap<T1, T2> &b);
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
LHeap<T1, T2>::LHeap() {
	root = NULL;
	size = 0;
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
LHeap<T1, T2>::LHeap(int(*compare)(const T1 &a, const T1 &b)) {
	root = NULL;
	size = 0;
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
LHeap<T1, T2>::LHeap(const T1 &rootID, const T2 * const rootRcd, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(rootID, rootRcd);
	size = 1;
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
LHeap<T1, T2>::LHeap(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b)) {
	root = new Node<T1, T2>(rootID, rootRcd);
	size = 1;
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
	if (Old.root != NULL) {
		root = new Node<T1, T2>;
		root->copy(Old.root);
	}
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
//        NAME: calcNpl
// DESCRIPTION: To get the Npl of a Node or NULL.
//   ARGUMENTS: const Node<T1, T2> * const node - the node of which the Npl we want to find out
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: int
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-03-05
//							KC 2015-03-05
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
int LHeap<T1, T2>::calcNpl(const Node<T1, T2> * const node) const {
	if (node == NULL)
		return -1;
	return node->getNpl();
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: merge
// DESCRIPTION: To merge two heaps.
//   ARGUMENTS: const Node<T1, T2> * const node - the root the of another heap
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-03-05
//							KC 2015-03-05
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2>* LHeap<T1, T2>::merge(Node<T1, T2> *H1, Node<T1, T2> *H2) {
	Node<T1, T2> *head = NULL, *Tmp = NULL;
	if (H1 == NULL)
		return H2;
	if (H2 == NULL)
		return H1;
	head = cmp(H1->getID(), H2->getID()) > 0 ? H2 : H1;
	head->AddRgt(merge(head->getRgt(), cmp(H1->getID(), H2->getID()) > 0 ? H1 : H2));
	head->setNpl(MIN(calcNpl(head->getLft()), calcNpl(head->getRgt())) + 1);	// reset Npl
	if (calcNpl(head->getLft()) < calcNpl(head->getRgt())) {	// swap if left-npl is smaller than right-npl
		Tmp = head->getRgt();
		head->AddRgt(head->getLft());
		head->AddLft(Tmp);
	}
	return head;
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
//        NAME: Pop
// DESCRIPTION: To get the top element in a heap and delete it.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-03-05
//							KC 2015-03-05
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2> * LHeap<T1, T2>::Pop() {
	Node<T1, T2> * tmp;
	if (root == NULL) {
		throw LHeapERR("the heap is already empty");
		return NULL;
	}
	tmp = root;
	root = merge(root->getLft(), root->getRgt());
	return tmp;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: Top
// DESCRIPTION: To get the top element in a heap without deleting it.
//   ARGUMENTS: none
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: Node<T1, T2>*
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-03-03
//							KC 2015-03-03
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
Node<T1, T2> * LHeap<T1, T2>::Top() {
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
//        NAME: Insert
// DESCRIPTION: To insert a node into the heap.
//   ARGUMENTS: const T1 &id - the ID of the new node
//				const T2 * rcd - the Rcd of the new node
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-02-10
//							KC 2015-02-10
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool LHeap<T1, T2>::Insert(const T1 &id, const T2 * rcd) {
	Node<T1, T2> *H2 = NULL;
	H2 = new Node<T1, T2>(id, rcd);
	if (H2 == NULL) {
		throw LHeapERR("Out of space");
		return false;
	}
	root = merge(root, H2);
	++size;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
//        NAME: Insert
// DESCRIPTION: To merge a new-come heap with this heap.
//   ARGUMENTS: LHeap * lhp - the new-come heap
// USES GLOBAL: none
// MODIFIES GL: root, size
//     RETURNS: bool
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-03-08
//							KC 2015-03-08
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
bool LHeap<T1, T2>::Merge(LHeap * lhp) {
	Node<T1, T2> *tmp;
	if (lhp == NULL)
		return true;
	
	tmp = new Node<T1, T2>(*(lhp->root));
	root = merge(root, tmp);
	size = calcSize(root);
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

////////////////////////////////////////////////////////////////////////////////
//        NAME: operator+
// DESCRIPTION: To merge two leftist heaps.
//   ARGUMENTS: LHeap &a, LHeap &b - the heaps that are to be merged
// USES GLOBAL: none
// MODIFIES GL: none
//     RETURNS: LHeap *
//      AUTHOR: Kingston Chan
// AUTHOR/DATE: KC 2015-03-08
//							KC 2015-03-08
////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2>
LHeap<T1, T2> * operator+(LHeap<T1, T2> &a, LHeap<T1, T2> &b) {
	LHeap<T1, T2> *New = new LHeap<T1, T2>(a);
	New->Merge(b);
	return New;
}

#endif
