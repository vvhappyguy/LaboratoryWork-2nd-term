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
    // if(this->_current->prev()!=NULL)
    // {
        cout << "Prev elem of list" << endl;
        this->_current = this->_current->prev();
    // }
}

void ListInt::iterator::next()
{
    // if(this->_current->next()!=NULL)
    // {
        cout << "Next elem of list" << endl;
        this->_current = this->_current->next();
    // }
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
    cout << "List D-tor" << endl;
    for(ListInt::iterator it = head();it.valid();it.next())
    {
         Node* node = it._current;
         cout << "Delete node:" << node << endl;
         delete node;
    }
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
    if(this->size() == 0){return true;}
    else{return false;}
}

size_t ListInt::size() const
{
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

void ListInt::pop_back()
{
    cout << "Pop_back Func. Tail has been pop : " << this->_tail << endl;
    this->_tail = this->_tail->prev();
    delete this->_tail->next();
    this->_tail->next() = NULL;
}

void ListInt::reverse()
{
    cout << "Reverse List" << endl;
    int counter = 1;
    Node *tmp;
    for(ListInt::iterator it1 = head();it1.valid();it1.prev())
    {
        tmp = it1._current->next();
        it1._current->next() = it1._current->prev();
        it1._current->prev() = tmp; 
    }
    tmp = _head;
    _head = _tail;
    _tail = tmp;
}

void ListInt::grab_and_append(ListInt& from)
{
    cout << "Grab&Append Func: " << endl;
    this->_tail->next() = from._head;
    from._head->prev() = this->_tail;
    this->_size += from._size;
    from._size = 0;
    from._head = NULL;
    this->_tail = from._tail;
    from._tail = NULL;
}

ListInt::iterator ListInt::insert(ListInt::iterator pos, int value)
{
    ListInt::Node *node = new ListInt::Node(value);
    node->prev() = pos._current->prev();
    pos._current->prev()->next() = node;
    pos._current->next()->prev() = node;
    node->next() = pos._current;
    cout << "InsertFunc new Node("<<value<<")" <<endl;
}

ListInt::iterator ListInt::erase(ListInt::iterator pos)
{
    pos._current->prev()->next() = pos._current->next();
    pos._current->next()->prev() = pos._current->prev();
    _size-=1;
    pos._current = NULL;
    cout << "Erase Func" << endl;
}




int main()
{
    cout << "------------------------------------------" <<endl;
    cout<<"Start Main" << endl;
    ListInt l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    

    ListInt l2;
    l2.push_back(10);

    for(ListInt::iterator it(l.head()); it.valid(); it.next())
    {
		cout << it.get() << endl;
    }

    l.grab_and_append(l2);
    
    ListInt::iterator it(l.head());
    it.next();
    it.next();
    l.insert(it,123);
    it.next();
    l.erase(it);
    it.next();
    




    cout << endl << "First Show" << endl;
    for(ListInt::iterator it(l.head()); it.valid(); it.next())
    {
		cout << it.get() << endl;
    }

    // l.pop_back();
    // l.push_back(5);

    // cout << endl << "Second Show" << endl;
    // for(ListInt::iterator it(l.head()); it.valid(); it.next())
    // {
	// 	cout << it.get() << endl;
    // }

    // l.reverse();
    // cout << endl << "Third Show" << endl;
    // for(ListInt::iterator it(l.head()); it.valid(); it.next())
    // {
	// 	cout << it.get() << endl;
    // }
    // cout << "End Main" << endl;
    cout << "------------------------------------------" <<endl;
    return 0;
}
