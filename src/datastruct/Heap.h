#ifndef __HEAP_H__
#define __HEAP_H__

/* 堆算法中的比较函数
Paremeter:
    @a: child
    @b: father
Return:
    @0: child不用移动
    @1: child上移 */
typedef int (*HeapCmpHook)(void* a, void* b);

/* 堆算法中的打印函数 */
typedef void (*HeapPrtHook)(void* item);

typedef struct {
    void* array;
    unsigned int num;   /* 堆元素容量 */
    unsigned int size;  /* 堆元素大小 */
    unsigned int cnt;   /* 当前堆元素个数 */
    HeapCmpHook cmp;    /* 比较钩子函数 */
    HeapPrtHook prt;    /* 打印钩子函数 */
} Heap;

/* 使用堆数据结构前调用该接口进行初始化 
Parameter:
    @heap: IN
    @size: IN the size of single item
    @num: IN the num of items
    @cmp: IN the compare func
    @prt: IN the print func
Return: NA */
void HeapInit(Heap* heap, unsigned int size, unsigned int num, void* cmp, void* prt);

/* 使用堆数据结构后调用该接口进行去初始化 
Parameter:
    @heap: IN
Return: NA */
void HeapDeinit(Heap* heap);

/* 判断堆是否满
Parameter:
    @heap: IN
Return:
    @0: not full
    @1: full */
int HeapIsFull(Heap* heap);

/* 判断堆是否空
Parameter:
    @heap: IN
Return:
    @0: not empty
    @1: empty */
int HeapIsEmpty(Heap* heap);

/* 插入堆元素操作
Parameter:
    @heap: IN
    @item: IN the pointer of item
    @size: IN the size of item
Return:
    @0: fail
    @1: success */
int HeapInsert(Heap* heap, void* item, unsigned int size);

/* 弹出堆元素操作
Parameter:
    @heap: IN
    @item: OUT the pointer of item
    @size: OUT the size of item
Return:
    @0: fail
    @1: success */
int HeapPop(Heap* heap, void* item, unsigned int size);

/* 根据索引获取堆元素
Parameter:
    @heap: IN
    @idx: IN the index of item
Return:
    @void*: the pointer of item in heap */
void* HeapGetItem(Heap* heap, unsigned idx);

/* 刷新当前堆元素在堆中位置，修改过堆中元素后调用
Parameter:
    @heap: IN
    @idx: IN the index of item
Return: NA */
void HeapItemRefresh(Heap* heap, int idx);

/* 打印堆结构
Parameter:
    @heap: IN
Return: NA */
void HeapPrint(Heap* heap);

#endif