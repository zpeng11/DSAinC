#include "vector.h"

vector VecCreate(int DataSize)
{
    vector new ={
        ._size =0,
        ._DataSize =DataSize,
        ._capacity = 5
    };

    new._data = malloc(new._DataSize * new._capacity);
    return new;
}

static void VecExtend(vector *_vector)
{
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

vector VecCreateWithPtr(int DataSize, const void *old_ptr, int size)
{
    vector new = VecCreate(DataSize);
    new._size = size;
    VecExtend(&new);
    memcpy(new._data, old_ptr, new._DataSize * size);
    return new;
}



void *VecGet(const vector *_vector, int rank)
{
    if (rank <= _vector->_size - 1 && rank > -1)
        return (_vector->_data + _vector->_DataSize * rank);
    return NULL;
}

int VecPut(vector *_vector, const void *input_ptr, int rank)
{
    return VecPutMultiple(_vector, input_ptr, 1, rank);
}

int VecPutMultiple(vector *_vector, const void *input_ptr, int num_2_put, int start_rank)
{
    if (_vector == NULL || start_rank + num_2_put > _vector->_size - 1 || start_rank < 0)
        return 0;
    memcpy(VecGet(_vector, start_rank), input_ptr, _vector->_DataSize * num_2_put);
    return _vector->_size;
}

int VecInsert(vector *_vector, const void *input_ptr, int rank)
{
    return VecInsertMultiple(_vector, input_ptr, 1, rank);
}

int VecInsertMultiple(vector *_vector, const void *input_ptr, int num_2_insert, int start_rank)
{
    if (_vector == NULL || input_ptr == NULL || start_rank > _vector->_size)
        return 0;
    _vector->_size += num_2_insert;
    VecExtend(_vector);
    memmove(VecGet(_vector, start_rank + num_2_insert), VecGet(_vector, start_rank), _vector->_DataSize * (_vector->_size - start_rank - num_2_insert));
    memcpy(VecGet(_vector, start_rank), input_ptr, _vector->_DataSize * num_2_insert);
    return _vector->_size;
}

int VecPushBack(vector *_vector, const void *input_ptr)
{
    return VecInsert(_vector, input_ptr, _vector->_size);
}

int VecRemove(vector *_vector, int rank)
{
    memmove(VecGet(_vector, rank), VecGet(_vector, rank + 1), _vector->_DataSize * (_vector->_size - 1 - rank));
    _vector->_size -= 1;
    return _vector->_size;
}

const void *VecPopBack(vector *_vector)
{
    VecRemove(_vector, _vector->_size - 1);
    return VecGet(_vector, _vector->_size-1)+_vector->_DataSize;
}

int VecRemoveMultiple(vector *_vector, int num_2_remove, int start_rank)
{
    if (start_rank < 0 || start_rank + num_2_remove > _vector->_size || _vector == NULL)
        return 0;
    memmove(VecGet(_vector, start_rank), VecGet(_vector, num_2_remove + start_rank), _vector->_DataSize * (_vector->_size - start_rank - num_2_remove));
    _vector->_size -= num_2_remove;
    return _vector->_size;
}

void VecTraverse(vector *_vector, void (*callback)(void *))
{
    int i;
    for (i = 0; i < _vector->_size; i++)
    {
        callback(VecGet(_vector, i));
    }
}

void VecDestruct(vector *_vector)
{
    if (_vector == NULL)
        return;
    free(_vector->_data);
    return;
}

int VecFindBetween(const vector *_vector, const void *target, int start_rank, int end_rank)
{
    int hi = end_rank - 1;
    while ((start_rank - 1 < hi) && (memcmp(VecGet(_vector, hi), target, _vector->_DataSize)))
        hi -= 1;
    return hi;
}

int VecFind(const vector *_vector, const void *target)
{
    return VecFindBetween(_vector, target, 0, _vector->_size);
}

int VecFindOL(const vector *_vector, const void *target, int (*IsEqual)(const void *, const void *))
{
    int hi = _vector->_size - 1;
    while ((-1 < hi) && !IsEqual(target, VecGet(_vector, hi)))
        hi -= 1;
    return hi;
}

int VecDisorderedOL(const vector *_vector, int (*IsGreater)(const void *, const void *))
{
    int n = 0;
    for (int i = 1; i < _vector->_size; i++)
    {
        n += IsGreater(VecGet(_vector, (i - 1)), VecGet(_vector, i));
    }
    return n;
}

void VecSelectionSortOL(vector *_vector, int (*IsGreater)(const void *left, const void *right))
{
    int i, j, min;

    for (i = 0; i < _vector->_size - 1; i++)
    {
        min = i;
        for (j = i + 1; j < _vector->_size; j++)
        {
            if (IsGreater(VecGet(_vector, min), VecGet(_vector, j)))
                min = j;
        }
        if (min != i)
        {
            memcpy(VecGet(_vector, _vector->_size - 1) + _vector->_DataSize, VecGet(_vector, i), _vector->_DataSize);
            memcpy(VecGet(_vector, i), VecGet(_vector, min), _vector->_DataSize);
            memcpy(VecGet(_vector, min), VecGet(_vector, _vector->_size - 1) + _vector->_DataSize, _vector->_DataSize);
        }
    }
}

static void merge(vector *_vector, int lo, int mi, int hi, int (*IsGreater)(const void *, const void *))
{
    void *arr__ = malloc(_vector->_DataSize * (hi - lo));
    for (int i = lo, j = mi, k = 0; (i < mi || j < hi);)
    {
        if (i < mi && (j >= hi || !IsGreater(VecGet(_vector, i), VecGet(_vector, j))))
        {
            memcpy((void *)arr__ + _vector->_DataSize * k++, VecGet(_vector, i++), _vector->_DataSize);
        }
        if (j < hi && (i >= mi || IsGreater(VecGet(_vector, i), VecGet(_vector, j))))
        {
            memcpy((void *)arr__ + _vector->_DataSize * k++, VecGet(_vector, j++), _vector->_DataSize);
        }
    }
    memcpy(VecGet(_vector, lo), arr__, (hi - lo) * _vector->_DataSize);
    free(arr__);
}
static void VecMergeSort(vector *_vector, int lo, int hi, int (*IsGreater)(const void *, const void *))
{
    if (lo + 2 > hi)
        return;
    int mi = (lo + hi) >> 1;
    VecMergeSort(_vector, lo, mi, IsGreater);
    VecMergeSort(_vector, mi, hi, IsGreater);
    merge(_vector, lo, mi, hi, IsGreater);
}

void VecMergeSortOL(vector *_vector, int (*IsGreater)(const void *, const void *))
{
    VecMergeSort(_vector, 0, _vector->_size, IsGreater);
}

void VecSortOL(vector *_vector, int (*IsGreater)(const void *, const void *))
{
    if (rand() % 2)
        VecMergeSortOL(_vector, IsGreater);
    else
        VecSelectionSortOL(_vector, IsGreater);
}

int VecSearchOL(const vector *_vector, const void *target, int (*IsGreater)(const void *, const void *))
{
    int lo = 0;
    int hi = _vector->_size;
    while (lo < hi)
    {
        int mi = (hi + lo) >> 1;
        if (IsGreater(VecGet(_vector, mi), target))
            hi = mi;
        else
            lo = ++mi;
    }
    return --lo;
}