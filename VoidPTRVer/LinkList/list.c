#include "list.h"

ListNode *NodeCreate(int DataSize)
{
    ListNode *ptr = (ListNode *)malloc(sizeof(ListNode));
    ptr->_DataSize = DataSize;
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

void NodeDestruct(ListNode *_ListNode)
{
    free(_ListNode->_data);
    free(_ListNode);
}

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

int ListSize(list *_list)
{
    return _list->_size;
}

static void NodeInsertBefore(ListNode *old, ListNode *new)
{
    new->pred = old->pred;
    new->succ = old;
    old->pred->succ = new;
    old->pred = new;
}

static void NodeInsertAfter(ListNode *old, ListNode *new)
{
    new->pred = old;
    new->succ = old->succ;
    old->succ->pred = new;
    old->succ = new;
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
    NodeInsertBefore(NodeGet(_list, position), ptr);
    _list->_size += 1;
    return _list->_size;
}

static void NodeDecouple(ListNode *node)
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

int ListRemove(list *_list, int position)
{
    ListNode * ptr = NodeGet(_list, position);
    NodeDecouple(NodeGet(_list, position));
    NodeDestruct(ptr);
    _list->_size -= 1;
    return _list->_size;
}


void ListMove(list *_list, int Dst, int Src)
{
    ListNode * SourceNode= NodeGet(_list, Src);
    ListNode * InsertNode = NodeGet(_list, Dst);
    NodeDecouple(SourceNode);
    NodeInsertBefore(InsertNode, SourceNode);
}


int ListDisorderedOL(list *_list, int (*IsGeater)(const void *, const void *))
{
    ListNode * left = _list->header->succ;
    ListNode * right = left->succ;
    int n = 0;
    while(right->succ)
    {
        n += IsGeater(left->_data, right->_data);
    }
    return n;
}


int ListFind(list *_list, const void *target)
{
    ListNode * ptr = _list->tailer->pred;
    int n = _list->_size -1;
    while(ptr->pred && memcmp(ptr->_data, target, _list->_DataSize))
    {
        ptr = ptr->pred;
        n--;
    }
    return n;
}

int ListFindOL(list *_list, const void *target, int (* IsEqual)(const void *, const void *))
{
    ListNode * ptr = _list->tailer->pred;
    int n = _list->_size-1;
    while (ptr->pred && !IsEqual(ptr->_data, target) )
    {
        ptr = ptr->pred;
        n--;
    }
    return n;
}



void ListSortOL(list *_list, int(* IsGreater)(const void *, const void *));

static void NodeMoveBefore(ListNode * Dst, ListNode * Src)
{
    NodeDecouple(Src);
    NodeInsertBefore(Dst,Src);
}

void ListInsertSortOL(list *_list, int(* IsGreater)(const void *, const void *))
{
    ListNode * left = _list->header->succ;
    ListNode * right = left->succ;
    while(right ->succ)
    {
        left = _list->header->succ;
        while(left != right)
        {
            if(IsGreater(left->_data, right->_data)){
                right = right->pred;
                NodeMoveBefore(left, right->succ);
                break;
            }
            left = left->succ;
        }
        right = right->succ;
    }
}

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

int ListSearchOL(list *_list, const void *target, int (*IsGreater)(const void *, const void *));
void ListUniquifyOL(list *_list);
void ListTraverse(list *_list, void (*callback)(void *));

void ListExchange(list *_list, int left, int right);
void ListDestruct(list *_list);