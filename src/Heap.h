#ifndef __HEAP_H__
#define __HEAP_H__

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"

typedef int (*Compare)(void* a, void* b);
typedef void (*Print)(void* item);

typedef struct {
    void* array;
    unsigned int num;  // 堆元素容量
    unsigned int size; // 堆元素大小
    unsigned int cnt;  // 当前堆元素个数
    Compare cmp;       // 比较函数，返回值大于0，则上移动，小于等于0，不用动
    Print prt;         // 打印函数，打印一个元素的内容
} Heap;

static inline void HeapInit(Heap* heap, unsigned int size, unsigned int num, void* cmp, void* prt)
{
    heap->array = (void*)malloc(size * num);
    assert(heap->array);
    heap->size = size;
    heap->num = num;
    heap->cnt = 0;
    assert(cmp);
    assert(prt);
    heap->cmp = (Compare)cmp;
    heap->prt = (Print)prt;
}

static inline void HeapDeinit(Heap* heap)
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

static inline int HeapIsFull(Heap* heap)
{
    return heap->cnt == heap->num;
}

static inline int HeapIsEmpty(Heap* heap)
{
    return heap->cnt == 0;
}

static inline void* HeapGetItem(Heap* heap, unsigned idx)
{
    return (char*)heap->array + idx * heap->size;
}

static inline void HeapExchange(Heap* heap, unsigned a, unsigned b)
{
    void* tmp = (void*)malloc(heap->size);
    assert(tmp);
    memcpy(tmp, HeapGetItem(heap, a), heap->size);
    memcpy(HeapGetItem(heap, a), HeapGetItem(heap, b), heap->size);
    memcpy(HeapGetItem(heap, b), tmp, heap->size);
}

static inline int HeapInsert(Heap* heap, void* item, unsigned int size)
{
    assert(heap->size == size);
    if (HeapIsFull(heap)) {
        return false;
    }
    memcpy(HeapGetItem(heap, heap->cnt), item, size);
    heap->cnt++;
    
    unsigned int child = heap->cnt - 1;
    unsigned int father = (child % 2 == 0 ? child / 2 - 1 : child / 2);
    for (; father >= 0; child = father, father = (child % 2 == 0 ? child / 2 - 1 : child / 2)) {
        if (heap->cmp(HeapGetItem(heap, child), HeapGetItem(heap, father))) {
            HeapExchange(heap, child, father);
        } else {
            break;
        }
    }

    return true;
}

static inline int HeapPop(Heap* heap, void* item, unsigned int size)
{
    assert(heap->size == size);
    if (HeapIsEmpty(heap)) {
        return false;
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
    return true;
}

static inline void HeapPrintItems(Heap* heap)
{
    for (unsigned i = 0; i < heap->cnt; i++) {
        heap->prt(HeapGetItem(heap, i));
        printf("\n");
    }
}


#endif