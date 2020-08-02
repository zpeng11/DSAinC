#include "list.h"

ListNode *NodeCreate(int DataSize);
ListNode *NodeCreateWithPtr(int DataSize, const void *input_ptr);
ListNode *NodeGet(list *_list, int position);
void NodeInsertBefore(ListNode *old, ListNode *new);
void NodeInsertAfter(ListNode *old, ListNode *new);
void NodeDecouple(ListNode *node);
void NodeMoveBefore(ListNode *Dst, ListNode *Src);
void NodeDestruct(ListNode *_ListNode);
//node opertations
ListNode *NodeCreate(int DataSize)
{
    ListNode *ptr = (ListNode *)malloc(sizeof(ListNode));
    ptr->pred = NULL;
    ptr->succ = NULL;
    ptr->_data = malloc(DataSize);
    return ptr;
}

ListNode *NodeCreateWithPtr(int DataSize, const void *input_ptr)
{
    ListNode *ptr = NodeCreate(DataSize);
    memcpy(ptr->_data, input_ptr, DataSize);
    return ptr;
}

ListNode *NodeGet(list *_list, int position)
{
    if (!(0 <= position && position < _list->_size))
    {
        return NULL;
    }
    ListNode *ptr;
    if (position > (_list->_size >> 1))
    {
        ptr = _list->tailer->pred;
        for (int i = _list->_size - 1; position < i; i--)
        {
            ptr = ptr->pred;
        }
    }
    else
    {
        ptr = _list->header->succ;
        for (int i = 0; i < position; i++)
        {
            ptr = ptr->succ;
        }
    }
    return ptr;
}

void NodeInsertBefore(ListNode *old, ListNode *new)
{
    new->pred = old->pred;
    new->succ = old;
    old->pred->succ = new;
    old->pred = new;
}

void NodeInsertAfter(ListNode *old, ListNode *new)
{
    new->pred = old;
    new->succ = old->succ;
    old->succ->pred = new;
    old->succ = new;
}

void NodeDecouple(ListNode *node)
{
    if (node->pred)
    {
        node->pred->succ = node->succ;
    }
    if (node->succ)
    {
        node->succ->pred = node->pred;
    }
}

void NodeMoveBefore(ListNode *Dst, ListNode *Src)
{
    NodeDecouple(Src);
    NodeInsertBefore(Dst, Src);
}

void NodeDestruct(ListNode *_ListNode)
{
    free(_ListNode->_data);
    free(_ListNode);
}

//list operations
list ListCreate(int DataSize)
{
    list new = {._DataSize = DataSize, ._size = 0};
    new.header = NodeCreate(DataSize);
    new.tailer = NodeCreate(DataSize);
    new.header->succ = new.tailer;
    new.tailer->pred = new.header;
    return new;
}

list ListCreateWithPtr(int DataSize, const void *input_ptr, int num_2_create)
{
    list new = ListCreate(DataSize);
    for (int i = 0; i < num_2_create; i++)
    {
        ListInsertAsLast(&new, input_ptr + new._DataSize *i);
    }
    return new;
}

void *ListGet(list *_list, int position)
{
    return (NodeGet(_list, position))->_data;
}



int ListInsertAsFirst(list *_list, const void *input_ptr)
{
    ListNode *ptr = NodeCreateWithPtr(_list->_DataSize, input_ptr);
    _list->_size += 1;
    NodeInsertAfter(_list->header, ptr);
    return _list->_size;
}

int ListInsertAsLast(list *_list, const void *input_ptr)
{
    ListNode *ptr = NodeCreateWithPtr(_list->_DataSize, input_ptr);
    _list->_size += 1;
    NodeInsertBefore(_list->tailer, ptr);
    return _list->_size;
}

int ListInsertBefore(list *_list, int position, const void *input_ptr)
{
    ListNode *ptr = NodeCreateWithPtr(_list->_DataSize, input_ptr);
    NodeInsertBefore(NodeGet(_list, position), ptr);
    _list->_size += 1;
    return _list->_size;
}

int ListInsertAfter(list *_list, int position, const void *input_ptr)
{
    ListNode *ptr = NodeCreateWithPtr(_list->_DataSize, input_ptr);
    NodeInsertAfter(NodeGet(_list, position), ptr);
    _list->_size += 1;
    return _list->_size;
}

const void * ListRemove(list *_list, int position)
{
    ListNode *ptr = NodeGet(_list, position);
    memcpy(_list->tailer->_data,ptr->_data,_list->_DataSize );
    NodeDecouple(ptr);
    NodeDestruct(ptr);
    _list->_size -= 1;
    return  _list->tailer->_data;
}

void ListMove(list *_list, int Dst, int Src)
{
    ListNode *SourceNode = NodeGet(_list, Src);
    ListNode *InsertNode = NodeGet(_list, Dst);
    NodeDecouple(SourceNode);
    if (Dst < Src)
        NodeInsertBefore(InsertNode, SourceNode);
    else
        NodeInsertAfter(InsertNode, SourceNode);
}

void ListExchange(list *_list, int left, int right)
{
    if (left < right)
    {
        int temp = left;
        left = right;
        right = temp;
    }
    ListMove(_list, left, right);
    ListMove(_list, right, left + 1);
}

int ListDisorderedOL(list *_list, int (*IsGeater)(const void *, const void *))
{
    ListNode *left = _list->header->succ;
    ListNode *right = left->succ;
    int n = 0;
    while (right->succ)
    {
        n += IsGeater(left->_data, right->_data);
        right = right->succ;
        left = left->succ;
    }
    return n;
}

int ListFind(list *_list, const void *target)
{
    ListNode *ptr = _list->tailer->pred;
    int n = _list->_size - 1;
    while (ptr->pred && memcmp(ptr->_data, target, _list->_DataSize))
    {
        ptr = ptr->pred;
        n--;
    }
    return n;
}

int ListFindOL(list *_list, const void *target, int (*IsEqual)(const void *, const void *))
{
    ListNode *ptr = _list->tailer->pred;
    int n = _list->_size - 1;
    while (ptr->pred && !IsEqual(ptr->_data, target))
    {
        ptr = ptr->pred;
        n--;
    }
    return n;
}

void ListSortOL(list *_list, int (*IsGreater)(const void *, const void *));

void ListInsertSortOL(list *_list, int (*IsGreater)(const void *, const void *))
{
    ListNode *left = _list->header->succ;
    ListNode *right = left->succ;
    while (right->succ)
    {
        left = _list->header->succ;
        while (left != right)
        {
            if (IsGreater(left->_data, right->_data))
            {
                right = right->pred;
                NodeMoveBefore(left, right->succ);
                break;
            }
            left = left->succ;
        }
        right = right->succ;
    }
}

/*
void ListMergeSort(list *_list, int(*IsGreater)(const void * , const void *))
{
    vector SortVec = VecCreate(_list->_DataSize);
    ListNode * temp = _list->header->succ;
    for (int i =0;i<_list->_size;i++)
    {
        VecPushBack(&SortVec,temp->_data);
        temp = temp->succ;
    }
}
*/

void ListUniquifyOL(list *_list, int (*IsEqual)(const void *, const void *))
{
    ListNode *left = _list->header->succ;
    ListNode *right = left->succ;
    while (right->succ)
    {
        if (IsEqual(left->_data, right->_data))
        {
            ListNode *temp = right->succ;
            NodeDecouple(right);
            NodeDestruct(right);
            _list->_size -= 1;
            right = temp;
        }
        else
        {
            left = right;
            right = right->succ;
        }
    }
}

void ListTraverse(list *_list, void (*callback)(void *))
{
    ListNode *ptr = _list->header->succ;
    while (ptr->succ)
    {
        callback(ptr->_data);
        ptr = ptr->succ;
    }
}

void ListDestruct(list *_list)
{
    ListNode *ptr = _list->header;
    while (1)
    {
        ListNode *temp = ptr->succ;
        NodeDestruct(ptr);
        ptr = temp;
        if (!ptr)
            return;
    }
}