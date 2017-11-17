#ifndef memory_bound_h
#define memory_bound_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "eratosthene.h"

// Class List where all members of this list are prime.
class Node{
	private:
		unsigned int number;
		Node *next;
	public:
		Node(unsigned int a);
		~Node();
		unsigned int getNumber() const;
		Node* getNext() const;
		void setNext(Node *n);
};

class List
{
	protected:
		Node *head;
	public:
		List();
		~List();
		Node* getHead() const;
        void setHead(Node* n);
};
std::ostream& operator<<(std::ostream& flux, const List& l);

// #### MEMORY-BOUND #### //
void memory_bound(unsigned int nbr, List* l);

#endif
