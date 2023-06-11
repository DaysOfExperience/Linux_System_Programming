#ifndef _MUTEX_HPP_
#define _MUTEX_HPP_
#include <pthread.h>

class Mutex
{
public:
    Mutex()
    {
        pthread_mutex_init(&mtx_, nullptr);
    }
    ~Mutex()
    {
        pthread_mutex_destroy(&mtx_);
    }
    void lock()
    {
        pthread_mutex_lock(&mtx_);
    }
    void unlock()
    {
        pthread_mutex_unlock(&mtx_);
    }
public:
    pthread_mutex_t mtx_;
};

#endif