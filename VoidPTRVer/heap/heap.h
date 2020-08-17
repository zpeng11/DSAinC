#ifndef HEAP_H
#define HEAP_H

#include "vector.h"
#include "BST.h"

typedef struct  heap
{
    vector _vector;
    int KeyDataSize;
    int ValueDataSize;
}heap;

heap HeapCreate(int KeyDataSize, int ValueDataSize, int (* KetIsEqual)(const void *, const void *),int (* KeyIsGreater)(const void * ,const void *) );//create a heap
heap HeapBatchCreate(entry * Old_Ptr, int size,  int KeyDataSize, int ValueDataSize, int (* KetIsEqual)(const void *, const void *),int (* KeyIsGreater)(const void * ,const void *));//batch create an heap O(n) complexity
void HeapDestruct(heap *);//Destruct a heap
void HeapInsert(heap * _heap, const void * key, const void * value);//insert an element O(logn) complexity
void * HeapGetMax(heap * _heap);//get the maximun of a heap which is the first element in the vector O(1) complexity
void HeapDelMax(heap * _heap);//remove the first element in the heap tree O(logn) complexity
#endif /*HEAP_H*/