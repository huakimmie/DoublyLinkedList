#ifndef LinkedList_H
#define LinkedList_H
#include <iostream>
namespace linked {
	class LinkedList;
	class const_iterator;

	class node {
		friend class LinkedList; /* LinkedList needs to construct nodes and to
								 know next/prev of node for insertions, deletions, etc. */
		friend class iterator; // iterators need to know next/prev to move, etc.
		friend class const_iterator;
	private:
		int val; // the data
		node *prev, *next; // previous and next nodes
		node(int i); // constructor to create new node is PRIVATE // declare the node
	};

	class iterator {
		friend class LinkedList;
	public:
		iterator& operator++(); // prefix ++
		iterator operator++(int dum); // postfix ++
		iterator& operator--(); // prefix - -
		iterator operator--(int dum); // postfix - -
		int& operator*(); // dereferencing operator (unary)
		bool operator==(const iterator& rhs) const; // comparison
		node* get_curr() const;
		const LinkedList* get_container() const;
	private:
		node *curr; // currently managed node
		const LinkedList *container; // the iterator should not change the list
									 // constructor: requires a node and list to point to
		iterator(node* n, const LinkedList* ell);
	};

	class const_iterator {
		friend LinkedList;
	public:
		const_iterator(iterator it); //conversion
		node* get_curr() const; //accessors
		const_iterator& operator++(); // prefix ++
		const_iterator operator++(int); // postfix ++
		const_iterator& operator--(); // prefix - -
		const_iterator operator--(int); // postfix - -
		int operator*() const; // dereferencing operator (unary)
		bool operator==(const const_iterator&) const; // comparison
	private:
		node *curr; // currently managed node
		const LinkedList *container; // the iterator should not change the list
									 // constructor: requires a node and list to point to
		const_iterator(node* n, const LinkedList* ell);
	};
	 
	bool operator!=(const iterator&, const iterator&); //not equal
	bool operator!=(const const_iterator&, const const_iterator&); //not equal


	class LinkedList {

		friend iterator;
		friend const_iterator;
	private:
		node *first, *last; // pointers to first and last nodes

	public:
		LinkedList(); //default
		LinkedList(const LinkedList& rhs); //copy
		LinkedList(LinkedList&&); //move
		~LinkedList(); //destructor
		LinkedList& operator=(LinkedList rhs); //assigment operator

		void push_back(int); // append to end
		void pop_back(); // remove from the end
		void push_front(int); // add to beginning
		void pop_front(); // remove from beginning
		const_iterator begin() const; // obtain const begin iterator
		const_iterator end() const; // obtain const iterator pointing past end
		iterator begin(); //begin iterator
		iterator end(); //end iterator
		void insert(iterator, int); // insert value before current position
		void erase(iterator); // erase value at position
		int size(); //function to get size
		void sort(); //function to sort
	};

	std::ostream& operator<<(std::ostream& out, LinkedList list); //operator to output LinkedList
	bool seqSearch(const_iterator a, const_iterator b, int value); //seqSearch fucntion
}

#endif
