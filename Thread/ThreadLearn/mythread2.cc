#include <iostream>
#include <pthread.h>
#include <string>
#include <unistd.h>

using namespace std;

// 线程互斥 - 多线程抢票程序，加锁解锁


// 共享资源，多线程同时访问(未来的临界资源)
int tickets = 3000;
// pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

struct ThreadData
{
public:
    ThreadData(const string& tname, pthread_mutex_t* pmtx)
    : tname_(tname), pmtx_(pmtx)
    {}
    string tname_;
    pthread_mutex_t* pmtx_;
};

void* getTickets(void* args)
{
    ThreadData* td = (ThreadData*)args;
    while(true)
    {
        pthread_mutex_lock(td->pmtx_);
        if(tickets > 0)  // 未来的临界区
        {
            usleep(1000);
            printf("%s : %d\n", td->tname_.c_str(), tickets); // 未来的临界区
            // cout << *ps << " get ticket " << tickets << endl;
            tickets--; // 未来的临界区
            pthread_mutex_unlock(td->pmtx_);
        }
        else
        {
            pthread_mutex_unlock(td->pmtx_);
            break;
        }
        // usleep(1000);
    }
    delete td;
    pthread_exit(nullptr);
    // return nullptr;
}

// 多线程抢票程序
int main()
{
    pthread_t tid[3];
    pthread_mutex_t mtx;
    pthread_mutex_init(&mtx, nullptr);
    for(int i = 0; i < 3; ++i)
    {
        string s("thread");
        s += to_string(i+1);
        ThreadData* td = new ThreadData(s, &mtx);
        pthread_create(tid + i, nullptr, getTickets, (void*)td);
    }
    for(int i = 0; i < 3; ++i)
    {
        pthread_join(tid[i], nullptr);
        // printf("主线程等待回收新线程%d成功\n", i + 1);
        // cout << "主线程等待回收新线程" << i+1 << "成功" << endl;
    }
    pthread_mutex_destroy(&mtx);
    return 0;
}