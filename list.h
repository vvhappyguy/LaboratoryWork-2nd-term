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
				void next(); //Why it returned void?
				void prev(); //Why it returned void? Maybe it may return iterator*
				bool valid() const; //Checking for iterator life
				int& get(); //get wr-method
				int get() const; //get only-read method
				bool equal(/*const interator*/) const; //Compare two iterators - MISTAKE HERE
		};

		void push_back(); //Push to tail of List new element
		iterator begin(); //Link for List's begin
		iterator end(); //Link for List's end
		iterator last(); //Link to next-end
		iterator before(); //Link to prev.begin 
		size_t size() const; //size of List
		bool empty() const; //checking for list isn't empty
		//<c-tors>
		//<d-tors>
		void insert(iterator, int); //insert new iterator to "int" position
		void erase(iterator); //remove current iterator from List
};
