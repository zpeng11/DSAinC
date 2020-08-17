#include "heap.h"

#define Parent(i) (((i)-1) >> 1)
#define LChild(i) (1 + ((i) << 1))
#define RChild(i) ((1 + (i)) << 1)
#define ParentValid(i) (Parent(i) > -1)
#define lcValid(i) (LChild(i) < _heap->_vector._size)
#define rcValid(i) (RChild(i) < _heap->_vector._size)
#define ENTRY *(entry *)
#define HeapGet(rank) (VecGet(&(_heap->_vector), (rank)))
#define IsGreater(const_void_ptr, const_void_ptr_) (_heap->_vector.IsGreater((const_void_ptr), (const_void_ptr_)))
#define key_ptr(rank) ((ENTRY HeapGet(rank)).key)

int percolateDown(heap *_heap,  int rank);
int percolateUp(heap *_heap, int rank);
int heapify(heap *_heap, int n);

int percolateUp(heap *_heap, int rank)
{
    while (ParentValid(rank))
    {
        int ParentRank = Parent(rank);
        if (IsGreater(key_ptr(rank), key_ptr(ParentRank))) //swap entries if key is not in the order
        {
            entry temp = ENTRY HeapGet(rank);
            ENTRY HeapGet(rank) = ENTRY HeapGet(ParentRank);
            ENTRY HeapGet(ParentRank) = temp;
            rank = ParentRank;
        }
        else
        {
            break;
        }
    }
    return rank;
}

int ProperParent(heap *_heap, int parent)
{
    int lc = (lcValid(parent)) ? LChild(parent) : -1;
    int rc = (rcValid(parent)) ? RChild(parent) : -1;
    if (lc + 1) //lc exist
    {
        if (rc + 1) //both lc rc exist
        {
            if (!IsGreater(key_ptr(lc), key_ptr(rc))) //rc >= lc
            {
                if (!IsGreater(key_ptr(lc), key_ptr(parent))) //parent >= lc
                {
                    goto l0r1; //get rid off lc
                }
                else //parent < lc
                {
                    return rc;
                }
            }
            else //rc < lc
            {
                if (!IsGreater(key_ptr(parent), key_ptr(rc))) //rc >= parent
                {
                    return lc;
                }
                else //rc < parent
                {
                    goto l1r0; //get rid off rc
                }
            }
        }
        else //lc1 rc0
        {
        l1r0:
            return (!IsGreater(key_ptr(lc), key_ptr(parent))) ? parent : lc;
        }
    }
    else //lc does not exist
    {
        if (rc + 1) //lc0 rc1
        {
        l0r1:
            return (!(IsGreater(key_ptr(rc), key_ptr(parent)))) ? parent : rc;
        }
        else // rc0 rc0
        {
            return parent;
        }
    }
}

int percolateDown(heap *_heap,  int rank)
{
    int ParentRank;
    while (rank != (ParentRank = ProperParent(_heap, rank)))
    {
        entry temp = ENTRY HeapGet(rank);
        ENTRY HeapGet(rank) = ENTRY HeapGet(ParentRank);
        ENTRY HeapGet(ParentRank) = temp;
        rank = ParentRank;
    }
    return rank;
}

heap HeapCreate(int KeyDataSize, int ValueDataSize, int (*KetIsEqual)(const void *, const void *), int (*KeyIsGreater)(const void *, const void *))
{
    heap _heap;
    _heap._vector = VecCreate(sizeof(entry), KetIsEqual, KeyIsGreater);
    _heap.KeyDataSize = KeyDataSize;
    _heap.ValueDataSize = ValueDataSize;
    return _heap;
}

void HeapDestruct(heap *_heap)
{
    VecTraverse(&(_heap->_vector), EntryDestruct);
    VecDestruct(&(_heap->_vector));
}

void HeapInsert(heap *_heap, const void *key, const void *value)
{
    entry temp = EntryCreate(key, _heap->KeyDataSize, value, _heap->ValueDataSize);
    VecPushBack(&(_heap->_vector), &temp);
    percolateUp(_heap, _heap->_vector._size - 1);
}

void *HeapGetMax(heap *_heap)
{
    return ((entry *)_heap->_vector._data)->value;
}

void HeapDelMax(heap *_heap)
{
    entry temp = ENTRY HeapGet(0);
    ENTRY HeapGet(0) = ENTRY HeapGet(_heap->_vector._size - 1);
    ENTRY HeapGet(_heap->_vector._size - 1) = temp;
    EntryDestruct(HeapGet(_heap->_vector._size - 1));
    VecPopBack(&(_heap->_vector));
    percolateDown(_heap, _heap->_vector._size, 0);
}


heap HeapBatchCreate(entry * Old_Ptr, int size,  int KeyDataSize, int ValueDataSize, int (* KetIsEqual)(const void *, const void *),int (* KeyIsGreater)(const void * ,const void *))
{
    heap _heap;
    _heap.KeyDataSize = KeyDataSize;
    _heap.ValueDataSize = ValueDataSize;
    _heap._vector = VecCreateWithPtr(sizeof(entry), Old_Ptr, size, KetIsEqual, KeyIsGreater);
    heapify(&_heap, size-1);
}


int heapify(heap *_heap, int n)
{
    for(int i = n; i>0;i--)
    {
        percolateDown(_heap, i);
    }
}
