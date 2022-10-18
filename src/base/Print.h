#ifndef __PRINT_H__
#define __PRINT_H__

enum {
    E_MAP_SPACE,
    E_MAP_OBSTACLE,
    E_MAP_PATH,

    E_MAP_BUT
};

/* 获取地形信息钩子函数 
Return:
    @E_MAP_SPACE: 空地
    @E_MAP_OBSTACLE: 障碍物
    @E_MAP_PATH: 路径 */
typedef int (*PrintMapInfoHook)(int x, int y);

/* 打印地图信息
Parameter:
    @width: IN x
    @height: IN y
    @getType: IN get terain of map
Return: NA */
void PrintMapInfo(int width, int height, PrintMapInfoHook getType);

#endif