#include "headers.h"

Listener::Listener(unsigned short port)
{
	running = true;
	std::thread listenerThread = std::thread(&Listener::Run, this, port); // start it in a thread
	listenerThread.detach();											  //detach, thus the std::thread won't be freed
}

void Listener::Run(unsigned short port)
{
	handlerPool.start();
	socket.bind(port); // bind to a port
	socket.listen(500);

	while (running)
	{
		//info("Listener waiting");
		MySocket tmp(-1);
		//std::cout << "\nListener \n" << tmp.socketId <<" "<< socket.socketId << "\n";
		socket.accept(tmp);
		//info("Listener get one conn %d", tmp.socketId);
		handlerPool.addConn(tmp.socketId); //add it to connQueue
	}
}

void Listener::doStop()
{
	running = false;
	handlerPool.stop();
	//wait for listenerThread to stop
	Sleep(500);
	// close conn here !
	socket.close();
}

Listener::~Listener()
{
	// you must call doStop() in your code!
}
