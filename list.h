#pragma once

class List{
		//Can we use struct, what's reason to use "class" for Node?
		class Node
		{
			private:
				short unsigned _value; //Value of array's element
				Node * head; //Link to previous Node
				Node * tail; //Link to next Node
			public:
				Node ();
		}; 
	public:
		class iterator{
				Node* current; //Current Node with two links and value
			public:
				void next();//
				void prev();
				bool valid() const;
				int& get();
				int get() const;
				bool equal(/*const interator*/) const; //Compare two iterators - MISTAKE HERE
		};

		void push_back(); //Push to tail of List new element
		iterator begin(); //Link for List's begin
		iterator end(); //Link for List's end
		iterator last(); 
		iterator before(); 
		size_t size() const; 
		bool empty() const; 
		//<c-tors>
		//<d-tors>
		void insert(iterator, int);
		void erase(iterator);
};
