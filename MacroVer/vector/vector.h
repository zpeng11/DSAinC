/*Author : Zhanfei Peng,

TO DO:
1. Change constructor that it returns the struct but not poiner to heap 
2. Change Get to return value
3. Complete the rest

User guide :

1. Change three macros DataType vector and function to what data type you want, vector and function macros can be change to what you may want to call

2. If you want to use nested vector or multiple vector, try to undefine three macros mentioned above by 
#undef DataType
#undef vector
#undef function
You may copy paste those three lines below the including sentences,I tried to find a better way unfortuantly this seems to be only way. 

3.When using this library call vector by int_vector for instance, intVector to call a vector with interger inside,
intVectorCreate to return a pointer to the established vector in heap
*/

#ifndef VECTOR_H //May be changed when nested or multiple
#define VECTOR_H //May be changed when nested or multiple
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DataType int                   //change int to what datatype you want
#define vector int##Vector             //you may edit the name you want to call the data structure
#define function(fun) int##Vector##fun //you may edit this to what name you wanna call the functions like foo##fun
//#define USE_AS_STACK

typedef struct vector //core structrue
{
    /*_size is recording abstract length of data, but it is unecessary to be related with physical length in heap */
    int _size; 
    /*_capacity is tracking the length of physical memory use*/
    int _capacity;
    /*This is the core of the container which tracks memory in heap*/
    DataType *_data;
} vector;

//create and destruct
vector function(Create)(void); //create a vector and initialize memory in heap, every create should correspond to a destruct 
vector function(CreateWithPtr)(const DataType *old_ptr, int size);//creater for convinent
void function(Destruct)(vector *_vector);


int function(Size)(const vector *_vector);//take existing vector pointer and return size of it
DataType function(Get)(const vector *_vector, int rank);//Get the data store in vector at index "rank", it works like geting value with []
int function(Put)(vector *_vector, DataType input, int rank); //change value at an existing position rank #It does not change the size of vector
int function(PutMultiple)(vector *_vector, const DataType *input_ptr, int num_2_put, int start_rank);
int function(Insert)(vector *_vector, DataType input, int rank);//Insert value at given position, size would be changed
int function(InsertMultiple)(vector *_vector, const DataType *input_ptr, int num_2_insert, int start_rank);
int function(PushBack)(vector *_vector, DataType input);//AKA Insert at the end
DataType function(Remove)(vector *_vector, int rank);
DataType function(PopBack)(vector *_vector);//AKA remove at the end
int function(RemoveMultiple)(vector *_vector, int start_rank, int end_rank);
void function(Traverse)(vector *_vector, void (*callback)(DataType *));//it take in a function pointer and do same action for all elements in vector


//Related algorithm
int function(Disordered)(const vector *_vector);
int function(Sort)(vector *_vector);
int function(Find)(const vector *_vector, DataType target, int *result_rank);
int function(Search)(const vector *_vector, DataType target, int *result_rank);
int function(Deduplicate)(vector *_vector);
int function(Uniquify)(vector *_vector);


/*Algorithm function used when involes in comparison overload*/
int function(DisorderedOL)(const vector *_vector, int (*IsEqual)(const DataType *, const DataType *));
int function(SortOL)(vector *_vector, int (*IsEqual)(const DataType *, const DataType *));
int function(FindOL)(const vector *_vector, DataType target, int *result_rank, int (*IsEqual)(const DataType *, const DataType *));
int function(SearchOL)(const vector *_vector, DataType target, int *result_rank, int (*IsEqual)(const DataType *, const DataType *));
int function(DeduplicateOL)(vector *_vector, int (*IsEqual)(const DataType *, const DataType *));
int function(UniquifyOL)(vector *_vector, int (*IsEqual)(const DataType *, const DataType *));

#endif /*VECTOR_H*/