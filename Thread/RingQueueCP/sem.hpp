#ifndef _SEM_HPP_
#define _SEM_HPP_

#include <semaphore.h>

// 信号量的封装
class Sem
{
public:
    Sem(int value)
    {
        sem_init(&sem_, 0, value);
    }
    ~Sem()
    {
        sem_destroy(&sem_); 
    }
    void p()
    {
        sem_wait(&sem_);
    }
    void v()
    {
        sem_post(&sem_);
    }
private:
    sem_t sem_;
};

#endif