//reference
//#include "stdafx.h"
#include "headers.h"
#include "debug.h"
#include "socket.h"

#include <string>
using std::string;

MySocket::MySocket()
{
	WORD version;
	WSADATA data;
	version = MAKEWORD(2, 0);
	int err = WSAStartup(version, &data);
	// debug test
	check(err == 0);
	socketId = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	check(socketId > 0);
}

MySocket::MySocket(int Id)
{
	socketId = Id;
}
MySocket::~MySocket()
{
	//WSACleanup();
	//you must destroy socket maually
	//info( "delete socket");
}

void MySocket::bind(unsigned short port)
{
	struct sockaddr_in addr;
	char optval = 1;
	memset(&addr, 0, sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	int err;
	err = setsockopt(socketId, SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(char));
	check(err >= 0, "setsockopt failed!");
	err = ::bind(socketId, (struct sockaddr *)&addr, sizeof(sockaddr_in));
	check(err >= 0, "bind failed!");
}

void MySocket::listen(int length)
{
	int err = ::listen(socketId, length);
	check(err >= 0, "Listen failed! ");
}

void MySocket::accept(MySocket &comming)
{
	SOCKET sk = -1;
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));
	socklen_t socklen = sizeof(addr);
	sk = ::accept(socketId, (struct sockaddr *)&addr, &socklen);
#pragma warning(disable : 4996)
	printf("[info] get a socket from %s and Port%d\n", inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
	check(sk > 0, "accept failed! ");
	comming.socketId = sk;
}

void MySocket::close()
{
	int err = closesocket(socketId);
	//check(err >= 0,"close socket failed!");
}

int MySocket::read(char *buf, int n)
{ //we only need the first a few bytes
	check(socketId >= 0);
	int left = n;
	char *bufp = buf;
	int read = 0;
	int err = 0;
	//while (left>0)
	//{
	read = ::recv(socketId, buf, left, 0);
	//if (read == 0) break;//end
	check(read > 0, "read failed! force thread to terminate!");
	if (read < 0)
		std::terminate();
	left -= read;
	bufp += read;
	//}
	bufp = '\0'; //add the end of buf
	return left; //left to read
};
int MySocket::write(const char *buf, int n)
{
	//fputs(buf, stdout);
	check(socketId >= 0);
	int left = n;
	const char *bufp = buf;
	int written = 0;
	int err = 0;
	while (left > 0)
	{
		written = send(socketId, buf, left, 0);
		if (written == 0)
			break; //end
		check(written >= 0, "written failed! force thread to terminate\n");
		if (written < 0)
			std::terminate();
		left -= written;
		bufp += written;
	}
	//info("left to written %d", left);
	return n - left; //how much we've written
};
void MySocket::socketOutFlush()
{
	//reference stackoverflow.com/.....
	string tmp = socketStringStream.str();
	const char *buf = tmp.c_str();
	int size = strlen(buf);
	write(buf, size);
	//std::cout << "[DEBUG] what we put with size of " << size<<std::endl;
	//fputs(buf, stdout);//debug
	//https://stackoverflow.com/questions/20731/how-do-you-clear-a-stringstream-variable
	socketStringStream.str(std::string());
}
