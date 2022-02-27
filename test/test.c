#include "stdio.h"
#include "../src/Heap.h"

void Prt(void* item)
{
    unsigned int* tmp = (unsigned int*)item;
    printf("%d", *tmp);
}

int Cmp(void* a, void* b)
{
    unsigned int* ita = (unsigned int*)a;
    unsigned int* itb = (unsigned int*)b;
    return *ita < *itb;
}

int main()
{
    Heap heap;
    HeapInit(&heap, sizeof(unsigned int), 10, Cmp, Prt);
    unsigned int tmp = 10;
    for (int i = 0; i < 10; i++) {
        HeapInsert(&heap, &tmp, sizeof(unsigned int));
        tmp--;
    }
    HeapPrint(&heap);
    return 0;
}