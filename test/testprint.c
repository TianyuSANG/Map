#include <stdio.h>

#include "Print.h"

int g_map[10][10] = {0};

int GetTerain(int x, int y)
{
    return g_map[x][y];
}

int main()
{
    g_map[0][1] = E_MAP_OBSTACLE;
    g_map[0][2] = E_MAP_OBSTACLE;
    g_map[3][5] = E_MAP_OBSTACLE;
    g_map[1][3] = E_MAP_OBSTACLE;
    g_map[1][4] = E_MAP_OBSTACLE;
    PrintMapInfo(10, 10, GetTerain);
    return 0;
}