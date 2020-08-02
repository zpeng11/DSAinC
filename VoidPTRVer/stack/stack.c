#include "stack.h"

stack StackCreate(int DataSize)
{
    stack new;
    new._vector = VecCreate(DataSize);
    return new;
}

int StackPush(stack *_stack, const void *input_ptr)
{
    return VecPushBack(((vector *)_stack), input_ptr);
}
const void *StackPop(stack *_stack)
{
    return VecPopBack(((vector *)_stack));
}

const void *StackTop(stack *_stack)
{
    return VecGet(((vector *)_stack), _stack->_vector._size - 1);
}

void StackDestruct(stack *_stack)
{
    VecDestruct(((vector *)_stack));
}