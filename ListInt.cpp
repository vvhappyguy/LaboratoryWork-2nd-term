#include "ListInt.h"
#include <iostream>

using namespace std;

ListInt::Node::Node(int value)
{
    cout << "Node C-tor with value: " << value << endl;
    int _value = value;
    Node *_prev = nullptr;
    Node *_next = nullptr;
}

ListInt::Node::Node()
{
    cout << "Node Default C-tor" << endl;
}

int& ListInt::Node::value()
{
    return this->_value;
}

int  ListInt::Node::value() const
{
    return this->_value;
}

ListInt::Node*& ListInt::Node::prev()
{
    return this->_prev;
}

ListInt::Node*& ListInt::Node::next()
{
    return this->_next;
}

ListInt::ListInt::ListInt()
{
    cout << "List Default C-tor" << endl;
    Node* _head = nullptr;
    Node* _tail = nullptr;
    size_t _size = 0;
    cout << " head:" << _head << ", tail:" << _tail << endl;
    cout << " size = " << _size << endl;
}

ListInt::ListInt::~ListInt()
{
    cout << "List D-tor" << endl;
}



int main()
{
    ListInt l;
    
    return 0;
}