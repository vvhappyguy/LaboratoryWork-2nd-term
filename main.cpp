#include <iostream>
#include "list.h"

using namespace std;

int main(int argc, char* argv[])
{
	ListInt l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);

	for(ListInt::iterator it = l.head(); l.valid(); l.next())
		cout << l.get() << endl;

	l.reverse();

	for(ListInt::iterator it = l.head(); l.valid(); l.next())
		cout << l.get() << endl;

	l.sort();

	for(ListInt::iterator it = l.head(); l.valid(); l.next())
		cout << l.get() << endl;

	cout << "size: " << l.size() << endl;
	return 0;
}
