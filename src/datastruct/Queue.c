#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "Queue.h"


void QueueInit(Queue* queue, int size, int num, QueuePrtHook prt)
{
    assert(size > 1);
    queue->array = malloc(size * num);
    assert(queue->array);
    memset(queue->array, 0, size * num);
    queue->size = size;
    queue->num = num;
    queue->begin = 0;
    queue->end = 0;
    queue->prt = prt;
}

void QueueDeinit(Queue* queue)
{
    if (queue->array) {
        free(queue->array);
    }
    queue->size = 0;
    queue->num = 0;
    queue->begin = 0;
    queue->end = 0;
    queue->prt = NULL;
}

int QueueIsEmpty(Queue* queue)
{
    return queue->begin == queue->end;
}

int QueueIsFull(Queue* queue)
{
    return ((queue->end - queue->begin + queue->num) % queue->num) == queue->num - 1;
}

void* GetItemByIndex(Queue* queue, int idx)
{
    return (char*)(queue->array) + idx * queue->size;
}

int QueueInsert(Queue* queue, void* item, int size)
{
    assert(queue->size == size);
    if (QueueIsFull(queue)) {
        return 0;
    }
    memcpy(GetItemByIndex(queue, queue->end), item, size);
    queue->end = (queue->end + 1) % queue->num;
    return 1;
}

int QueuePop(Queue* queue, void* item, int size)
{
    assert(queue->size == size);
    if (QueueIsEmpty(queue)) {
        return 0;
    }
    memcpy(item, GetItemByIndex(queue, queue->begin), size);
    queue->begin = (queue->begin + 1) % queue->num;
    return 1;
}

void QueuePrint(Queue* queue)
{
    for (int i = queue->begin, cnt = 0; cnt < ((queue->end - queue->begin + queue->num) % queue->num);
        cnt++, i = (i + 1) % queue->num) {
        queue->prt(GetItemByIndex(queue, i));
        printf("\n");
    }
}