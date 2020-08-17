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

stack StackCreate(int DataSize);//create a stack which is a vector actually
#define StackSize(stackPTR) (((vector *)(stackPTR))->_size)//return element number in the stack
int StackPush(stack *_stack, const void *input_ptr);//put an element at the top of the stack
const void *StackPop(stack *_stack);//pop out the top element in the stack 
void *StackTop(stack *_stack);//get the top element in the stack
#define StackEmpty(stackPTR) (!(((vector *)(stackPTR))->_size))//check if the stack is empty
void StackDestruct(stack *_stack);//destruct the stack and clean all elements

#endif /*STACK_H*/