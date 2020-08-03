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

list ListCreate(int DataSize, int (*IsEqual)(const void *, const void *), int (*IsGreater)(const void *, const void *));
list ListCreateWithPtr(int DataSize, const void *input_ptr, int num_2_create, int (*IsEqual)(const void *, const void *), int (*IsGreater)(const void *, const void *));
void *ListGet(list *_list, int position);
#define ListSize(listPTR) ((listPTR)->_size)
int ListInsertAsFirst(list *_list, const void *input_ptr);
int ListInsertAsLast(list *_list, const void *input_ptr);
int ListInsertBefore(list *_list, int position, const void *input_ptr);
int ListInsertAfter(list *_list, int position, const void *input_ptr);
const void * ListRemove(list *_list, int position);
int ListFind(list *_list, const void *target);

int ListDisorderedOL(list *_list);
int ListFindOL(list *_list, const void *target);
void ListSortOL(list *_list);
void ListInsertSortOL(list *_list);
void ListUniquifyOL(list *_list);

void ListTraverse(list *_list, void (*callback)(void *));
void ListMove(list *_list, int Dst, int Src);
void ListExchange(list *_list, int left, int right);
void ListDestruct(list *_list);
ListNode *NodeGet(list *_list, int position);
#endif /*LIST_H*/