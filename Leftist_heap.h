
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  drasimmo @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}

// destructor
template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  
}

// return whether or not the heap is empty
template <typename Type>
bool Leftist_heap<Type>::empty() const {
	return ( root_node == nullptr );
}

// returns the number of elements in the heap
template <typename Type>
int Leftist_heap<Type>::size() const {
	return heap_size;
}

// returns the null path length of the root node
template <typename Type>
int Leftist_heap<Type>::null_path_length() const {
	
	// if a node is null, then it's null path length is -1
	if (empty()) {
		return -1;
	}

	// otherwise return the heap null path length of the root node
	else {
		return root_node->null_path_length();

	}
}

// return the amount of instances of the argument in the heap
template <typename Type>
int Leftist_heap<Type>::count( const Type &obj ) const {
	
	// call the node count method on the root node
	return root_node->count(obj);

}

// return the element at the top of the heap
template <typename Type>
Type Leftist_heap<Type>::top() const{
	
	// if the heap is empty, throw an exception
	if(empty()) {

		throw EXCEPTION_H::underflow();

	}

	//if the heap is not empty, return the root node's element
	else {

		return root_node->retrieve();

	}
}

// insert a new node into the heap
template <typename Type>
void Leftist_heap<Type>::push(const Type &obj) { // create the new node at the beginnign instead of each if/else statement

	// if the heap is empty, create a root node with the element 
	// as the argument
	if (empty()){

		//create a new root node
		root_node = new Leftist_node<Type>(obj);

		//increment the heap size
		heap_size++;
	}

	//otherwise, call push on the root node
	else{

		// create temporary variable for the node being pushed in
		Leftist_node<Type> *temp = new Leftist_node<Type>(obj);

		// call push on the root node
		root_node->push(temp, root_node);

		// increment heap size
		heap_size++;
	}
}

// also called extract-min, pop deletes the node with the lowest value and
// returns said value
template <typename Type>
Type Leftist_heap<Type>::pop() {
	
	// if the heap is empty, throw an exception
	if(empty()) {

		throw EXCEPTION_H::underflow();

	}

	// if the heap is not empty, extract the minimum value in the heap
	else {

		// create temporary variable for the right subtree of the root node
		Leftist_node<Type> *temp_right = root_node->right();

		// create temporary variable for the root node
		Leftist_node<Type> *old_root = root_node;

		// create a tempporary variable to store the element of the root node
		Type return_value = root_node->retrieve();

		// assign the left subtree of the old root node to the root node
		root_node = root_node->left();

		// deallocate memory for the old root node
		delete old_root;

		// push the right subtree of the old root node onto the new root node
		root_node->push(temp_right, root_node);

		// decrement the heap size
		heap_size--;

		return return_value;
	}
}

// clear the heap
template <typename Type>
void Leftist_heap<Type>::clear() {
	root_node->clear();

	// set the heap size to zero
	heap_size = 0;

	// set the root node to point to null
	root_node = nullptr;
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}

// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
//
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
