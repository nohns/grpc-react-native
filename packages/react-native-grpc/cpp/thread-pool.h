//
//  thread-pool.h
//  grpc-react-native
//
//  Created on 27/10/2021.
//
//  credit: progschj (https://github.com/progschj/ThreadPool)
//  credit: mrousavy (https://github.dev/mrousavy/react-native-jsi-contacts)

#ifndef thread_pool_h
#define thread_pool_h

#include <vector>
#include <queue>
#include <future>

class ThreadPool {
public:
    ThreadPool(size_t);
    std::future<void> enqueue(std::function<void()> task);
    ~ThreadPool();
private:
    // need to keep track of threads so we can join them
    std::vector<std::thread> workers;
    // the task queue
    std::queue<std::function<void()>> tasks;
    
    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};
 
#endif /* thread_pool_h */
