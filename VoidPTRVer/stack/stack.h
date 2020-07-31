#ifndef STACK_H
#define STACK_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../vector/vectorPTR.h"

#define stack vector


stack * StackCreate(int DataSize);
int StackSize(stack * _stack);
int StackPush(stack * _stack, const void * input_ptr);
const void * StackPop(stack * _stack);
const void * StackTop(stack * _stack);
int StackEmpty(stack * _stack);
void StackDestruct(stack * _stack);



#endif /*STACK_H*/