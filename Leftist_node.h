
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

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// returns the element stored in the current node
template <typename Type>
Type Leftist_node<Type>::retrieve() const {
	return element;
}

// returns the address of the left tree of the current node
template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::left() const {
	return left_tree;
}

// returns the address of the right tree of the current node
template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const {
	return right_tree;
}

//return the null path length of the current node
template <typename Type>
int Leftist_node<Type>::null_path_length() const {
	
	// if this node is empty, the null path length is -1
	if (empty()) {
		
		return -1;
	}

	// otherwise return the null path length
	else {
		
		return heap_null_path_length;
	}
}

// return the number of instances of the argument in the current subtree
template <typename Type>
int Leftist_node<Type>::count( const Type &obj) const {

	if (empty()) {

		return 0;
	}

	// if the current element is equal to the argument, return 1 more than 
	// the number of instances in each of the subtrees 
	if (element == obj ) {

		// recursivley call count on the left and right subtrees
		return 1 + left_tree->count(obj) +right_tree->count(obj);
	}

	// otherwise, simply return the sum of instances in each subtree
	else {

		// recursivley call count on the left and right subtrees
		return left_tree->count(obj) + right_tree->count(obj);
	}
	
}

template <typename Type>
void Leftist_node<Type>::push(Leftist_node *new_heap, Leftist_node *&ptr_to_this) {
	
	// return if the heap to be pushed is empty
	if (new_heap == nullptr) {
		return;
	}

	// if this node is empty, set the pointer to the new heap
	if (ptr_to_this == nullptr) {
		ptr_to_this = new_heap;

		return;
	}

	// if the new node has a value less than the current node, recursively push it onto the right subtree
	if (ptr_to_this->retrieve() <= new_heap->retrieve()) {
		
		ptr_to_this->right_tree->push(new_heap, ptr_to_this->right_tree);

		// set the heap null path length to be 1 plus the minimum of the null path lengths of the left and right subtrees
		ptr_to_this->heap_null_path_length = 1 + std::min(  left_tree->null_path_length(), right_tree->null_path_length() );

		// if the right tree is larger than the left tree, swap the two
		if (left_tree->null_path_length() < right_tree->null_path_length() ) {
			std::swap(left_tree, right_tree);
		}

	}

	// if the new node has value less than that of the current node, switch out the current node
	// and the new heap and push the current node onto the new heap
	else {

		Leftist_node *temp = ptr_to_this;

		ptr_to_this = new_heap;
  
		ptr_to_this->push(temp, ptr_to_this);
	}

}

// clear the tree taking root at the current node
template <typename Type>
void Leftist_node<Type>::clear() {
	
	// if this node is empty, return
	if (empty()) {
		return;
	}

	// recursively clear the right subtree
	right_tree->clear();

	// recursively clear the left subtree
	left_tree->clear();

	// delete the current node
	delete this;

	// set the null path length to zero
	heap_null_path_length = -1;
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr);
}

// You must implement everything

#endif
