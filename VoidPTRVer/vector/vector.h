/*
User guide :

1.
This is a vector library works for safely manage linear RAM memory in heap for different data structure and algorithm.

2.
The container uses void * and associate datasize to manage data in the container, which means vector is unsensitive to actual data. 
It ONLY works as a memory manager.

3.
It is the user's responsibility to convert rvalue to lvalue and pass pointer for the vector to handle as input. 
And it is the user's responsibility to extract data from the output void* 
For instance 
#define INT (int)*(int *)
int a = INT VecPopBack(vec);
to extract an interger from a vector named vec.

4.
Try to use functions to access and edit data for memory safe,
edition of varible in the vector may leads to unpredict memory leak
The memory of vect object is managed by user yourself, don't forget to free it if you call it from heap
Dont forget to use create and destruct functions at the beginning and the end of lifespan 


*/

#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector //core structrue
{
    int _size;
    int _capacity;
    int _DataSize;
    void *_data;
} vector;

vector VecCreate(int DataSize);
vector VecCreateWithPtr(int DataSize, const void *old_ptr, int size);
int VecSize(const vector *_vector);
void *VecGet(const vector *_vector, int rank);

int VecPut(vector *_vector, const void *input_ptr, int rank);
int VecPutMultiple(vector *_vector, const void *input_ptr, int num_2_put, int start_rank);
int VecInsert(vector *_vector, const void *input_ptr, int rank);
int VecInsertMultiple(vector *_vector, const void *input_ptr, int num_2_insert, int start_rank);
int VecPushBack(vector *_vector, const void *input_ptr);
int VecRemove(vector *_vector, int rank);
const void *VecPopBack(vector *_vector);
int VecRemoveMultiple(vector *_vector, int start_rank, int end_rank);
void VecTraverse(vector *_vector, void (*callback)(void *));
void VecDestruct(vector *_vector);

int VecFind(const vector *_vector, const void *target);
int VecFindBetween(const vector *_vector, const void *target, int start_rank, int end_rank);

/*function used when involes in comparison overload*/
int VecDisorderedOL(const vector *_vector, int (*IsGreater)(const void *, const void *));
void VecSortOL(vector *_vector, int (*IsGreater)(const void *, const void *));
void VecMergeSortOL(vector *_vector, int (*IsGreater)(const void *, const void *));
void VecSelectionSortOL(vector *_vector, int (*IsGreater)(const void *, const void *));
int VecFindOL(const vector *_vector, const void *target, int (*IsEqual)(const void *, const void *));
int VecSearchOL(const vector *_vector, const void *target, int (*IsGreater)(const void *, const void *));
int VecUniquifyOL(vector *_vector, int (*IsEqual)(const void *, const void *));

#endif /*VECTOR_H*/