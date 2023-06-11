// 创建线程池的main源文件
#include <iostream>
#include <ctime>
#include <unistd.h>
#include "threadPool.hpp"
#include "task.hpp"
#include "log.hpp"


int main()
{
    srand((unsigned int)time(nullptr) ^ getpid());

    ThreadPool<Task> *tp = ThreadPool<Task>::getThreadPool();
    // ThreadPool<Task> tp1 = *tp;
    // tp1 = *tp;
    tp->run();
    
    // 创建线程池，往线程池内push任务，供给线程池内的线程执行。
    while(true)
    {
        int x = rand() % 10 + 1;
        usleep(3333);
        int y = rand() % 10 + 1;
        Task t(x, y, [](int x, int y)->int {
            return x + y;
        });
        tp->pushTask(t);
        logMessage(NORMAL, "主线程生产完成: %d+%d=?", x, y);
        sleep(1);
    }
    return 0;
}