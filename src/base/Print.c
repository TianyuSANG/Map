#include <stdio.h>

#include "Print.h"

void PrintMapInfo(int width, int height, PrintMapInfoHook getType)
{
    char terainMap[E_MAP_BUT][32] = {
        "   ", " ^ ", " . "
    };

    printf("---------------------MapInfo-------------------\n");
    for (int y = 0; y < height + 1; y++) {
        printf("----");
    }
    printf("-\n");
    for (int y = 0; y < height + 1; y++) {
        if (y == 0) {
            printf("|   ");
        } else {
            printf("|%3d", y - 1);
        }
    }
    printf("|\n");
    for (int x = 0; x < width; x++) {
        for (int t = 0; t < height + 1; t++) {
            printf("----");
        }
        printf("-\n");
        for (int y = 0; y < height + 1; y++) {
            if (y == 0) {
                printf("|%3d", x);
                continue;
            }
            printf("|%s", terainMap[getType(x, y - 1)]);
        }
        printf("|\n");
    }

    for (int t = 0; t < height + 1; t++) {
        printf("----");
    }
    printf("-\n");
}