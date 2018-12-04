#include "headers.h"
string fileBase;
unsigned short port;
int main(int argc, char const *argv[])
{
    //read config from argv
	//debug("argc %d", argc);
	if (argc==3)
	{
		fileBase = argv[1];
		const char * tmp = fileBase.c_str();
		port = atoi(argv[2]);//get a port from argv
		info("fileBase:%s\n[INFO] port:%d", tmp, port);
	}
	else
	{
		port = 8181;
		//read from input
		fileBase = "E:/document/computer/www/z-y00.github.io/";
		//cin >> fileBase;
	}

    //start listener thread
    Listener localListener(port);

	//wait for input to close
	getchar();
	localListener.doStop();
	info("server stopped!");
    return 0;
}
