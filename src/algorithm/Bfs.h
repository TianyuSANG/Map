#ifndef __BFS_H__
#define __BFS_H__

#include "Pos.h"

#define BFS_SPACE 0
#define BFS_OBSTACLE 1

/* 获取地形信息 返回值为BFS_SPACE 或者 BFS_OBSTACLE */
typedef int (*BfsMapInfoHook)(Pos pos);

typedef struct {
    int* flag;                 /* 地图上走过的标记 */
    Pos* father;               /* 地图上坐标的父亲坐标 */
    int width;                 /* 地图宽度，x < width */
    int height;                /* 地图高度，y < height */
    BfsMapInfoHook getType;    /* 获取地图的地形信息 */
} Bfs;

/* 使用Bfs算法前调用该接口进行初始化 
Parameter:
    @bfs: IN
    @width: IN the width of map
    @height: IN the height of map
    @getType: IN the func get terain type
Return: NA */
void BfsInit(Bfs* bfs, int width, int height, BfsMapInfoHook getType);

/* 使用Bfs算法后调用该接口进行去初始化 
Parameter:
    @bfs: IN
Return: NA */
void BfsDeinit(Bfs* bfs);

/* 使用该接口可以获取路径信息
Parameter:
    @bfs: IN
    @begin: IN begin pos
    @end: IN end pos
    @path: OUT the array of path from begin to end
    @stepNum: OUT
Return: 
    @0: fail to find the path
    @1: success find the path */
int BfsGetPath(Bfs* bfs, Pos begin, Pos end, Pos* path, int* stepNum);

#endif