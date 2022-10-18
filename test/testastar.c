#include <stdio.h>

#include "AStar.h"
#include "Print.h"
#include "Log.h"

#define MAP_WIDTH  20
#define MAP_HEIGHT 20
int g_map[MAP_WIDTH][MAP_HEIGHT] = {0};

int GetTerain(Pos pos)
{
    return g_map[pos.x][pos.y];
}

int GetMapType(int x, int y)
{
    Pos tmp;
    tmp.x = x;
    tmp.y = y;
    return GetTerain(tmp);
}

int main()
{
    g_map[0][1] = E_MAP_OBSTACLE;
    g_map[0][2] = E_MAP_OBSTACLE;
    g_map[1][2] = E_MAP_OBSTACLE;
    g_map[1][3] = E_MAP_OBSTACLE;
    g_map[2][2] = E_MAP_OBSTACLE;
    g_map[5][5] = E_MAP_OBSTACLE;
    g_map[4][6] = E_MAP_OBSTACLE;
    g_map[6][4] = E_MAP_OBSTACLE;
    g_map[6][5] = E_MAP_OBSTACLE;
    g_map[5][6] = E_MAP_OBSTACLE;
    PrintMapInfo(MAP_WIDTH, MAP_HEIGHT, GetMapType);
    AStar astar;
    AStarInit(&astar, MAP_WIDTH, MAP_HEIGHT, GetTerain);
    Pos path[1000];
    int stepNum = 0;
    Pos begin = {0, 0};
    Pos end = {19, 19};
    LOGC(LOG_LEVEL_INFO, "AStarGetPath Start");
    AStarGetPath(&astar, begin, end, path, &stepNum);
    LOGC(LOG_LEVEL_INFO, "AStarGetPath End stepNum=%d", stepNum);
    for (int i = 0; i < stepNum; i++) {
        printf("(%d,%d)\n", path[i].x, path[i].y);
    }
    for (int i = 0; i < stepNum; i++) {
        g_map[path[i].x][path[i].y] = E_MAP_PATH;
    }
    PrintMapInfo(MAP_WIDTH, MAP_HEIGHT, GetMapType);
    AStarDeinit(&astar);
    return 0;
}