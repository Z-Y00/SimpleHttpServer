//https://stackoverflow.com/questions/15278343/c11-thread-safe-queue
//TODO !! reference
//https://en.cppreference.com/w/cpp/thread/condition_variable
#ifndef MYQUEUE
#define MYQUEUE

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>  
#include <iostream>

// thread safe queue
template <class T>
class MyQueue
{
private:
	std::queue<T> queue;
	mutable std::mutex mutex;
	std::condition_variable condition_variable;
public:
	MyQueue(void){}
  ~MyQueue(void){}

  // enqueue element to the queue.
  void enqueue(T t)
  {
    //std::lock_guard<std::mutex> lock(m);
	//https://en.cppreference.com/w/cpp/thread/lock_guard
	  mutex.lock();
    queue.push(t);
    condition_variable.notify_one();
	mutex.unlock();
  }
  
  // If empty, wait till avaiable.
  T dequeue(void)
  {
    std::unique_lock<std::mutex> lock(mutex);
	while (queue.empty())
	{
		//wait for the condition_variable
		condition_variable.wait(lock);
	}
	//https://stackoverflow.com/questions/25035691/why-doesnt-stdqueuepop-return-value
	//One might wonder why pop() returns void, instead of value_type. 
	//That is, why must one use front() and pop() to examine and remove the element at the front of the queue, 
	//instead of combining the two in a single member function? In fact, there is a good reason for this design. If pop() returned the front element, it would have to return by value rather than by reference: return by reference would create a dangling pointer. Return by value, however, is inefficient: it involves at least one redundant copy constructor call. Since it is impossible for pop() to return a value in such a way as to be both efficient and correct, it is more sensible for it to return no value at all and to require clients to use front() to inspect the value at the front of the queue. 
    T val = queue.front();
    queue.pop();
    return val;
  }
};
#endif