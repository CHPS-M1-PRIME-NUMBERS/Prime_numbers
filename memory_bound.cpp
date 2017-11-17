#include "memory_bound.h"

// #### NODE #### //

Node::Node(unsigned int a){ number = a; next = NULL; }
Node::~Node(){ delete next; }
unsigned int Node::getNumber() const{ return number; }
Node* Node::getNext() const{ return next; }
void Node::setNext(Node *n){ next = n; }

// #### LIST #### //

List::List(){ head = NULL; }
List::~List(){ delete head; }
Node* List::getHead() const{ return head; }
void List::setHead(Node* n) { head = n; }
std::ostream& operator<<(std::ostream& flux, List& l)
{
	while(l.getHead() != NULL)
	{
		flux << l.getHead()->getNumber() << ' ';
		l.setHead(l.getHead()->getNext());
	}
	flux << std::endl;
	return flux;
}


// #### MEMORY-BOUND #### //

void memory_bound(unsigned int nbr, List* l){ // Return a list of prime numbers between 2 and nbr.

    bool* isPrime;
    unsigned int i;
    isPrime = eratosthene(nbr); // Application of the eratosthene sieve to find the prime numbers

    for(i = 0; i <= nbr; i++){
        if (isPrime[i]){
            if (l->getHead() != NULL){
		        Node* tmp = new Node(i);
		        tmp->setNext(l->getHead());
                l->setHead(tmp);
            }
            else {
                Node* tmp = new Node(i);
		        l->setHead(tmp);
            }
        }
    }
    delete [] isPrime;
}

int main(){
    List l;
    memory_bound(1039, &l);
    std::cout << l;

    return 0;
}
