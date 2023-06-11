#include <iostream>
#include <string>
#include <thread>
#include <signal.h>
#include <unistd.h>
// #include <pthread.h>
#include <string>
// using namespace std;


// C++线程库

// void routine()
// {
//     std::cout << "haha" << std::endl;
// }

// int main()
// {
//     std::thread t1(routine);
//     t1.join();
//     return 0;
// }


// 验证线程id的本质

// __thread int num = 6;

// void* routine(void* arg) {}

// int main()
// {
//     pthread_t tid;
//     pthread_create(&tid, nullptr, routine, nullptr);
//     int a = 10;
//     int *p = new int(10);
//     printf("栈区 : %p\n", &a);
//     printf("tid  : %p\n", tid);
//     printf("堆区 : %p\n", p);
//     // printf("num : %p\n", &num);
//     return 0;
// }



// 线程接口的使用示例程序
// #define N 10

// void* routine(void* arg)
// {
//     long long num = 0;
//     for(int i = 0; i < N; ++i)
//     {
//         if(((int*)arg)[i] % 2 == 0) num++;
//     }
//     pthread_exit((void*)num);
//     // return (void*)num;  // 偶数个数
// }

// int main()
// {
//     int* p = new int[N];
//     srand(time(nullptr));
//     for(int i = 0; i < N; ++i)
//     {
//         p[i] = rand()%100;
//     }
//     pthread_t pid = 0;
//     pthread_create(&pid, nullptr, routine, (void*)p);

//     void* retVal;
//     pthread_join(pid, &retVal);
//     cout << "共" << (long long)retVal << "个偶数" << endl;
//     return 0;
// }


// 新cancel主，主pthread_exit，不影响新的进行，但是主是defunct，同时即使新join主，主还是defunct，所以真的不建议这样啊
// void* routine(void* ptr)
// {
//     int cnt = 0;
//     pthread_join((pthread_t)ptr, nullptr);
//     while(true)
//     {
//         cnt++;
//         cout << "new thread running..." << endl;
//         sleep(1);
//         // if(cnt == 5) pthread_cancel((pthread_t)ptr);
//         if(cnt == 10) break;
//     }
//     // exit(0);
// }

// int main()
// {
//     pthread_t pid;
//     pthread_create(&pid, nullptr, routine, (void*)pthread_self());

//     int cnt = 0;
//     while(true)
//     {
//         cnt++;
//         sleep(1);
//         cout << "main thread running..." << endl;
//         if(cnt == 3) pthread_exit(nullptr);
//     }

//     // sleep(3);
//     // pthread_exit(nullptr);
//     // return 0;
// }


// 验证每个线程都有独立的信号屏蔽字。

// void showSigblock(sigset_t* curSigset);

// void *routine(void *arg)
// {
//     int cnt = 0;
//     while (true)
//     {
//         cnt++;
//         sleep(1);
//         cout << "新线程的信号屏蔽字为 : ";
//         sigset_t curSigset;
//         sigprocmask(SIG_BLOCK, nullptr, &curSigset);
//         showSigblock(&curSigset);
//         if(cnt == 5) break;
//     }
//     string *p = new string("新线程执行完毕");
//     pthread_exit(reinterpret_cast<void*>(p));
// }

// void showSigblock(sigset_t* curSigset)
// {
//     for (int i = 1; i <= 31; ++i)
//     {
//         if (sigismember(curSigset, i))
//             cout << "1";
//         else
//             cout << "0";
//     }
//     cout << endl;
// }

// int main()
// {
//     // 主线程
//     sigset_t sigset;
//     sigemptyset(&sigset);
//     sigaddset(&sigset, 8);
//     sigaddset(&sigset, 1);
//     sigaddset(&sigset, 11);
//     sigprocmask(SIG_BLOCK, &sigset, nullptr);

//     sigset_t curSigset;
//     sigprocmask(SIG_BLOCK, nullptr, &curSigset);
//     cout << "主线程此时的信号屏蔽字为 : ";
//     showSigblock(&curSigset);

//     pthread_t pid;
//     pthread_create(&pid, nullptr, routine, nullptr);

//     sleep(3);
//     sigaddset(&sigset, 3);
//     sigprocmask(SIG_BLOCK, &sigset, nullptr);
//     cout << "主线程成功屏蔽3号信号: ";
//     sigprocmask(SIG_BLOCK, nullptr, &curSigset);
//     showSigblock(&curSigset);

//     void* retThread = nullptr;
//     pthread_join(pid, &retThread);
//     cout << *(string*)retThread << endl;
//     delete (string*)retThread;
//     return 0;
// }