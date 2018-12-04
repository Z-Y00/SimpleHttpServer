#pragma once
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
using std::string;
class MySocket
{
	public:
    int port;
    int socketId;
	std::stringstream socketStringStream;
  
    MySocket(/* args */);
	MySocket(int );
	//MySocket(const MySocket &);
    ~MySocket();
    void bind(unsigned short );
    void listen(int );
    void accept(MySocket& );
    void close();

    //buf IO
    int read(char *, int n);
    int write(const char *, int n);

	//stream IO
	void socketOutFlush();
};
