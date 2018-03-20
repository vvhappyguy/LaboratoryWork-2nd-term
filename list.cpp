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
    Node *temp, *p;
    temp = new Node;
    temp = (Node*)malloc(sizeof(Node));
    p = next();
    temp->_value = value;
    temp->_next = p;
    temp->_prev = prev();
    if(p != nullptr)
    {
        p->_prev = temp;
    }
}

int ListInt::Node::value ()const
{
    return this->_value;
}

int& ListInt::Node::value()
{
    return this->_value;   
}

ListInt::Node*& ListInt::Node::prev(){
    return this->_prev;
}

ListInt::Node*& ListInt::Node::next(){
    return this->_next;
}


ListInt::iterator::iterator(Node *node)
{
    
}

/* STD C-tor for ListInt*/
ListInt::ListInt()
{
    ListInt* list = new ListInt;
    Node *node = nullptr;
    iterator iterator = ListInt::iterator(node);
    size_t size = 0;
}

ListInt::~ListInt()
{

}