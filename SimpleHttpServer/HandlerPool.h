#pragma once
using namespace std;

class HandlerPool
{
  private:
	  MyQueue <int> pendingConns;
    
    volatile boolean running;
	static const int num_threads = 1;// DO NOT change this!
	std::thread t[num_threads];
	//Handler    handlers[num_threads];
  public:
    HandlerPool();
    void start();
    void run(int tid);
    void addConn(int commingConn);
    void stop();
	void process(int );
    ~HandlerPool();
};
