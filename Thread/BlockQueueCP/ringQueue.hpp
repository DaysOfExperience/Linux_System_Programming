#ifndef _RINGQUEUE_HPP_
#define _RINGQUEUE_HPP_

#include <vector>
#include "sem.hpp"
#include "mutex.hpp"

const int g_default_size = 5;

template <class T>
class RingQueue
{
public:
    RingQueue(int size = g_default_size)
        : ring_queue_(size), 
        size_(size), 
        space_sem_(size), data_sem_(0), 
        p_index_(0), c_index_(0), 
        p_mutex_(), c_mutex_()
    {}
    ~RingQueue() = default;
    void push(const T &in)
    {
        // 生产者: 环形队列的push的操作
        space_sem_.p(); // 空间资源的p操作

        p_mutex_.lock();
        ring_queue_[p_index_++] = in;
        p_index_ %= size_;
        p_mutex_.unlock();

        data_sem_.v(); // 数据资源v操作
    }
    void pop(T *out)
    {
        data_sem_.p(); // 数据资源的p操作，消费者进行。若没有数据资源，则阻塞挂起消费者线程

        c_mutex_.lock();
        *out = ring_queue_[c_index_++];
        c_index_ %= size_;
        c_mutex_.unlock();

        space_sem_.v(); // 空间资源v操作
    }

private:
    std::vector<T> ring_queue_; // 使用vector模拟环形队列
    int size_;                  // 环形队列的大小
    int p_index_;   // 生产者下标
    int c_index_;   // 消费者下标
    Sem space_sem_; // 空间资源信号量，生产者使用
    Sem data_sem_;  // 数据资源信号量，消费者使用
    Mutex p_mutex_;
    Mutex c_mutex_;
};


// 自己写的：环形队列利用互斥锁+条件变量进行。
// template <class T>
// class RingQueue
// {
// public:
//     RingQueue(int size = g_default_size)
//     : ring_queue_(size)
//     , size_(size)
//     , c_index_(0), p_index_(0)
//     , c_mutex_(), p_mutex_()
//     {
//         pthread_cond_init(&not_empty_, nullptr);
//         pthread_cond_init(&not_full_, nullptr);
//     }
//     ~RingQueue()
//     {
//         pthread_cond_destroy(&not_empty_);
//         pthread_cond_destroy(&not_full_);
//     }
//     void push(const T &in)
//     {
//         // 生产者
//         p_mutex_.lock();  // 加锁

//         while((p_index_ + 1) % size_ == c_index_)
//         {
//             // 满的
//             pthread_cond_wait(&not_full_, &p_mutex_.mtx_);
//         }
//         // 不满了
//         ring_queue_[p_index_++] = in;
//         p_index_ %= size_;
//         pthread_cond_signal(&not_empty_);

//         p_mutex_.unlock(); 
//     }
//     void pop(T *out)
//     {
//         // 消费者
//         c_mutex_.lock();

//         while(c_index_ == p_index_)  // 为空，没有数据资源，等待条件变量。
//         {
//             pthread_cond_wait(&not_empty_, &c_mutex_.mtx_);
//         }
//         *out = ring_queue_[c_index_++];
//         c_index_ %= size_;
//         pthread_cond_signal(&not_full_);

//         c_mutex_.unlock();
//     }
// private:
//     std::vector<T> ring_queue_;  // 环形队列
//     int size_;
//     int c_index_;
//     int p_index_;
//     Mutex c_mutex_;
//     Mutex p_mutex_;
//     pthread_cond_t not_empty_;
//     pthread_cond_t not_full_;
// };

#endif