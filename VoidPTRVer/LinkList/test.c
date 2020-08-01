#include <stdio.h>
#include "list.h"
#define INT *(int *)

int IntIsEqual(const void *left, const void *right)
{
    return (int)*(int *)left == (int)*(int *)right;
}

int DoubleIsEqual(const void *left, const void *right)
{
    return (double)*(double *)left == (double)*(double *)right;
}

int IntIsGreater(const void *left, const void *right)
{
    return (int)*(int *)left > (int)*(int *)right;
}

int DoubleIsGreater(const void *left, const void *right)
{
    return (double)*(double *)left > (double)*(double *)right;
}

void addone(void *input)
{
    INT input = INT input + 1;
}

void swp(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
    printf("\na:%i  b:%i  \n", a, b);
}

int main()
{
    int b[] = {5, 2, 2, 0};
    list a = ListCreateWithPtr(sizeof(int), b, 4);
    ListUniquifyOL(&a, IntIsEqual);
    int d = 2;
    int c = ListFindOL(&a, &d, IntIsEqual);
    printf("%i", c);
    ListDestruct(&a);
}