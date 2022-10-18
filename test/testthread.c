#include <stdio.h>
#include <Threadpool.h>
#include <unistd.h>
int var = 1000;
void* ThreadFunc(void* arg)
{
    pthread_t tid = pthread_self();
    uint64_t t;
    pthread_threadid_np(tid, &t);
    printf("threadfunc tid=%llu\n", t);
    for (int i = 0; i < 10000; i++) {
        var++;
    }
    return NULL;
}

int main()
{
    ThreadPool* pool = ThreadPoolCreate(20, 200);
    for (int i = 0; i < 10; i++) {
        ThreadPoolAdd(pool, ThreadFunc, NULL);
    }
    pthread_t tid = pthread_self();
    uint64_t tidd, tidy;
    pthread_threadid_np(NULL, &tidd);
    pthread_threadid_np(tid, &tidy);
    printf("main tidd=%llu tidy=%llu\n", tidd, tidy);
    ThreadPoolDestroy(pool);
    printf("var = %d\n", var);
    return 0;
}