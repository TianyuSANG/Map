#include <stdio.h>

#include "Log.h"

int main()
{
    LOGC(LOG_LEVEL_INFO, "Hello World!");
    LOGC(LOG_LEVEL_ERROR, "Hello World!");
    return 0;
}