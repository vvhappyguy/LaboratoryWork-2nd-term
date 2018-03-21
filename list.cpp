#include "list.h"
#include <iostream>
#include "malloc.h"

using namespace std;

//Node c-tors, d-tors and functions
ListInt::Node::Node()
{
    int _value;
    Node *_prev = nullptr;
    Node *_next = nullptr;
}

ListInt::Node::Node(int value)
{
    p = prev();
    Node node = new Node;
    if (p->_prev != nullptr)
    {
        p->_next = node;
        node->_prev = p;
        node->_next = nullptr;
        node->_value = value;
    }
    else
    {
        node->_prev = nullptr;
        node->_next = nullptr;
        node->_value = vlaue;
    }
}

int ListInt::Node::value() const
{
    return this->_value;
}

int &ListInt::Node::value()
{
    return this->_value;
}

ListInt::Node *&ListInt::Node::prev()
{
    return this->_prev;
}

ListInt::Node *&ListInt::Node::next()
{
    return this->_next;
}

/*
*
*
*/

//Iterator c-tor, copy-tor and d-tor
ListInt::iterator::iterator(Node *node)
{
    this->*_current = *node;
}

ListInt::iterator::iterator(const iterator &)
{
    iter = new iterator;
    iter->_current = iterator->_current;
}

~ListInt::iterator::iterator()
{
}

bool valid() const
{
    return _current != NULL ? true : false;
}

/* STD C-tor for ListInt*/
ListInt::ListInt()
{
    ListInt *list = new ListInt;
    Node *node = nullptr;
    iterator iterator = ListInt::iterator(node);
    size_t size = 0;
}

ListInt::~ListInt()
{
}