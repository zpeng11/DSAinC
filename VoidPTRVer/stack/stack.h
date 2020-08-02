#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"

typedef struct stack
{
    struct vector _vector;
} stack;

stack StackCreate(int DataSize);
#define StackSize(stackPTR) (((vector *)(stackPTR))->_size)
int StackPush(stack *_stack, const void *input_ptr);
const void *StackPop(stack *_stack);
const void *StackTop(stack *_stack);
#define StackEmpty(stackPTR) (!(((vector *)(stackPTR))->_size))
void StackDestruct(stack *_stack);

#endif /*STACK_H*/