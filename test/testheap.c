#include <stdio.h>

#include "Heap.h"

void Prt(void* item)
{
    unsigned int* tmp = (unsigned int*)item;
    printf("%- 3d", *tmp);
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
    printf("HeapInsert After:\n");
    HeapPrint(&heap);

    void* item = HeapGetItem(&heap, 5);
    *(unsigned int*)item = 0;
    HeapItemRefresh(&heap, 5);
    printf("HeapItemRefresh After:\n");
    HeapPrint(&heap);

    for (int i = 0; i < 5; i++) {
        HeapPop(&heap, &tmp, sizeof(unsigned int));
    }
    printf("HeapPop After:\n");
    HeapPrint(&heap);
    return 0;
}