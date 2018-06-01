#include "ListInt.h"
#include <iostream>

using namespace std;

// Node Block
ListInt::Node::Node(int value)
{
    //cout << "Node C-tor with value: " << value << endl;
    this->_value = value;
    this->_prev = NULL;
    this->_next = NULL;
}

ListInt::Node::Node()
{
    //cout << "Node Default C-tor" << endl;
    _prev = NULL;
    _next = NULL;
}

int &ListInt::Node::value()
{
    //cout << "ValueFunc: " << this->_value << " ";
    return this->_value;
}

int ListInt::Node::value() const
{
    //cout << "ValueFunc C: " << this->_value << " ";
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

//Iterator Block
ListInt::iterator::iterator(Node *node) : _current(node)
{
    //cout << "Iterator C-tor" << endl;
}

ListInt::iterator::~iterator()
{
    //cout << "Iterator D-tor" << endl;
    _current = NULL;
}

ListInt::iterator::iterator()
{
    //cout << "Iterator Default C-tor" << endl;
    _current = NULL;
}

ListInt::iterator::iterator(const iterator &it)
{
    this->_current = it._current;
}

bool ListInt::iterator::valid() const
{
    if (_current != NULL)
    {
        //cout << "Iterator is valid." << endl;
        return true;
    }
    else
    {
        //cout << "Iterator is INvalid." << endl;
        return false;
    }
}

bool ListInt::iterator::invalid() const
{
    if (_current == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int &ListInt::iterator::get()
{
    //cout << "GetFunc: " << this->_current->value()<< " for node:"<< this->_current << endl;
    return this->_current->value();
}

int ListInt::iterator::get() const
{
    //cout << "GetFunc C: " << this->_current->value() << endl;
    return this->_current->value();
}

void ListInt::iterator::prev()
{
    // if(this->_current->prev()!=NULL)
    // {
    //cout << "Prev elem of list" << endl;
    if(this->valid())
    {
        this->_current = this->_current->prev();
    }
    else
    {
        throw 2;
    }
    // }
}

void ListInt::iterator::next()
{
    // if(this->_current->next()!=NULL)
    // {
    //cout << "Next elem of list" << endl;
    if(this->valid())
    {
        this->_current = this->_current->next();
    }
    else
    {
        throw 1;
    }
    // }
}

bool ListInt::iterator::equal(const iterator &other) const
{
    if (this->_current->value() == other._current->value())
    {
        return true;
    }
    else
    {
        return false;
    }
}

ListInt::ListInt() : _head(NULL), _tail(NULL), _size(0)
{
    //cout << "List Default C-tor" << endl;
    //cout << " head:" << _head << ", tail:" << _tail << endl;
    //cout << " size = " << _size << endl;
}

ListInt::~ListInt()
{
    //cout << "List D-tor" << endl;
    for (ListInt::iterator it = head(); it.valid(); it.next())
    {
        Node *node = it._current;
        //cout << "Delete node:" << node << endl;
        delete node;
    }
}

void ListInt::push_back(int val)
{
    Node *node = new Node(val);
    node->next() = NULL;
    if (empty())
    {
        //cout << "Append node: "<< node <<" values _head and _tail for it" << endl;
        this->_head = node;
        this->_tail = node;
        this->_size++;
    }
    else
    {
        //cout << "Append node: " << node << " value _tail for it" << endl;
        node->prev() = this->_tail;
        this->_tail->next() = node;
        this->_tail = node;
        this->_size++;
    }
}

bool ListInt::empty() const
{
    if (this->size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t ListInt::size() const
{
    return _size;
}

ListInt::iterator ListInt::head()
{
    //cout << "Init head iterator" << endl;
    //cout << "Head: " << _head << endl;
    return ListInt::iterator(_head);
}
ListInt::iterator ListInt::tail()
{
    //cout << "Init tail iterator" << endl;
    //cout << "Tail: " << _tail << endl;
    return ListInt::iterator(_tail);
}

void ListInt::pop_back()
{
    //cout << "Pop_back Func. Tail has been pop : " << this->_tail << endl;
    if(this->size() > 1)
    {
        this->_tail = this->_tail->prev();
        delete this->_tail->next();
        this->_size -= 1;
    }
    else
    {
        ListInt::Node* tmp  = this->_tail;
        delete tmp;
        this->_tail = NULL;
        this->_head = NULL;
        this->_size = 0;
    }
}

void ListInt::reverse()
{
    //cout << "Reverse List" << endl;
    Node *tmp;
    for (ListInt::iterator it1 = head(); it1.valid(); it1.prev())
    {
        tmp = it1._current->next();
        it1._current->next() = it1._current->prev();
        it1._current->prev() = tmp;
    }
    tmp = _head;
    _head = _tail;
    _tail = tmp;
}

void ListInt::grab_and_append(ListInt &from)
{
    if(from.size() > 0)
    {
        //cout << "Grab&Append Func: " << endl;
        this->_tail->next() = from._head;
        from._head->prev() = this->_tail;
        this->_size += from._size;
        from._size = 0;
        from._head = NULL;
        this->_tail = from._tail;
        from._tail = NULL;
    }
}

ListInt::iterator ListInt::insert(ListInt::iterator pos, int value)
{
    ListInt::Node *node = new ListInt::Node(value);
    node->prev() = pos._current->prev();
    pos._current->prev()->next() = node;
    pos._current->next()->prev() = node;
    node->next() = pos._current;
    //cout << "InsertFunc new Node("<<value<<")" <<endl;
    return pos;
}

ListInt::iterator ListInt::erase(ListInt::iterator pos)
{
    pos._current->prev()->next() = pos._current->next();
    pos._current->next()->prev() = pos._current->prev();
    _size -= 1;
    pos._current = NULL;
    //cout << "Erase Func" << endl;
    return pos;
}

// void ListInt::sort()
// {
//     if(this->empty())
//         return;
//     ListInt::iterator it1 = this->head();
//     size_t it1_count = 1;

//     ListInt::iterator it2 = this->tail();
//     size_t it2_count = this->size();

//     size_t mid_size = this->size() / 2 + this->size() % 2;

//     size_t counter = 1;
//     ListInt::iterator tmp_it = this->head();
//     for(; tmp_it.valid(); tmp_it.next())
//     {
//         if(counter != mid_size)
//         {
//             counter++;
//         }
//         else
//         {
//             break;
//         }
//     }

//     do
//     {
//         while(it1.get() < tmp_it.get())
//         {
//             it1.next();
//             it1_count++;
//         }

//         while(it2.get() > tmp_it.get())
//         {
//             it2.prev();
//             it2_count--;
//         }

//         if(it1_count <= it2_count)
//         {
//             int tmp = it1.get();
//             it1.get() = it2.get();
//             it2.get() = tmp;

//             it1_count++;
//             it1.next();

//             it2_count--;
//             it2.prev();
//         }
//     } while (it1_count <= it2_count);

//     if(it2_count > 0)
//     {
//         ListInt* l1 = new ListInt(); 
//         //Сделать список c первого по it2_count+1 элемент старого списка, сделать для него .sort()
//         int counter1 = 1;
//         for(ListInt::iterator tmp_it = this->head(); tmp_it.valid(); tmp_it.next())
//         {
//             if(counter1 > it2_count + 1)
//             {
//                 break;
//             }
//             l1->push_back(tmp_it.get());
//             counter1++;
//         }
//         l1->sort();
//     }

//     if(it1_count < this->size())
//     {
//         ListInt* l2 = new ListInt();
//         int counter2 = 1;
//         //Сделать список с it1_count до конца старого списка, сделать для него .sort()
//         for(ListInt::iterator tmp_it = this->head(); tmp_it.valid(); tmp_it.next())
//         {
//             if(counter2 > it1_count)
//             {
//                 counter2++;
//                 l2->push_back(tmp_it.get());
//             }
//         }
//         l2->sort();
//     }
    
//     //cout << "Test Sort" << endl;
// }

void ListInt::cut_and_push(ListInt& list,iterator pos)
{
	//cout << "C_A_P" << endl;
	if(pos.valid())
	{
		Node *tmp;
		tmp = this->cut(pos);
		list.push_back(tmp);
	}
	else
	{
		throw 4;
	};
}
void ListInt::push_back(Node *node)
{
	//cout << "PB_N" << endl;
	node->next() = NULL;

	if(_head!=NULL)
	{
		node->prev() = _tail;
		_tail->next() = node;
		_tail = node;
	}
	else
	{
		node->prev() = NULL;
		_head = node;
		_tail = node;
	}
	_size++;
}

ListInt::Node* ListInt::cut(iterator pos)
{
	//cout << "CUT" << endl;
	if(pos.valid())
	{	
		Node *tmp = pos._current;

		if(!pos.equal(this->head()) && !pos.equal(this->tail()))
		{
			tmp->prev()->next() = tmp->next();
			tmp->next()->prev() = tmp->prev();
		}
		if(pos.equal(this->head()) && !pos.equal(this->tail()))
		{
			this->_head = tmp->next();
			this->_head->prev() = NULL;
		}	
		if(pos.equal(this->tail()) && !pos.equal(this->head()))
		{
			this->_tail = tmp->prev();
			this->_tail->next() = NULL;
		}
		if(pos.equal(this->tail()) && pos.equal(this->head()))
		{
			this->_tail = NULL;
			this->_head = NULL;
		}
		this->_size--;
		tmp->nullNP();
		return tmp;
	}
	else
	{
		throw 4;
	};	
}
void ListInt::Node::nullNP()
{
		this->prev() = NULL;
		this->next() = NULL;
}

void ListInt::sort()
{
    //cout << "q_sort" << endl;
    if(this->_size>1)
    {
        ListInt tmp_l;
        iterator pos;
        Node *fix, *tmp;
        fix = this->cut(this->tail());
        pos = this->tail();
   
        while(pos.valid())
        {  
            if(pos._current->value() >= fix->value())
            {
                tmp = pos._current->prev();
                this->cut_and_push(tmp_l,pos);
                pos._current = tmp;
            }
            else
            {
                pos.prev();
            };
        }
       
        this->sort();
        tmp_l.sort();
       
        this->push_back(fix);
        this->grab_and_append(tmp_l);
    }
}

int main()
{
    cout << "------------------------------------------" <<endl;
    cout<<"Start Main" << endl;
    ListInt l;
    l.push_back(10);
    l.push_back(2);
    l.push_back(8);
    l.push_back(4);

    cout << endl << "First Show" << endl;
    for(ListInt::iterator it(l.head()); it.valid(); it.next())
    {
		cout << it.get() << endl;
    }

    l.sort();

    cout << endl << "Second Show" << endl;
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
