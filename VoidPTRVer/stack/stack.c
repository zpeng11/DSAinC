#include "stack.h"

stack StackCreate(int DataSize)
{
    stack new;
    new._vector = VecCreate(DataSize);
    return new;
}

int StackSize(stack * _stack){
    return _stack->_vector._size;
}

int StackPush(stack * _stack, const void * input_ptr){
    return VecPushBack(&(_stack->_vector), input_ptr);
}
const void * StackPop(stack * _stack)
{
    return VecPopBack(&(_stack->_vector));
}

const void * StackTop(stack * _stack)
{
    return VecGet(&(_stack->_vector), _stack->_vector._size-1);
}



int StackEmpty(stack * _stack){
    return !VecSize(&(_stack->_vector));
}

void StackDestruct(stack * _stack)
{
    VecDestruct(&(_stack->_vector));
}