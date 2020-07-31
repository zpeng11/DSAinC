#include "stack.h"

stack * StackCreate(int DataSize)
{
    return VecCreate(DataSize);
}

int StackSize(stack * _stack){
    return VecSize(_stack);
}

int StackPush(stack * _stack, const void * input_ptr){
    return VecPushBack(_stack, input_ptr);
}
const void * StackPop(stack * _stack)
{
    return VecPopBack(_stack);
}

const void * StackTop(stack * _stack)
{
    return VecGet(_stack, _stack->_size-1);
}



int StackEmpty(stack * _stack){
    return !VecSize(_stack);
}

void StackDestruct(stack * _stack)
{
    VecDestruct(_stack);
}