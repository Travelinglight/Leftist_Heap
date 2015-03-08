#include "LHeap.h"
#include <iostream>
#include <cstdlib>
using namespace std;
class A {
public :
	int x;
	A(int id = 0) { x = id; }
	friend ostream &operator<<(ostream &out, A a);
	friend bool operator<(const A &a, const A &b);
	friend bool operator>(const A &a, const A &b);
};

ostream &operator<<(ostream &out, A a) {
	cout << a.x;
	return out;
}

bool operator<(const A &a, const A &b) {
	return (a.x < b.x);
}

bool operator>(const A &a, const A &b) {
	return (a.x > b.x);
}

// the compare function
int cmp(const A &a, const A &b) {
	if (a.x > b.x)
		return 1;
	if (a.x < b.x)
		return -1;
	return 0;
}

int main() {
	{ // LHeap();	LHeap(const LHeap<T1, T2> &New);	bool setCmp(int(*compare)(const T1 &a, const T1 &b));
	  	cout << "========================================" << endl;
		LHeap<A> LH1;
		LH1.setCmp(cmp);
		LHeap<A> LH2(LH1);
	}
	{ // LHeap(int(*compare)(const T1 &a, const T1 &b));
		cout << "========================================" << endl;
		LHeap<A> LH1(cmp);
		for (int i = 1; i < 8; i++) {
			LH1.Insert(i);
			LH1.print();
			cout << "----------------------------------------" << endl;
		}
	}
	{ // LHeap(const T1 &rootID, const T2 * const rootRcd = NULL, int(*compare)(const T1 &a, const T1 &b) = dCmp);
		cout << "========================================" << endl;
		int a = 1, b = 2;
		LHeap<A, int> LH1(1, &a, cmp);
		LHeap<A, int> LH3(3, NULL, cmp);
		LHeap<A, int> LH4(4, &b);
		LHeap<A, int> LH5(5);
	}
	{ // LHeap(const T1 &rootID, const T2 &rootRcd, int(*compare)(const T1 &a, const T1 &b) = dCmp);
		cout << "========================================" << endl;
		LHeap<A, int> LH1(1, 2, cmp);
		LHeap<A, int> LH2(2, 3);
	}
	{	// test the merge function, with root set as public member
		Node<A> Na1(3);		Na1.setNpl(1);
		Node<A> Na2(10);	Na2.setNpl(1);
		Node<A> Na3(8);		Na3.setNpl(0);
		Node<A> Na4(21);	Na4.setNpl(0);
		Node<A> Na5(14);	Na5.setNpl(0);
		Node<A> Na6(17);	Na6.setNpl(0);
		Node<A> Na7(23);	Na7.setNpl(0);
		Node<A> Na8(26);	Na8.setNpl(0);
		Na1.AddLft(&Na2);
		Na1.AddRgt(&Na3);
		Na2.AddLft(&Na4);
		Na2.AddRgt(&Na5);
		Na3.AddLft(&Na6);
		Na5.AddLft(&Na7);
		Na6.AddLft(&Na8);

		Node<A> Nb1(6);		Nb1.setNpl(2);
		Node<A> Nb2(12);	Nb2.setNpl(1);
		Node<A> Nb3(7);		Nb3.setNpl(1);
		Node<A> Nb4(18);	Nb4.setNpl(0);
		Node<A> Nb5(24);	Nb5.setNpl(0);
		Node<A> Nb6(37);	Nb6.setNpl(0);
		Node<A> Nb7(18);	Nb7.setNpl(0);
		Node<A> Nb8(33);	Nb8.setNpl(0);
		Nb1.AddLft(&Nb2);
		Nb1.AddRgt(&Nb3);
		Nb2.AddLft(&Nb4);
		Nb2.AddRgt(&Nb5);
		Nb3.AddLft(&Nb6);
		Nb3.AddRgt(&Nb7);
		Nb5.AddLft(&Nb8);

		LHeap<A> LH1(cmp);
		LHeap<A> LH2(cmp);
		LH1.root = &Na1;
		LH2.root = &Nb1;
		//LH1.Merge(&LH2);
		//LH1.print();
		LHeap<A> *LH3 = LH1 + LH2;
		LH3->print();
		//cout << LH1.Pop() << endl;
		//LH1.print();
	}

	system("pause");
}