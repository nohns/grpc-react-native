//
//  thread-pool.cpp
//  grpc-react-native
//
//  Created on 27/10/2021.
//
//  credit: progschj (https://github.com/progschj/ThreadPool)
//  credit: mrousavy (https://github.dev/mrousavy/react-native-jsi-contacts)

#include "thread-pool.h"

// the constructor just launches some amount of workers
ThreadPool::ThreadPool(size_t threads): stop(false) {
   for(size_t i = 0;i<threads;++i)
       workers.emplace_back(
           [this]
           {
               for(;;)
               {
                   std::function<void()> task;

                   {
                       std::unique_lock<std::mutex> lock(this->queue_mutex);
                       this->condition.wait(lock,
                           [this]{ return this->stop || !this->tasks.empty(); });
                       if(this->stop && this->tasks.empty())
                           return;
                       task = std::move(this->tasks.front());
                       this->tasks.pop();
                   }

                   task();
               }
           }
       );
}

// add new work item to the pool
std::future<void> ThreadPool::enqueue(std::function<void()> func) {
  auto task = std::make_shared<std::packaged_task<void()>>(std::bind(std::forward<std::function<void()>>(func)));
  std::future<void> res = task->get_future();
  
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    
    // don't allow enqueueing after stopping the pool
    if (stop)
      throw std::runtime_error("enqueue on stopped ThreadPool");
    
    tasks.emplace([task](){ (*task)(); });
  }
  
  condition.notify_one();
  return res;
}

// the destructor joins all threads
ThreadPool::~ThreadPool()
{
   {
       std::unique_lock<std::mutex> lock(queue_mutex);
       stop = true;
   }
   condition.notify_all();
   for(std::thread &worker: workers)
       worker.join();
}

