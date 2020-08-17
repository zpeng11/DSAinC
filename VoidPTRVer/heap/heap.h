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

heap HeapCreate(int KeyDataSize, int ValueDataSize, int (* KetIsEqual)(const void *, const void *),int (* KeyIsGreater)(const void * ,const void *) );
heap HeapBatchCreate(entry * Old_Ptr, int size,  int KeyDataSize, int ValueDataSize, int (* KetIsEqual)(const void *, const void *),int (* KeyIsGreater)(const void * ,const void *));
void HeapDestruct(heap *);
void HeapInsert(heap * _heap, const void * key, const void * value);
void * HeapGetMax(heap * _heap);
void HeapDelMax(heap * _heap);
#endif /*HEAP_H*/