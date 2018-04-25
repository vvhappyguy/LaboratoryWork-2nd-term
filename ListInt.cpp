#include <cstlib>

using namespace std;

//Node c-tors, d-tors and functions
ListInt::Node::Node():_prev(NULL),_next(NULL),_value(0){}
ListInt::Node::Node(int value):_prev(NULL),_next(NULL),_value(value){}
int ListInt::Node::value() const{return this->_value;}
int &ListInt::Node::value(){return this->_value;}
ListInt::Node *&ListInt::Node::prev(){return this->_prev;}
ListInt::Node *&ListInt::Node::next(){return this->_next;}

/*
*
*
*/

//Iterator c-tor, copy-tor and d-tor
ListInt::iterator::iterator(Node *node){this->*_current = *node;}
ListInt::iterator::iterator(const iterator& iter):_current(iter._current){}
~ListInt::iterator::iterator(){}
bool valid() const {return _current != NULL ? true : false;}
bool 

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
