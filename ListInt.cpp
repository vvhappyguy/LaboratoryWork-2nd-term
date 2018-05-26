#include "ListInt.h"
#include <iostream>

using namespace std;

// Node Block
ListInt::Node::Node(int value)
{
    cout << "Node C-tor with value: " << value << endl;
    this->_value = value;
    this->_prev = NULL;
    this->_next = NULL;
}

ListInt::Node::Node()
{
    cout << "Node Default C-tor" << endl;
    _prev = NULL;
    _next = NULL;
}

int& ListInt::Node::value()
{
    cout << "ValueFunc: " << this->_value << " ";
    return this->_value;
}

int  ListInt::Node::value() const
{
    cout << "ValueFunc C: " << this->_value << " ";
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

//Iterator Block
ListInt::iterator::iterator(Node* node):_current(node){
    cout << "Iterator C-tor" << endl;
}

ListInt::iterator::~iterator(){
    cout << "Iterator D-tor" << endl;
    _current = NULL;
}

ListInt::iterator::iterator(){
    cout << "Iterator Default C-tor" << endl;
    _current = NULL;
}

//!!!
ListInt::iterator::iterator(const iterator& it)
{
    this->_current = it._current;
}

bool ListInt::iterator::valid() const
{
    if (_current != NULL)
    {
        cout << "Iterator is valid." << endl;
        return true;
    }
    else
    {
        cout << "Iterator is INvalid." << endl;
        return false;
    }
}

bool ListInt::iterator::invalid() const
{
    if(_current == NULL) {return true;}
    else {return false;}
}

int& ListInt::iterator::get()
{
    cout << "GetFunc: " << this->_current->value()<< " for node:"<< this->_current << endl;
    if (this->valid())
    {
        return this->_current->value();
    }
}

int ListInt::iterator::get() const
{
    cout << "GetFunc C: " << this->_current->value() << endl;
    if(this->valid()){
        
        return this->_current->value();
    }
}

void ListInt::iterator::prev()
{
    cout << "Prev elem of list" << endl;
    this->_current = this->_current->prev();
}

void ListInt::iterator::next()
{
    cout << "Next elem of list" << endl;
    this->_current = this->_current->next();
}

bool ListInt::iterator::equal(const iterator& other) const
{
    if(this->_current->value() == other._current->value()){
        return true;
    } else {
        return false;
    }
}




ListInt::ListInt():_head(NULL),_tail(NULL),_size(0)
{
    cout << "List Default C-tor" << endl;
    cout << " head:" << _head << ", tail:" << _tail << endl;
    cout << " size = " << _size << endl;
}

ListInt::~ListInt()
{

    // for(ListInt::iterator it = head();it.valid();it.next())
    // {
    //     Node* node = it._current;
    //     delete node;
    // }
    cout << "List D-tor" << endl;
}

void ListInt::push_back(int val)
{
    Node* node = new Node(val);
    node->next() = NULL;
    if (empty()){
        cout << "Append node: "<< node <<" values _head and _tail for it" << endl;
        this->_head = node;
        this->_tail = node;
        this->_size++;
    }
    else {
        cout << "Append node: " << node << " value _tail for it" << endl;
        node->prev() = this->_tail;
        this->_tail->next() = node;
        this->_tail = node;
        this->_size++;
    }
}

bool ListInt::empty() const
{
    //cout << this->size() << endl;
    if(this->size() == 0){return true;}
    else{return false;}
}

size_t ListInt::size() const
{
    //cout << "Size(): " << _size << endl;
    return _size;
}

ListInt::iterator ListInt::head()
{
    cout << "Init head iterator" << endl;
    cout << "Head: " << _head << endl;
    return ListInt::iterator(_head); 
}
ListInt::iterator ListInt::tail()
{
    cout << "Init tail iterator" << endl;
    cout << "Tail: " << _tail << endl;
    return ListInt::iterator(_tail);
}

ListInt::iterator ListInt::insert(iterator pos, int value)
{

}

void ListInt::insert(iterator pos, Node* node)
{

}

void ListInt::pop_back()
{

}




int main()
{
    ListInt l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(2);
    l.push_back(5);
    cout << "Empty: " << l.empty() << endl;
    cout << "Size: " << l.size() << endl;
    
    for(ListInt::iterator it(l.head()); it.valid(); it.next())
    {
		cout << it.get() << endl;
    }
    return 0;
}
