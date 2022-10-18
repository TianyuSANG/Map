if (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    set(CMAKE_C_COMPILER "C:/Program Files/mingw64/bin/gcc.exe")
    set(CMAKE_CXX_COMPILER "C:/Program Files/mingw64/bin/g++.exe")
else()
    set(CMAKE_C_COMPILER "/usr/bin/gcc")
endif()

# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

# 项目信息
project("Map")

# include路径
include_directories(${PROJECT_SOURCE_DIR}/src/algorithm)
include_directories(${PROJECT_SOURCE_DIR}/src/base)
include_directories(${PROJECT_SOURCE_DIR}/src/datastruct)

# 设置可执行文件生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 生成debug版本
SET(CMAKE_BUILD_TYPE "debug")
if (CMAKE_BUILD_TYPE STREQUAL debug)
    add_definitions(-D_DEBUG)
endif ()
SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -O0 -Wall -g -ggdb -std=c11")
SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O3 -Wall -std=c11")
# link_directories(${PROJECT_SOURCE_DIR}/lib)

# link_libraries(cjson)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory("./src/algorithm" DIR_SRCS)
aux_source_directory("./src/base" DIR_SRCS)
aux_source_directory("./src/datastruct" DIR_SRCS)

# 指定生成目标
add_executable(TestHeap ${DIR_SRCS} test/testheap.c)
add_executable(TestAStar ${DIR_SRCS} test/testastar.c)
add_executable(TestPrint ${DIR_SRCS} test/testprint.c)
add_executable(TestLog ${DIR_SRCS} test/testlog.c)
add_executable(TestQueue ${DIR_SRCS} test/testqueue.c)
add_executable(TestBfs ${DIR_SRCS} test/testbfs.c)
# add_executable(TestThread test/testthread.c)

MESSAGE(STATUS "sources = ${DIR_SRCS}.")