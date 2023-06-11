// 条件变量的最初测试代码
#include <iostream>
#include <pthread.h>
#include <string>
#include <functional>
#include <unistd.h>
using namespace std;

struct ThreadData;
#define THREAD_NUM 5
typedef void (*func_t)(ThreadData*);
// #define std::function<void (ThreadData*)> func

bool quit = false;

struct ThreadData
{
public:
    ThreadData(const string& name, pthread_mutex_t* pmtx, pthread_cond_t* pcond, func_t func)
    :name_(name), pmtx_(pmtx), pcond_(pcond), func_(func)
    {}
    string name_;
    pthread_mutex_t* pmtx_;
    pthread_cond_t* pcond_;
    func_t func_;
};

void thread1(ThreadData* td)
{
    while(!quit)
    {
        pthread_mutex_lock(td->pmtx_);
        // 这里原本是要先判断临界资源是否就绪，若不就绪则wait等待
        cout << td->name_ << " wait" << endl;
        pthread_cond_wait(td->pcond_, td->pmtx_);
        cout << td->name_ << " wait done" << endl;
        pthread_mutex_unlock(td->pmtx_);
        sleep(1);
    }
}

void thread2(ThreadData* td)
{
    while(!quit)
    {
        pthread_mutex_lock(td->pmtx_);
        // 这里原本是要先判断临界资源是否就绪，若不就绪则wait等待
        cout << td->name_ << " wait" << endl;
        pthread_cond_wait(td->pcond_, td->pmtx_);
        cout << td->name_ << " wait done" << endl;
        pthread_mutex_unlock(td->pmtx_);
        sleep(1);
    }
}

void thread3(ThreadData* td)
{
    while(!quit)
    {
        pthread_mutex_lock(td->pmtx_);
        // 这里原本是要先判断临界资源是否就绪，若不就绪则wait等待
        cout << td->name_ << " wait" << endl;
        pthread_cond_wait(td->pcond_, td->pmtx_);
        cout << td->name_ << " wait done" << endl;
        pthread_mutex_unlock(td->pmtx_);
        sleep(1);
    }
}

void thread4(ThreadData* td)
{
    while(!quit)
    {
        pthread_mutex_lock(td->pmtx_);
        // 这里原本是要先判断临界资源是否就绪，若不就绪则wait等待
        cout << td->name_ << " wait" << endl;
        pthread_cond_wait(td->pcond_, td->pmtx_);
        cout << td->name_ << " wait done" << endl;
        pthread_mutex_unlock(td->pmtx_);
        sleep(1);
    }
}

void thread5(ThreadData* td)
{
    while(!quit)
    {
        pthread_mutex_lock(td->pmtx_);
        // 这里原本是要先判断临界资源是否就绪，若不就绪则wait等待
        cout << td->name_ << " wait" << endl;
        pthread_cond_wait(td->pcond_, td->pmtx_);
        cout << td->name_ << " wait done" << endl;
        pthread_mutex_unlock(td->pmtx_);
        sleep(1);
    }
}

void* entry(void* args)
{
    ThreadData* td = (ThreadData*)args;
    td->func_(td);
    delete td;
    pthread_exit(nullptr);
}

int main()
{
    pthread_mutex_t mtx;
    pthread_cond_t cond;

    pthread_mutex_init(&mtx, nullptr);
    pthread_cond_init(&cond, nullptr);

    pthread_t tid[THREAD_NUM];
    func_t funcs[THREAD_NUM] = {thread1, thread2, thread3, thread4, thread5};
    for(int i = 0; i < THREAD_NUM; ++i)
    {
        string name = "thread";
        name += to_string(i + 1);
        ThreadData* td = new ThreadData(name, &mtx, &cond, funcs[i]);
        pthread_create(tid + i, nullptr, entry, (void*)td);
    }
    int cnt = 10;
    while(cnt != 0)
    {
        cnt--;
        sleep(2);
        pthread_cond_signal(&cond);
        // pthread_cond_broadcast(&cond);
    }
    cout << "main thread control done" << endl;
    quit = true;
    pthread_cond_broadcast(&cond);

    for(int i = 0; i < THREAD_NUM; ++i)
    {
        pthread_join(tid[i], nullptr);
        printf("main thread waits thread%d success\n", i+1);
    }

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cond);
    return 0;
}