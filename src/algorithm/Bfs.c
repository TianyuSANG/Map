#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "Pos.h"
#include "Queue.h"
#include "Bfs.h"


void BfsInit(Bfs* bfs, int width, int height, BfsMapInfoHook getType)
{
    bfs->flag = malloc(sizeof(int) * width * height);
    bfs->father = malloc(sizeof(Pos) * width * height);
    assert(bfs->flag && bfs->father);
    memset(bfs->flag, 0, sizeof(int) * width * height);
    memset(bfs->father, 0, sizeof(Pos) * width * height);
    bfs->width = width;
    bfs->height = height;
    bfs->getType = getType;
}

void BfsDeinit(Bfs* bfs)
{
    if (bfs->flag) {
        free(bfs->flag);
    }
    if (bfs->father) {
        free(bfs->father);
    }
    bfs->getType = NULL;
    bfs->width = 0;
    bfs->height = 0;
}

static int BfsGetIdxByPos(Bfs* bfs, Pos pos)
{
    return pos.x * bfs->height + pos.y;
}

static int BfsIsPosValid(Bfs* bfs, Pos pos)
{
    if (pos.x < 0 || pos.x >= bfs->width || pos.y < 0 || pos.y >= bfs->height) {
        return 0;
    }
    return 1;
}

static void QueuePrintItem(void* item)
{
    Pos* tmp = item;
    printf("(%d,%d)", tmp->x, tmp->y);
}

int BfsGetPath(Bfs* bfs, Pos begin, Pos end, Pos* path, int* stepNum)
{
    memset(bfs->flag, 0, sizeof(int) * bfs->width * bfs->height);
    memset(bfs->father, 0, sizeof(Pos) * bfs->width * bfs->height);
    *stepNum = 0;
    Pos dir[8] = {
        {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
    };
    Queue queue;
    QueueInit(&queue, sizeof(Pos), bfs->width * bfs->height, QueuePrintItem);
    Pos item = begin;
    QueueInsert(&queue, &item, sizeof(Pos));
    bfs->flag[BfsGetIdxByPos(bfs, item)] = 1;
    bfs->father[BfsGetIdxByPos(bfs, item)] = item;
    int find = 0;
    while (!QueueIsEmpty(&queue)) {
        QueuePop(&queue, &item, sizeof(Pos));
        if (item.x == end.x && item.y == end.y) {
            find = 1;
            break;
        }
        Pos tmp;
        for (int i = 0; i < 8; i++) {
            tmp.x = item.x + dir[i].x;
            tmp.y = item.y + dir[i].y;
            if (!BfsIsPosValid(bfs, tmp) || bfs->flag[BfsGetIdxByPos(bfs, tmp)] == 1 || bfs->getType(tmp) == BFS_OBSTACLE) {
                continue;
            }
            QueueInsert(&queue, &tmp, sizeof(Pos));
            bfs->flag[BfsGetIdxByPos(bfs, tmp)] = 1;
            bfs->father[BfsGetIdxByPos(bfs, tmp)] = item;
        }
    }
    QueueDeinit(&queue);
    if (find == 0) {
        return 0;
    }
    Pos father = item;
    while (father.x != begin.x || father.y != begin.y) {
        path[*stepNum] = father;
        *stepNum = *stepNum + 1;
        father = bfs->father[BfsGetIdxByPos(bfs, father)];
    }
    path[*stepNum] = father;
    *stepNum = *stepNum + 1;
    return 1;
}