#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Heap.h"

void HeapInit(Heap* heap, unsigned int size, unsigned int num, void* cmp, void* prt)
{
    heap->array = (void*)malloc(size * num);
    assert(heap->array);
    heap->size = size;
    heap->num = num;
    heap->cnt = 0;
    assert(cmp);
    assert(prt);
    heap->cmp = (HeapCmpHook)cmp;
    heap->prt = (HeapPrtHook)prt;
}

void HeapDeinit(Heap* heap)
{
    if (heap->array) {
        free(heap->array);
    }
    heap->array = NULL;
    heap->size = 0;
    heap->num = 0;
    heap->cnt = 0;
    heap->cmp = NULL;
}

int HeapIsFull(Heap* heap)
{
    return heap->cnt == heap->num;
}

int HeapIsEmpty(Heap* heap)
{
    return heap->cnt == 0;
}

void* HeapGetItem(Heap* heap, unsigned idx)
{
    return (char*)heap->array + idx * heap->size;
}

void HeapExchange(Heap* heap, unsigned a, unsigned b)
{
    void* tmp = (void*)malloc(heap->size);
    assert(tmp);
    memcpy(tmp, HeapGetItem(heap, a), heap->size);
    memcpy(HeapGetItem(heap, a), HeapGetItem(heap, b), heap->size);
    memcpy(HeapGetItem(heap, b), tmp, heap->size);
    free(tmp);
}

void HeapItemRefresh(Heap* heap, int idx)
{
    int child = idx;
    int father = (child % 2 == 0 ? child / 2 - 1 : child / 2);
    for (; father >= 0; child = father, father = (child % 2 == 0 ? child / 2 - 1 : child / 2)) {
        if (heap->cmp(HeapGetItem(heap, child), HeapGetItem(heap, father))) {
            HeapExchange(heap, child, father);
        } else {
            break;
        }
    }
}

int HeapInsert(Heap* heap, void* item, unsigned int size)
{
    assert(heap->size == size);
    if (HeapIsFull(heap)) {
        return 0;
    }
    memcpy(HeapGetItem(heap, heap->cnt), item, size);
    heap->cnt++;
    
    int child = heap->cnt - 1;
    int father = (child % 2 == 0 ? child / 2 - 1 : child / 2);
    for (; father >= 0; child = father, father = (child % 2 == 0 ? child / 2 - 1 : child / 2)) {
        if (heap->cmp(HeapGetItem(heap, child), HeapGetItem(heap, father))) {
            HeapExchange(heap, child, father);
        } else {
            break;
        }
    }

    return 1;
}

int HeapPop(Heap* heap, void* item, unsigned int size)
{
    assert(heap->size == size);
    if (HeapIsEmpty(heap)) {
        return 0;
    }
    memcpy(item, HeapGetItem(heap, 0), size);
    HeapExchange(heap, 0, heap->cnt - 1);
    heap->cnt -= 1;
    unsigned int father = 0;
    unsigned int child = 2 * father + 1;
    for (; child < heap->cnt; father = child, child = 2 * father + 1) {
        if (child + 1 < heap->cnt && heap->cmp(HeapGetItem(heap, child + 1), HeapGetItem(heap, child))) {
            child = child + 1;
        }
        if (heap->cmp(HeapGetItem(heap, child), HeapGetItem(heap, father))) {
            HeapExchange(heap, child, father);
        } else {
            break;
        }
    }
    return 1;
}

void HeapPrint(Heap* heap)
{
    int num = 1;
    int cnt = 0;
    for (int i = 0; i < heap->cnt; i++) {
        heap->prt(HeapGetItem(heap, i));
        printf("  ");
        cnt++;
        if (cnt == num || i == heap->cnt - 1) {
            num = num * 2;
            cnt = 0;
            printf("\n");
        }
    }
}