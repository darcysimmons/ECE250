/*****************************************
 *
 * uWaterloo User ID:  drasimmo@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 *****************************************/

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include <iostream>
using namespace std;


class Dynamic_stack {

	private:
		int *array;
		int count;		
		int array_size;
		int initial_size;
	
	public:
		Dynamic_stack(int = 10);
		~Dynamic_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;
			
		void push( int const & );
		int pop();
		void clear();		
};

// constructor which initializes an array of size n to contain an initially empty stack.
// If n is zero or negative, the array will be initialized to 1. If n is greater than 10,
// the array is initialized to 10
Dynamic_stack::Dynamic_stack( int n ):
count( 0 ),
array_size( n ),
initial_size(n)
{
	// set array size to one given a non-positive input
	if (n<1)
		array_size=1;

	// set array size to ten given an input greater than ten
	else if (n>10)
		array_size = 10;

	// otherwise, create an array of size n
	else
		array = new int[array_size];

	// set the initial size of the array
	initial_size = array_size;

}

// destructor
Dynamic_stack::~Dynamic_stack() {
	
	// delete the array and its contents
	delete[] array;

	// set the array size to 0
	array_size = 0;

	// set the stack size to 0
	count = 0;
}

// return the item at the top of the stack
int Dynamic_stack::top() const {

	// if the stack is empty, throw an exception
	if (count < 1) {

		throw EXCEPTION_H::underflow();
	}

	// otherwise, return the array at the index of one less than the stack size
	else{

		return array[count - 1];
	}

	return  0;
}

// return the number of items in the stack
int Dynamic_stack::size() const {
	
	return count;
}

// return whether or not the stack is empty
bool Dynamic_stack::empty() const {
	
	if (count == 0)
		return true;

	else 
		return false;  
}

// return the size of the array in which the stack resides
int Dynamic_stack::capacity() const {
	
	return array_size;
}

// push an item to the top of the stack
void Dynamic_stack::push( int const &obj ) {
	
	// If there is no more room in the array to add onto the stack, 
	// create a new array with the same contents that is double the initial 
	// array size
	if(count == array_size) {

		// create new array of double the size
		int* newArray = new int[array_size*2];

		// copy the contents of array to the new array
		for (int i = 0; i<array_size; i++) {

			newArray[i] = array[i];
		}

		// deallocate memory for old array
		delete[] array;

		// set array to be the new array
		array = newArray;

		// push the new item to the top of the stack
		array[count] = obj; 

		// increment the size of the stack
		count++;
	}

	// otherwise, add the item "obj" to the top of the stack
	else {

		array[count] = obj;
		count++;
	}
}

// remove the item at the top of the stack
int Dynamic_stack::pop() {
	
	// if the stack is empty, throw an underflow
	if(empty()) {

		throw EXCEPTION_H::underflow();
	}

	// otherwise remove the top item
	else {

		// create an object equal to the one being popped
		int returnValue = array[count-1];

		// set the array equal to zero at the index of the object being popped
		array[count-1] = 0;

		// decrement the size of the stack
		count--;

		// return the value of the item that was popped
		return returnValue;
	}
}

// remove every item in the stack
void Dynamic_stack::clear() {
	
	// delete the container array and its contents
	delete[] array;

	// create a new array that is empty
	array = new int[initial_size];

}
#endif
