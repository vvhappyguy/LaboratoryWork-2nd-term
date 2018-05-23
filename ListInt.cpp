#include "ListInt.h"
#include <iostream>

using namespace std;

// Node Block
ListInt::Node::Node(int value)
{
    cout << "Node C-tor with value: " << value << endl;
    int _value = value;
    _prev = NULL;
    _next = NULL;
}

ListInt::Node::Node()
{
    cout << "Node Default C-tor" << endl;
    _prev = NULL;
    _next = NULL;
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

//Iterator Block
ListInt::iterator::iterator(Node* node){
    cout << "Iterator C-tor" << endl;
    Node* _current = node;
}

ListInt::iterator::~iterator(){
    cout << "Iterator D-tor" << endl;
    delete _current;
}

ListInt::iterator::iterator(){
    cout << "Iterator Default C-tor" << endl;
    _current = NULL;
}

//!!!
ListInt::iterator::iterator(const iterator& it)
{
    Node* _current;
    cout << "Iterator Copy-tor" << endl;
    this->_current = it._current;
}

bool ListInt::iterator::valid() const
{
    if (_current != NULL){return true;}
    else {return false;};
}

bool ListInt::iterator::invalid() const
{
    if(_current == NULL) {return true;}
    else {return false;}
}

int& ListInt::iterator::get()
{
    if (this->valid())
    {
        return this->_current->value();
    }
}

int ListInt::iterator::get() const
{
    if(this->valid()){
        return this->_current->value();
    }
}

void ListInt::iterator::prev()
{
    this->_current = this->_current->prev();
}

void ListInt::iterator::next()
{
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
    if (empty()){
        this->_head = node;
        this->_tail = node;
        this->_size++;
    }
    else {
        Node* tn = this->_tail;
        node->prev() = tn;
        tn->next() = node;
        node->next() = NULL;
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
    ListInt::iterator* it = new ListInt::iterator(_head);
    return *(it);
}
ListInt::iterator ListInt::tail()
{
    return this->_tail;
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
    l.push_back(2);
    cout << "Empty: " << l.empty() << endl;
    cout << "Size: " << l.size() << endl;
    
    for(ListInt::iterator it = l.head(); it.valid(); it.next())
		cout << it.get() << endl;
    //ListInt::iterator it1 = ListInt::iterator();
    // ListInt::iterator it2 = ListInt::iterator();
    // cout << it1.valid() << it1.invalid() << endl;
    //cout << it1.equal(it2) << endl;
    return 0;
}
