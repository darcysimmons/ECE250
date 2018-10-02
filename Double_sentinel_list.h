/*****************************************
 * UW User ID:  drasimmo #20719426
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

//

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////


//constructor that creates an empty linked list
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( new Double_node(Type(), nullptr, nullptr) ), 
list_tail( new Double_node(Type(), nullptr, nullptr) ),
list_size( 0 )
{
	//set head next node to be tail
	list_head->next_node = list_tail;

	//set tail previous node to be head
	list_tail->previous_node = list_head;

}

// constructor that creates a copy of a linked list which is passed into the constructor
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( new Double_node(Type(), nullptr, nullptr) ), 
list_tail( new Double_node(Type(), nullptr, nullptr) ),
list_size( 0 )
{
	//set head next node to be tail
	list_head->next_node = list_tail;

	//set tail previous node to be head
	list_tail->previous_node = list_head;

	//set each node to be a copy of each node in the list that was passed in
	if (!list.empty()) {
		for( auto *ptr = list.begin(); ptr != list.end(); ptr = ptr->next() ) {
			push_back(ptr->node_value);
		}	
	}
}

// moves the contents from a list passed into the constructor to an empty linked list
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( new Double_node(Type(), nullptr, nullptr) ),
list_tail( new Double_node(Type(), nullptr, nullptr) ),
list_size( 0 )
{
	//exit if the list being passed in is empty
	if (list.empty()) {
		return;
	}

	//set head next node to be tail
	list_head->next_node = list_tail;

	//set tail previous node to be head
	list_tail->previous_node = list_head;

	//swtich the empty list with the list passed in 
	swap(list); 
}

// destructor
template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	
	//remove the contents of this list until it is empty
	while(!empty()) {
		pop_front();
	}

	//deallocate memory for the head and tail
	delete list_head;
	delete list_tail;


}

// returns the list of the linked list
template <typename Type>
int Double_sentinel_list<Type>::size() const {

	return list_size;
}

// returns whether or not the linked list is empty
template <typename Type>
bool Double_sentinel_list<Type>::empty() const {

	//return true if the list is empty
	if(list_size == 0) {
		
		return true;

	}

	//return false if the list is not empty
	else{

		return false;
	
	}
}

// returns the value of the first item in the linked list
template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	
	if(empty()) {

		throw EXCEPTION_H::underflow();

	}

	//if the list is not empty, return the first node after the head
	else {

		return list_head->next_node->node_value;

	}
}

// returns the value of the last item in the linked list 
template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	
	if(empty()) {

		throw EXCEPTION_H::underflow();

	}

	//if the list is not empty, return the last node before the tail
	else {

		return list_tail->previous_node->node_value;

	}
}

// returns a pointer to the first list item for iteration purposes
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {

	return list_head->next();
}

// returns the tail of the list for iteration purposes
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {

	return list_tail;
}

// returns the list item before the tail for reverse iteration purposes
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {

	return list_tail->previous();
}

// returns the head of the list for iteration purposes
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	
	return list_head;
}

// return the first node in the list with a value equal to the argument "obj". If there does not exist a node with the value "obj", return the tail
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	
	//iterate through the list starting at the first node after the head
	for( auto *ptr = begin(); ptr != end(); ptr = ptr->next() ) {
		
		//return the pointer to the node if its node value is equal to "obj"
		if(ptr->node_value == obj) 
			return ptr;
		
	}

	// if a node with a value equal to "obj" is not found, return the list tail
	return end();
}

// return the number of items in the list with a value of "obj"
template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	
	// introduce a counter to count the number of node with a value of "obj"
	int counter = 0;

	// iterate through the list beginning at the first node after the head
	for( auto *ptr = begin(); ptr != end(); ptr = ptr->next() ) {
		
		// if a node is found whose value is equal to "obj" then increment the counter
		if(ptr->value() == obj) 
			counter++;
	}

	// return the number of nodes whose value is equal to "obj"
	return counter;
}

//swap the list with the list argument
template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// operator=( Double_sentinel_list<Type> rhs ) : The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	
	swap( rhs );

	return *this;
}

// operator=( Double_sentinel_list<Type> &&rhs ) : The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	
	swap( rhs );

	return *this;
}

// push a node to the front of the list
template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	
	// allocate memory for the new node being pushed in
	Double_node *push_node = new Double_node( obj , list_head , list_head->next_node ); 
	
	//set the previous value of the previous first node to point to the node being pushed in
	list_head->next_node->previous_node = push_node;

	// set the next value of the head to the node being pushed in
	list_head->next_node = push_node;

	//increment the list size
	list_size++;
}

// push a node to the back of the list
template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	
	// allocate memory for the node being pushed in
	Double_node *push_node = new Double_node( obj, list_tail->previous() , list_tail ); 

	// set the next value of the previous last node to point to the node being pushed in
	list_tail->previous_node->next_node = push_node;

	// set the previous value of the tail to the node being pushed in
	list_tail->previous_node = push_node;

	// increment the list size
	list_size++;
}

// pop a node from the front of the list
template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
		
	if(empty()) {

		throw EXCEPTION_H::underflow();

	}

	//	if list isn't empty, pop the first node after the head
	else {

		// create a temporary node to point to the node being removed
		Double_node* temp = list_head->next_node;

		// set the previous value of the new first node to the head
		temp->next_node->previous_node = list_head;

		// set the next value of the head to equal the node after the node being removed
		list_head->next_node = temp->next_node;

		// deallocate memory for the temporary node 
		delete temp;

		//decrement the list size
		list_size--;
	}
}

// pop a node from the back of the list
template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	
	if(empty()) {

		throw EXCEPTION_H::underflow();

	}

	//	if list isn't empty, pop the last node before the tail
	else {

		// create a temporary node to point to the node being removed
		Double_node* temp = list_tail->previous_node;

		// set the next value of the new last node to the tail
		temp->previous_node->next_node = list_tail;

		// set the previous value of the tail to equal the node before the node being removed		
		list_tail->previous_node = temp->previous_node;

		// deallocate memory for the temporary node 	
		delete temp;

		//decrement the list size
		list_size--;

	}
}

// delete any node with a value equal to obj
template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	
	// declare a counter
	int count = 0;

	// set a pointer to the first node after the head
	auto *ptr = begin();

	// iterate to find a node with a value equal to "obj"
	while(ptr != end()){

		if (ptr->node_value == obj) {

			// declare a temporary pointer
			Double_node *temp = ptr;

			//set the next value of the node previous to the node being popped
			ptr->previous_node->next_node = ptr->next_node;

			//set the previous value of the node after the node being popped
			ptr->next_node->previous_node = ptr->previous_node;

			//increment the counter
			count++;

			//decrement the list size
			list_size--;

			//increment the pointer to the next node in the linked list
			ptr = ptr->next();

			// deallocate the memory for the previous pointer
			delete temp;

		}
	}

	//return the new size of the list
	return count;
}

// constructor that creates a double node pointing to nothing
template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),
next_node( nullptr )
{
	//initialize the values for the node
	previous_node = pn;
	next_node = nn;
	node_value = nv;
}

// returns the value of a node
template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {

	return node_value; 
}

// returns the previous node of a node
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	
	return previous_node;
}

// returns the next node of a node 
template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {

	return next_node;

}

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif