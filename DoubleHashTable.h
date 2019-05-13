#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H


/****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
		int mod(int key, int capacity) const;
		int search(T const & );
};

// constructor: create an empty hash table
template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	// set the status of each bin to be empty
	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	
	// clear the hashmap
	clear();

	// delete both arrays implementing the hash map
	delete[] array; 
	delete[] array_state;

	// set the capacity to zero
	array_size = 0;
}

// size: return the number of items in the hash table
template<typename T >
int DoubleHashTable<T >::size() const {

    // return the number of non-empty and non-deleted items in the array
	return count;
}

// capacity: return the number of bins in the hash table
template<typename T >
int DoubleHashTable<T >::capacity() const {

	//return the size of the array that implements the hash table
	return array_size;
}

// empty: return true if there is nothing stored in the hash table 
// and false otherwise
template<typename T >
bool DoubleHashTable<T >::empty() const {

	// return whether or not the size of the hash table is zero
	return (size() == 0);
}

// the first hashing function: the object value modulo the size of the hash table
template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	
	// initialize the return value
	int ret = 0;

	// set reutrn value of h1 to be the integer value of "obj" modulo the 
	// size of the hash table
	ret = mod((int)obj , capacity());


	return ret;
}

// second hashing function: divide the integer value of the object by the 
// size of the hash table, and modulo this result with the size of the hash table
// this gives us a constant number of bins over which to jump from the initial bin
// which was hashed using the first hashing function
template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	// initialize the return value
	int ret = 0;

	// initalize a variable to be the integer value of the object divided by 
	// the size of the hash table
	int result = (int)obj / capacity();

	// modulo the result of the previous line with the size of the hash table
	ret = mod(result, capacity());

	// add 1 if even to make it odd
	if (ret%2 == 0 || ret == 0)
		ret+=1;

	return ret;
}

// member: return true if the given object is in the hash table and false otherwise
template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {

	//print();

	// use the first hashing function to generate an index for the object
	int index = h1(obj);

	// check if the object at the generated index is what we're looking for
	// if so, return true
	if (array[index] == obj && array_state[index] == OCCUPIED)
		return true;

	// if there is a collision, use the second hashing function to determine
	// how many bins to step over to get to the next probe
	int jump = h2(obj);

	for (int i = 0; i < capacity() ; i++){
		
		// add the jump value to get the next index
		if (index + jump < capacity())
			index += jump;
		else{
			index = (index + jump - capacity());
		}

		// if the bin at the next index is empty, the object we are searching for
		// is not in the hash table
		if (array_state[index] == EMPTY)
			return false;

		// if the value in the bin is equal to what we are searching for, return true
		if (array[index] == obj && array_state[index] == OCCUPIED) 
			return true;

	}
	
	// otherwise, the object is not in the hash table
	return false;
}

// bin: return the value in the bin n
template<typename T >
T DoubleHashTable<T >::bin( int n ) const {	  

 //print();    
    
	// make sure there is something in the bin
	if (array_state[n] == OCCUPIED) {      

    	// return the value in bin n      
		return array[n];
	}

	// if there is nothing in the bin, return null
	else {

		// initialize a null return value
		return 0;
	}
}

// insert: add the given object to the hash table
template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {

	// if the table is full, throw an exception
	if (size() == capacity())
		throw EXCEPTION_H::overflow();

	// increase the number of objects in the hashtable
	count++;

	// use the first hashing function to generate an index
	int index = h1(obj);

	// if the bin at this index is not occupied, insert the object here
	if (array_state[index] != OCCUPIED) {
		array[index] = obj;
		array_state[index] = OCCUPIED;
		return;
	}

	// otherwise use the second hash function to calculate the jump size

	// set jump size
	int jump = h2(obj);

	//std::cout << jump << std::endl;

	// iterate through the hash table, stopping when each bin has been checked, 
	// or when the object has been inserted
	for (int i = 0; i < capacity() ; i++ ) {

		// set the index to be the previous index plus the jump size 
		if (index + jump < capacity())
			index += jump;
		else{
			index = (index + jump - capacity());
		}

		// if the bin is not occupied, insert the object into that bin
		if (array_state[index] != OCCUPIED) {

			// set the value in the bin to the object
			array[index] = obj;
			array_state[index] = OCCUPIED;

			return;
		}
	}

	return;
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	
	// if the object we are removing is not in the hash table, return false
	if (!member(obj))
		return false;

	// decrement the count of objects in the hash table
	count--; 

	// get the index of the object
	int index = search(obj);

	// set the status of the bin to deleted
	array_state[index] = DELETED;

	return true;
}

// clear: clear the hash table
template<typename T >
void DoubleHashTable<T >::clear() {
	 
	// iterate through the status array and set every value to EMPTY
	for (int i=0; i< capacity(); i++) {
		array[i] = EMPTY;
	}

	// set the count of elements in the hash table to 0
	count = 0;

	return ; 
}

template<typename T >
void DoubleHashTable<T >::print() const {
      
      for (int i = 0; i< capacity(); i++) {
      	std::cout << i << ": " << array[i]<< " ; " << array_state[i] << std::endl;
      } 	
	return;
}

// the method mod takes two intergers and does the modulo of the first by 
// the second. The c++ "%" operator c++ modulo operator will return the negative of the 
// absoute value of the modulo of the key, if the key is negative, so we must create a 
// method to perform the proper version of modulo
template<typename T >
int DoubleHashTable<T >::mod(int key, int capacity) const {
    //initiaize a return value
    int ret = 0;

    // set the return value to the key modulo the capacity 
    ret = key%capacity;

    // if the value is negative, set the return value to ret plus the capacity
    if (ret<0) 
    	ret += capacity;

	return ret;
}

// search: return the index of the given object
// I assume that the object is in the hash table
template<typename T >
int DoubleHashTable<T >::search(T const &obj) {
	 
	// use the first hashing function to generate an index for the object
	int index = h1(obj);

	// check if the object at the generated index is what we're looking for
	// if so, return the index
	if (array[index] == obj && array_state[index] == OCCUPIED)
		return index;

	// if there is a collision, use the second hashing function to determine
	// how many bins to step over to get to the next probe
	int jump = h2(obj);

	for (int i = 0; i < capacity() ; i++){
		
		// add the jump value to get the next index
		if (index + jump < capacity())
			index += jump;
		else{
			index = (index + jump - capacity());
		}

		// if the value in the bin is equal to what we are searching for, return the index
		if (array[index] == obj && array_state[index] == OCCUPIED) 
			return index;

	}

	return 0;
}

#endif
