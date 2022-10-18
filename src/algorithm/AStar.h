#ifndef __ASTAR_H__
#define __ASTAR_H__

#include "Pos.h"

#define ASTAR_SPACE 0
#define ASTAR_OBSTACLE 1

/* 获取地形信息 返回值为ASTAR_SPACE 或者 ASTAR_OBSTACLE */
typedef int (*AStarMapInfoHook)(Pos pos);

typedef struct {
    int* flag;                   /* 地图上走过的标记 */
    Pos* father;                 /* 地图上坐标的父亲坐标 */
    int width;                   /* 地图宽度，x < width */
    int height;                  /* 地图高度，y < height */
    AStarMapInfoHook getTerain;  /* 获取地图的地形信息 */
} AStar;

/* 使用AStar算法前调用该接口进行初始化 
Parameter:
    @astar: IN
    @width: IN the width of map
    @height: IN the height of map
    @getTerain: IN the func get terain type
Return: NA */
void AStarInit(AStar* astar, int width, int height, AStarMapInfoHook getTerain);

/* 使用AStar算法后调用该接口进行去初始化 
Parameter:
    @astar: IN
Return: NA */
void AStarDeinit(AStar* astar);

/* 使用该接口可以获取路径信息
Parameter:
    @astar: IN
    @begin: IN begin pos
    @end: IN end pos
    @path: OUT the array of path from begin to end
    @stepNum: OUT
Return: 
    @0: fail to find the path
    @1: success find the path */
int AStarGetPath(AStar* astar, Pos begin, Pos end, Pos* path, int* stepNum);


#endif