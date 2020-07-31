#include "vector.h"

vector function(Create)(void)
{
    /*create a vector and initialize memory in heap*/
    vector new ;
    new._capacity = 5;
    new._size = 0;
    new._data = (DataType *)malloc(sizeof(DataType) * new._capacity); //create memory from heap
    return new;
}

static void function(Extend)(vector *_vector)
{
        /*This function is called in every other function that may cause size to grow 
        Whenever the size is near capacity, 
        we create a new bigger space, copy elements from old, then free old memory 
        */
    int oldCap = _vector->_capacity;
    while (_vector->_size >= _vector->_capacity)//if size near capacity
    {
        _vector->_capacity <<= 1;//capacity double 
        DataType *newData = (DataType *)malloc(sizeof(DataType) * _vector->_capacity);//create new memory
        memcpy(newData, _vector->_data, sizeof(DataType) * oldCap);//copy old memory to new
        free(_vector->_data);//free old
        _vector->_data = newData;
    }
}

vector function(CreateWithPtr)(const DataType *old_ptr, int size)
{
    vector new = function(Create)();
    new._size = size;
    function(Extend)(&new);
    memcpy(new._data, old_ptr, sizeof(DataType) * size);
    return new;
}

int function(Size)(const vector *_vector)
{
    if (_vector != NULL)
        return _vector->_size;
    return 0;
}

DataType function(Get)(const vector *_vector, int rank)
{

    /*return a copy of element at location rank*/
        return ((_vector->_data)[rank]);
}



int function(Put)(vector *_vector, DataType input, int rank)
{
    /*change existing element at rank to the same as input*/
    if (_vector == NULL || rank > _vector->_size - 1)
        return 0;
    _vector->_data[rank] = input;
    return _vector->_size;
}


int function(PutMultiple)(vector *_vector, const DataType *input_ptr, int num_2_put, int start_rank)
{
    if (_vector == NULL || start_rank + num_2_put > _vector->_size - 1 || start_rank < 0)
        return 0;
    memcpy(&(_vector->_data[start_rank]), input_ptr, sizeof(DataType) * num_2_put);
    return _vector->_size;
}

int function(Insert)(vector *_vector, DataType input, int rank)
{
    /*insert an element in the vector, increase size by 1, if insert at the middle move elements one place backward*/
    if (_vector == NULL || rank < 0 || rank > _vector->_size)//test if everything it is valid 
        return 0;
    _vector->_size += 1;
    function(Extend)(_vector);//extend if necessary
    memmove(&(_vector->_data[rank + 1]), &(_vector->_data[rank]), sizeof(DataType) * (_vector->_size - 1 - rank));//move memory to the back if necessary
    _vector->_data[rank] = input;//insert
    return _vector->_size;
}

int function(InsertMultiple)(vector *_vector, const DataType *input_ptr, int num_2_insert, int start_rank)
{
    if (_vector == NULL || input_ptr == NULL || start_rank > _vector->_size)
        return 0;
    _vector->_size += num_2_insert;
    function(Extend)(_vector);
    memmove(&(_vector->_data[start_rank + num_2_insert]), &(_vector->_data[start_rank]), sizeof(DataType) * (_vector->_size - start_rank - num_2_insert));
    memcpy(&(_vector->_data[start_rank]), input_ptr, sizeof(DataType) * num_2_insert);
    return _vector->_size;
}

int function(PushBack)(vector *_vector, DataType input)//AKA insert last
{
    return function(Insert)(_vector, input, _vector->_size);
}

DataType function(Remove)(vector *_vector, int rank)
{
    /*remove one element, move elements one place forward if necessary*/
    DataType temp = _vector->_data[rank];
    memmove(&(_vector->_data[rank]), &(_vector->_data[rank + 1]), sizeof(DataType) * (_vector->_size - 1 - rank));
    _vector->_size -= 1;
    return temp;
}

DataType function(PopBack)(vector *_vector)
{
    /*remove the last*/
    return function(Remove)(_vector, _vector->_size - 1);
}

int function(RemoveMultiple)(vector *_vector, int start_rank, int end_rank)
{
    if (start_rank < 0 || end_rank > _vector->_size || _vector == NULL)
        return 0;
    _vector->_size -= (end_rank - start_rank);
    memmove(&(_vector->_data[start_rank]), &(_vector->_data[end_rank]), _vector->_size - end_rank);
    return _vector->_size;
}

int function(Disordered)(const vector *_vector);
int function(Sort)(vector *_vector);
int function(Find)(const vector *_vector, DataType target, int *result_rank);
int function(Search)(const vector *_vector, DataType target, int *result_rank);
int function(Deduplicate)(vector *_vector);
int function(Uniquify)(vector *_vector);

void function(Traverse)(vector *_vector, void (*callback)(DataType *))
{
    /*do same action for all elements takes in argument of a call back funtion*/
    int i;
    for (i = 0; i < _vector->_size; i++)
    {
        callback(&_vector->_data[i]);
    }
}

void function(Destruct)(vector *_vector)
{
    /*savely destruct the vector*/
    if (_vector == NULL)
        return;
    free(_vector->_data);
    free(_vector);
    _vector = NULL;
    return;
}

/*function used when involes in comparison overload*/
int function(DisorderedOL)(const vector *_vector, int (*IsEqual)(const DataType *, const DataType *));
int function(SortOL)(vector *_vector, int (*IsEqual)(const DataType *, const DataType *));
int function(FindOL)(const vector *_vector, DataType target, int *result_rank, int (*IsEqual)(const DataType *, const DataType *));
int function(SearchOL)(const vector *_vector, DataType target, int *result_rank, int (*IsEqual)(const DataType *, const DataType *));
int function(DeduplicateOL)(vector *_vector, int (*IsEqual)(const DataType *, const DataType *));
int function(UniquifyOL)(vector *_vector, int (*IsEqual)(const DataType *, const DataType *));
