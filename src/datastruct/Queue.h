#ifndef __QUEUE_H__
#define __QUEUE_H__

/* 队列打印队元素钩子函数 */
typedef void (*QueuePrtHook)(void* item);

typedef struct {
    void* array;        /* 存储队列所有元素 */
    int size;           /* 队列元素 大小 */
    int num;            /* 队列元素 最大个数 */
    int begin;          /* 队头索引 */
    int end;            /* 队尾索引 */
    QueuePrtHook prt;
} Queue;

/* 队列结构使用前初始化
Parameter:
    @queue: IN
    @size: IN the size of item
    @num: IN the num of item
    @prt: IN the func to print item
Return: NA */
void QueueInit(Queue* queue, int size, int num, QueuePrtHook prt);

/* 队列结构使用后去初始化
Parameter:
    @queue: IN
Return: NA */
void QueueDeinit(Queue* queue);

/* 判断队列是否空
Parameter:
    @queue: IN
Return:
    @0: not empty
    @1: empty */
int QueueIsEmpty(Queue* queue);

/* 判断队列是否满
Parameter:
    @queue: IN
Return:
    @0: not full
    @1: full */
int QueueIsFull(Queue* queue);

/* 入队操作
Parameter:
    @queue: IN
    @item: IN the pointer to item
    @size: IN the size of item
Return:
    @0: fail
    @1: success */
int QueueInsert(Queue* queue, void* item, int size);

/* 出队操作
Parameter:
    @queue: IN
    @item: OUT the pointer to item
    @size: IN the size of item
Return:
    @0: fail
    @1: success */
int QueuePop(Queue* queue, void* item, int size);

/* 打印队列
Parameter:
    @queue: IN
Return: NA */
void QueuePrint(Queue* queue);

#endif