#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"
typedef struct ListNode
{
    void *_data;
    int _DataSize;
    struct ListNode *pred;
    struct ListNode *succ;
} ListNode;

typedef struct list
{
    ListNode *header;
    ListNode *tailer;
    int _size;
    int _DataSize;
} list;

list ListCreate(int DataSize);
list ListCreateWithPtr(int DataSize, const void *input_ptr, int num_2_create);
void *ListGet(list *_list, int position);
int ListSize(list *_list);
int ListInsertAsFirst(list *_list, const void *input_ptr);
int ListInsertAsLast(list *_list, const void *input_ptr);
int ListInsertBefore(list *_list, int position, const void *input_ptr);
int ListInsertAfter(list *_list, int position, const void *input_ptr);
const void * ListRemove(list *_list, int position);
int ListDisorderedOL(list *_list, int (*IsGeater)(const void *, const void *));
int ListFind(list *_list, const void *target);
int ListFindOL(list *_list, const void *target, int (*IsEqual)(const void *, const void *));
void ListSortOL(list *_list, int(IsGreater)(const void *, const void *));
void ListInsertSortOL(list *_list, int (*IsGreater)(const void *, const void *));
void ListUniquifyOL(list *_list, int (*IsEqual)(const void *, const void *));
void ListTraverse(list *_list, void (*callback)(void *));
void ListMove(list *_list, int Dst, int Src);
void ListExchange(list *_list, int left, int right);
void ListDestruct(list *_list);
ListNode *NodeGet(list *_list, int position);
#endif /*LIST_H*/