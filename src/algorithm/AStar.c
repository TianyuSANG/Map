#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Heap.h"
#include "AStar.h"

void AStarInit(AStar* astar, int width, int height, AStarMapInfoHook getTerain)
{
    astar->flag = malloc(sizeof(int) * width * height);
    astar->father = malloc(sizeof(Pos) * width * height);
    assert(astar->flag && astar->father);
    memset(astar->flag, 0, sizeof(int) * width * height);
    memset(astar->father, 0, sizeof(Pos) * width * height);
    astar->width = width;
    astar->height = height;
    astar->getTerain = getTerain;
}

void AStarDeinit(AStar* astar)
{
    if (astar->flag) {
        free(astar->flag);
    }
    if (astar->father) {
        free(astar->father);
    }
    astar->width = 0;
    astar->height = 0;
    astar->getTerain = NULL;
}

typedef struct {
    Pos pos;
    int g; /* 当前坐标距离起点的距离 */
    int h; /* 当前坐标距离终点的距离 */
} HeapItem;

int HeapCmp(void* a, void* b)
{
    HeapItem* a_ = a;
    HeapItem* b_ = b;
    return (a_->g + a_->h) < (b_->g + b_->h);
}

void HeapPrt(void* item)
{
    HeapItem* tmp = item;
    printf("(%3d,%3d) g=%d h=%d f=%d", tmp->pos.x, tmp->pos.y, tmp->g, tmp->h, tmp->g + tmp->h);
}

int AStarGetDistance(Pos begin, Pos end)
{
    return abs(begin.x - end.x) + abs(begin.y - end.y);
}

int AStarIsPosValid(AStar* astar, Pos pos)
{
    if (pos.x < 0 || pos.x >= astar->width || pos.y < 0 || pos.y >= astar->height) {
        return 0;
    }
    return 1;
}

int AStarGetIndexByPos(AStar* astar, Pos pos)
{
    return pos.x * astar->height + pos.y;
}

int AStarGetPath(AStar* astar, Pos begin, Pos end, Pos* path, int* stepNum)
{
    memset(astar->flag, 0, sizeof(int) * astar->width * astar->height);
    memset(astar->father, 0, sizeof(Pos) * astar->width * astar->height);
    *stepNum = 0;
    Pos dir[8] = {
        {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
    };
    Heap heap;
    HeapInit(&heap, sizeof(HeapItem), astar->width * astar->height / 2, HeapCmp, HeapPrt);
    HeapItem item;
    item.pos.x = begin.x;
    item.pos.y = begin.y;
    item.g = 0;
    item.h = AStarGetDistance(begin, end);
    HeapInsert(&heap, &item, sizeof(HeapItem));                                                                                 
    astar->flag[AStarGetIndexByPos(astar, begin)] = 1;
    astar->father[AStarGetIndexByPos(astar, begin)] = begin;
    int find = 0;
    while (!HeapIsEmpty(&heap)) {
        HeapPop(&heap, &item, sizeof(HeapItem));
        if (item.pos.x == end.x && item.pos.y == end.y) {
            find = 1;
            break;
        }
        HeapItem tmp;
        for (int i = 0; i < 8; i++) {
            tmp.pos.x = item.pos.x + dir[i].x;
            tmp.pos.y = item.pos.y + dir[i].y;
            tmp.g = item.g + 1;
            tmp.h = AStarGetDistance(tmp.pos, end);
            if (!AStarIsPosValid(astar, tmp.pos) || astar->flag[AStarGetIndexByPos(astar, tmp.pos)] == 1 || astar->getTerain(tmp.pos) == ASTAR_OBSTACLE) {
                continue;
            }
            if (HeapIsFull(&heap)) {
                return 0;
            }
            HeapInsert(&heap, &tmp, sizeof(HeapItem));
            astar->flag[AStarGetIndexByPos(astar, tmp.pos)] = 1;
            astar->father[AStarGetIndexByPos(astar, tmp.pos)] = item.pos;
        }
    }
    HeapDeinit(&heap);
    if (find == 0) {
        return 0;
    }
    Pos father = end;
    while (father.x != begin.x || father.y != begin.y) {
        path[*stepNum] = father;
        *stepNum = *stepNum + 1;
        father = astar->father[AStarGetIndexByPos(astar, father)];
    }
    path[*stepNum] = father;
    *stepNum = *stepNum + 1;
    return 1;
}
