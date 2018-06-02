#include <iostream>
#include "ListInt.h"

using namespace std;

int main(int argc, char* argv[])
{
	 
	
	ListInt l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);

	for(ListInt::iterator it = l.head(); it.valid(); it.next())
		cout << it.get() << endl;

	ListInt::iterator it = l.tail();
    l.erase(it);

    cout << endl;
	for(ListInt::iterator it = l.head(); it.valid(); it.next())
		cout << it.get() << endl;

	// l.sort();

	// for(ListInt::iterator it = l.head(); l.valid(); l.next())
	// 	cout << l.get() << endl;

	// cout << "size: " << l.size() << endl;
	return 0;
}