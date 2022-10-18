#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

typedef struct {
    void* (*func)(void* arg);
    void* arg;
} Task;

typedef struct {
    pthread_mutex_t lock;
    pthread_cond_t notify;
    pthread_t* threads;
    Task* tasks;
    int threadNum;
    int queueSize;
    int head;
    int tail;
    int count;
    int shutdown;
    int started;
} ThreadPool;

#define MAX_THREAD 32
#define MAX_QUEUE_SIZE 256

void* ThreadPoolFunction(void* arg)
{
    ThreadPool* pool = (ThreadPool*)arg;
    Task task;
    for (;;) {
        pthread_mutex_lock(&pool->lock);

        while (pool->count == 0 && pool->shutdown == 0) {
            pthread_cond_wait(&pool->notify, &pool->lock);
        }

        if (pool->shutdown == 1) {
            break;
        }

        task.func = pool->tasks[pool->head].func;
        task.arg = pool->tasks[pool->head].arg;
        pool->head = (pool->head + 1) % pool->queueSize;
        pool->count--;

        pthread_mutex_unlock(&pool->lock);

        task.func(task.arg);
    }

    pool->started--;
    pthread_mutex_unlock(&pool->lock);
    pthread_exit(NULL);
    return NULL;
}

int ThreadPoolDestroy(ThreadPool* pool)
{
    if (pool == NULL) {
        return 0;
    }
    if (pthread_mutex_lock(&pool->lock) != 0) {
        return 1;
    }
    int err = 0;
    do {
        if (pool->shutdown) {
            err = 1;
            break;
        }
        pool->shutdown = 1;
        if (pthread_cond_broadcast(&pool->notify) != 0 ||
            pthread_mutex_unlock(&pool->lock) != 0) {
            err = 1;
            break;
        }
        for (int i = 0; i < pool->threadNum; i++) {
            if (pthread_join(pool->threads[i], NULL) != 0) {
                err = 1;
            }
        }
    } while (0);
    if (err == 0) {
        if (pool && pool->threads) {
            free(pool->threads);
            free(pool->tasks);
            pthread_mutex_lock(&pool->lock);
            pthread_mutex_destroy(&pool->lock);
            pthread_cond_destroy(&pool->notify);
        }
    }
    return err;
}

void* ThreadPoolCreate(int threadNum, int queueSize)
{
    if (threadNum <=0 || threadNum > MAX_THREAD || queueSize <=0 || queueSize > MAX_QUEUE_SIZE) {
        return NULL;
    }
    ThreadPool* pool = malloc(sizeof(ThreadPool));
    assert(pool);

    if (pthread_mutex_init(&pool->lock, NULL) != 0 || pthread_cond_init(&pool->notify, NULL) != 0) {
        free(pool);
        return NULL;
    }

    pool->threads = malloc(sizeof(pthread_t) * threadNum);
    pool->tasks = malloc(sizeof(Task) * queueSize);
    assert(pool->threads && pool->tasks);
    pool->threadNum = threadNum;
    pool->queueSize = queueSize;
    pool->head = 0;
    pool->tail = 0;
    pool->count = 0;
    pool->shutdown = 0;
    pool->started = 0;

    for (int i = 0; i < threadNum; i++) {
        if (pthread_create(&(pool->threads[i]), NULL, ThreadPoolFunction, pool) != 0) {
            ThreadPoolDestroy(pool);
            return NULL;
        }
        pool->started++;
    }

    return pool;
}

int ThreadPoolAdd(ThreadPool* pool, void* (*func)(void*), void* arg)
{
    if (pool == NULL || func == NULL) {
        return 1;
    }
    if (pthread_mutex_lock(&pool->lock) != 0) {
        return 1;
    }
    int next = (pool->tail + 1) % pool->queueSize;
    int err = 0;
    do {
        if (pool->count == pool->queueSize) {
            err = 1;
            break;
        }
        if (pool->shutdown == 1) {
            err = 1;
            break;
        }
        pool->tasks[pool->tail].func = func;
        pool->tasks[pool->tail].arg = arg;
        pool->tail = next;
        pool->count += 1;
        if (pthread_cond_signal(&pool->notify) != 0) {
            err = 1;
            break;
        }
    } while(0);
    if (pthread_mutex_unlock(&pool->lock) != 0) {
        err = 1;
    }
    return err;
}

#endif