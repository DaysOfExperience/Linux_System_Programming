#include "ringQueue.hpp"
#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;

// 消费者
void *consumer(void *args)
{
    RingQueue<int> *rq = (RingQueue<int> *)args; // 生产消费的缓冲区：环形队列
    while (true)
    {
        sleep(1);
        int x;
        rq->pop(&x);
        cout << "消费：" << x << " [" << pthread_self() << "]" << endl;
    }
    pthread_exit(nullptr);
}

// 生产者
void *producer(void *args)
{
    RingQueue<int> *rq = (RingQueue<int> *)args;
    while (true)
    {
        int x = rand() % 100 + 1;
        rq->push(x);
        cout << "生产：" << x << " [" << pthread_self() << "]" << endl;
    }
    pthread_exit(nullptr);
}

// int main()
// {
//     srand((unsigned int)time(nullptr));

//     // RingQueue<int>* ring_queue = new RingQueue<int>();
//     RingQueue<int> ringQueue;
//     pthread_t c[2], p[3];     // 多生产多消费，3生产2消费

//     for(int i = 0; i < 2; ++i)
//         pthread_create(c + i, nullptr, consumer, &ringQueue);
//     for(int i = 0; i < 3; ++i)
//         pthread_create(p + i, nullptr, producer, &ringQueue);

//     for(int i = 0; i < 2; ++i)
//         pthread_join(c[i], nullptr);
//     for(int i = 0; i < 3; ++i)
//         pthread_join(p[i], nullptr);
//     return 0;
// }
int main()
{
    srand((unsigned int)time(nullptr));

    RingQueue<int> ringQueue;
    pthread_t c, p;

    pthread_create(&c, nullptr, consumer, &ringQueue);

    pthread_create(&p, nullptr, producer, &ringQueue);

    pthread_join(c, nullptr);

    pthread_join(p, nullptr);
    return 0;
}

// 二元信号量充当互斥锁

// int tickets = 10000;
// pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

// void *getTickets(void *args)
// {
//     Sem *sem = (Sem *)args;
//     while (true)
//     {
//         sem->p(); // 申请信号量，原子的，只有一个线程会申请成功
//         // pthread_mutex_lock(&mtx);
//         if (tickets > 0)
//         {
//             usleep(1000); // 1ms，模拟抢票过程
//             cout << "tickets : " << tickets << " [" << pthread_self() << "]" << endl;
//             tickets--;
//             sem->v();
//             // pthread_mutex_unlock(&mtx);
//         }
//         else
//         {
//             sem->v();
//             // pthread_mutex_unlock(&mtx);
//             break;
//         }
//     }
//     pthread_exit(nullptr);
// }

// int main()
// {
//     pthread_t tids[4];
//     Sem sem(1);
//     for (int i = 0; i < 4; ++i)
//     {
//         pthread_create(tids + i, nullptr, getTickets, &sem);
//     }

//     for (int i = 0; i < 4; ++i)
//     {
//         pthread_join(tids[i], nullptr);
//     }
//     return 0;
// }