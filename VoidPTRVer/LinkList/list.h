#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"
typedef struct ListNode
{
    void *_data;
    struct ListNode *pred;
    struct ListNode *succ;
} ListNode;

typedef struct list
{
    ListNode *header;
    ListNode *tailer;
    int _size;
    int _DataSize;
    int (*IsEqual)(const void *, const void *);
    int (*IsGreater)(const void *, const void *);
} list;

list ListCreate(int DataSize, int (*IsEqual)(const void *, const void *), int (*IsGreater)(const void *, const void *));//create a list 
list ListCreateWithPtr(int DataSize, const void *input_ptr, int num_2_create, int (*IsEqual)(const void *, const void *), int (*IsGreater)(const void *, const void *));//create a list from a array
void *ListGet(list *_list, int position);//get data element at specific position in a list, O(n) complexity
#define ListSize(listPTR) ((listPTR)->_size)// get the element number in the list
int ListInsertAsFirst(list *_list, const void *input_ptr);//insert as first element O(1) complexity
int ListInsertAsLast(list *_list, const void *input_ptr);///insert as first element O(1) complexity
int ListInsertBefore(list *_list, int position, const void *input_ptr);//insertion O(1) complexity
int ListInsertAfter(list *_list, int position, const void *input_ptr);//insertion O(1) complexity
const void * ListRemove(list *_list, int position);//remove O(1) complexity
int ListFind(list *_list, const void *target);//find an element O(n) complexity

int ListDisorderedOL(list *_list);//check if the list is disordered, O(n) complexity
int ListFindOL(list *_list, const void *target);//find a specific element in the list O(n)complexity
void ListSortOL(list *_list);//use insertion sort to sort elements in the list O(n^2) complexity
void ListInsertSortOL(list *_list);
void ListUniquifyOL(list *_list);

void ListTraverse(list *_list, void (*callback)(void *));//do same action to all elements
void ListMove(list *_list, int Dst, int Src);//move an node to another position in the list O(1) complexity
void ListExchange(list *_list, int left, int right);//exchange two element in the list
void ListDestruct(list *_list);//destruct the list O(n) complexity
ListNode *NodeGet(list *_list, int position);//return element at position O(n) complexity
#endif /*LIST_H*/