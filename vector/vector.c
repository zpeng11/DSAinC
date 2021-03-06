#include "vector.h"

vector VecCreate(int DataSize,int (*IsEqual)(const void *, const void *),int (*IsGreater)(const void *, const void *) )
{
    /*Create a new vector take size of each data and two element comparison function, 
    if elements are not designed to be compared, use NULL
    Comparison functions are used for sorting and unify */
    vector new ={
        ._size =0,
        ._DataSize =DataSize,
        ._capacity = 5,
        .IsEqual = IsEqual,
        .IsGreater = IsGreater
    };

    new._data = malloc(new._DataSize * new._capacity);
    return new;
}

static void VecExtend(vector *_vector)
{
    /*try to check if element length longer than capacity
    this function could only be called by other vecter extend operations like insert
    capacity would be doubled whenever extended */
    int oldCap = _vector->_capacity;
    while (_vector->_size + 2 > _vector->_capacity)
    {
        _vector->_capacity <<= 1;
        void *newData = malloc(_vector->_DataSize * _vector->_capacity);
        memcpy(newData, _vector->_data, _vector->_DataSize * oldCap);
        free(_vector->_data);
        _vector->_data = newData;
    }
}

vector VecCreateWithPtr(int DataSize, const void *old_ptr, int size ,int (*IsEqual)(const void *, const void *),int (*IsGreater)(const void *, const void *))
{
    /*same as creation above but with an array to initialize*/
    vector new = VecCreate(DataSize, IsEqual, IsGreater);
    new._size = size;
    VecExtend(&new);
    memcpy(new._data, old_ptr, new._DataSize * size);
    return new;
}

#define VecGet_(vectorPTR,rank)  ((vectorPTR)->_data+(vectorPTR)->_DataSize *(rank))//used only in this file, this macro doesnot take care of edge

void *VecGet(const vector *_vector, int rank)
{
    /*return a pointer to element at rank O(1) complexity*/
    if (rank <= _vector->_size - 1 && rank > -1)
        return (_vector->_data + _vector->_DataSize * rank);
    return NULL;
}

int VecPut(vector *_vector, const void *input_ptr, int rank)
{
    /*chage a specific element in the vector O(1) complexity*/
    return VecPutMultiple(_vector, input_ptr, 1, rank);
}

int VecPutMultiple(vector *_vector, const void *input_ptr, int num_2_put, int start_rank)
{
    if (_vector == NULL || start_rank + num_2_put > _vector->_size - 1 || start_rank < 0)
        return 0;
    memcpy(VecGet_(_vector, start_rank), input_ptr, _vector->_DataSize * num_2_put);
    return _vector->_size;
}

int VecInsert(vector *_vector, const void *input_ptr, int rank)
{
    /*insert a element in the vector O(n) complexity*/
    return VecInsertMultiple(_vector, input_ptr, 1, rank);
}

int VecInsertMultiple(vector *_vector, const void *input_ptr, int num_2_insert, int start_rank)
{
    if (_vector == NULL || input_ptr == NULL || start_rank > _vector->_size)
        return 0;
    _vector->_size += num_2_insert;
    VecExtend(_vector);
    memmove(VecGet_(_vector, start_rank + num_2_insert), VecGet_(_vector, start_rank), _vector->_DataSize * (_vector->_size - start_rank - num_2_insert));
    memcpy(VecGet_(_vector, start_rank), input_ptr, _vector->_DataSize * num_2_insert);
    return _vector->_size;
}

int VecPushBack(vector *_vector, const void *input_ptr)
{
    /*AKA insert as last O(1) complexty*/
    return VecInsert(_vector, input_ptr, _vector->_size);
}

int VecRemove(vector *_vector, int rank)
{
    /*remove a specific element in the vector O(n) complexity*/
    memmove(VecGet_(_vector, rank), VecGet_(_vector, rank + 1), _vector->_DataSize * (_vector->_size - 1 - rank));
    _vector->_size -= 1;
    return _vector->_size;
}

const void *VecPopBack(vector *_vector)
{
    /*remove last element in the vector O(1) complexity*/
    _vector->_size -=1;
    return VecGet_(_vector, _vector->_size);
}

int VecRemoveMultiple(vector *_vector, int num_2_remove, int start_rank)
{
    
    if (start_rank < 0 || start_rank + num_2_remove > _vector->_size || _vector == NULL)
        return 0;
    memmove(VecGet_(_vector, start_rank), VecGet_(_vector, num_2_remove + start_rank), _vector->_DataSize * (_vector->_size - start_rank - num_2_remove));
    _vector->_size -= num_2_remove;
    return _vector->_size;
}

void VecTraverse(vector *_vector, void (*callback)(void *))
{
    /*do same action to each elements in the vector*/
    int i;
    for (i = 0; i < _vector->_size; i++)
    {
        callback(VecGet_(_vector, i));
    }
}

void VecDestruct(vector *_vector)
{
    /*safely destruct the vector and free the space used */
    if (_vector == NULL)
        return;
    free(_vector->_data);
    return;
}

int VecFindBetween(const vector *_vector, const void *target, int start_rank, int end_rank)
{
    
    int hi = end_rank - 1;
    while ((start_rank - 1 < hi) && (memcmp(VecGet_(_vector, hi), target, _vector->_DataSize)))
        hi -= 1;
    return hi;
}

int VecFind(const vector *_vector, const void *target)
{
    /*find a element in the vector O(n) complexity*/
    return VecFindBetween(_vector, target, 0, _vector->_size);
}

int VecFindOL(const vector *_vector, const void *target)
{
    /*use overloaded IsEqual function to find element O(n) complexity*/
    int hi = _vector->_size - 1;
    while ((-1 < hi) && !_vector->IsEqual(target, VecGet_(_vector, hi)))
        hi -= 1;
    return hi;
}

int VecDisorderedOL(const vector *_vector)
{
    /*use overloaded IsGreater function to check if the vector is disordered O(n) complexity*/
    int n = 0;
    for (int i = 1; i < _vector->_size; i++)
    {
        n += _vector->IsGreater(VecGet_(_vector, (i - 1)), VecGet_(_vector, i));
    }
    return n;
}

void VecSelectionSortOL(vector *_vector)
{
    /*use selection sort algorithem to sort the vector, this function requires IsGreater function is specified O(n^2) complexity*/
    int i, j, min;

    for (i = 0; i < _vector->_size - 1; i++)
    {
        min = i;
        for (j = i + 1; j < _vector->_size; j++)
        {
            if (_vector->IsGreater(VecGet_(_vector, min), VecGet_(_vector, j)))
                min = j;
        }
        if (min != i)
        {
            memcpy(VecGet_(_vector, _vector->_size - 1) + _vector->_DataSize, VecGet_(_vector, i), _vector->_DataSize);
            memcpy(VecGet_(_vector, i), VecGet_(_vector, min), _vector->_DataSize);
            memcpy(VecGet_(_vector, min), VecGet_(_vector, _vector->_size - 1) + _vector->_DataSize, _vector->_DataSize);
        }
    }
}

static void merge(vector *_vector, int lo, int mi, int hi)
{
    void *arr__ = malloc(_vector->_DataSize * (hi - lo));
    for (int i = lo, j = mi, k = 0; (i < mi || j < hi);)
    {
        if (i < mi && (j >= hi || !_vector->IsGreater(VecGet_(_vector, i), VecGet_(_vector, j))))
        {
            memcpy((void *)arr__ + _vector->_DataSize * k++, VecGet_(_vector, i++), _vector->_DataSize);
        }
        if (j < hi && (i >= mi || _vector->IsGreater(VecGet_(_vector, i), VecGet_(_vector, j))))
        {
            memcpy((void *)arr__ + _vector->_DataSize * k++, VecGet_(_vector, j++), _vector->_DataSize);
        }
    }
    memcpy(VecGet_(_vector, lo), arr__, (hi - lo) * _vector->_DataSize);
    free(arr__);
}
static void VecMergeSort(vector *_vector, int lo, int hi)
{
    /*function used for recursion*/
    if (lo + 2 > hi)
        return;
    int mi = (lo + hi) >> 1;
    VecMergeSort(_vector, lo, mi);
    VecMergeSort(_vector, mi, hi);
    merge(_vector, lo, mi, hi);
}

void VecMergeSortOL(vector *_vector)
{
    /*Merge sort algorithem, requires IsGreater to be declared, O(logn) complexity, but pretty high space complexity and so much malloc and  delete*/
    VecMergeSort(_vector, 0, _vector->_size);
}

void VecSortOL(vector *_vector)
{
    /*randomly selection from merge sort and selection sort*/
    if (rand() % 2)
        VecMergeSortOL(_vector);
    else
        VecSelectionSortOL(_vector);
}

int VecSearchOL(const vector *_vector, const void *target)
{
    /*search a specific element in the vector, requires the vector in order and IsGreater being decleared*/
    int lo = 0;
    int hi = _vector->_size;
    while (lo < hi)
    {
        int mi = (hi + lo) >> 1;
        if (_vector->IsGreater(VecGet_(_vector, mi), target))
            hi = mi;
        else
            lo = ++mi;
    }
    return --lo;
}