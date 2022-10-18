#include <stdio.h>

#include "Queue.h"

typedef struct {
    int x;
    int y;
} Pos;

void QueuePrintItem(void* item)
{
    Pos* tmp = item;
    printf("(%d,%d)", tmp->x, tmp->y);
}

int main()
{
    Queue queue;
    QueueInit(&queue, sizeof(Pos), 10, QueuePrintItem);
    for (int i = 0; i < 5; i++) {
        Pos tmp;
        tmp.x = i;
        tmp.y = i;
        QueueInsert(&queue, &tmp, sizeof(Pos));
    }
    printf("QueueInsert After:\n");
    QueuePrint(&queue);
    for (int i = 0; i < 3; i++) {
        Pos tmp;
        QueuePop(&queue, &tmp, sizeof(Pos));
    }
    printf("QueuePop After:\n");
    QueuePrint(&queue);
    QueueDeinit(&queue);
    return 0;
}