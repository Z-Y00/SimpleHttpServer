#include "headers.h"

static const char PAGE_404[] = "HTTP/1.1 404 Not Found\r\nContent-Type: \
text/html\r\nContent-Length: 38\r\n\r\n<HTML>\r\n<BODY>\r\n  404\
\r\n</BODY>\r\n</HTML>\r\n\0";

using namespace std;
extern string fileBase;

HandlerPool::HandlerPool()
{
}

void HandlerPool::start()
{
	running = true;

	info("HandlerPool init");
	for (int i = 0; i < num_threads; ++i) //start as much thread as needed
	{
		t[i] = std::thread(&HandlerPool::run, this, i);
	}
	info("HandlerPool start done ");
}

void HandlerPool::run(int tid)
{
	//   the tid denote which of the the pendingConn[] to do
	// core loop here

	while (running)
	{
		int toResponse = pendingConns.dequeue();
		//std::cout << "dequeue a new socket "<<toResponse.socketId<<"\n";
		std::thread handlerThread = std::thread(&HandlerPool::process, this, toResponse); // start a new thread to process it
		std::cout << "create a new thread " <<  "\n";
		handlerThread.detach();
	}
	//once exit, close it's conn
}

void HandlerPool::addConn(int commingConn)
{
	pendingConns.enqueue(commingConn);
}

void HandlerPool::stop()
{
	running = false; // it should be a little more than this, especially about the queue!
}

void HandlerPool::process(int id)
{
	//info(" process a new socket ");
	//revive the socket
	MySocket comming(id);

	while (running)
	{
		//read the buf
		char buf[MAXLINE + 1]; //defined in header.hpp
		comming.read(buf, MAXLINE);

		//regex process
		//fputs(buf, stdout);
		//std::cout << "\n then the regex get!\n";       //print out
		std::smatch sm;
		std::regex regex("([A-Za-z]+) +(.*) +(HTTP/[0-9][.][0-9])");
		std::string text(buf);
		int match = std::regex_search(text, sm, regex);
		//std::cout << match;
		if (match == 0)
		{
			//info("no header found, read again");
			break; // force the conn to close!!!
		}
		//else {
		//info("\nthe matches were: \n");
		//for (unsigned i = 0; i < sm.size(); ++i) {
		//std::cout << sm[i] << "\n ";
		//}
		//}

		string operation1 = sm[1]; // GET
		string operation2 = sm[2]; // /index.html
		std::cout << "[info] operation: " << operation1 << " " << operation2 << std::endl;

		string contentType;
		std::smatch sm2;
		std::regex regex2("\\..*");
		int match2 = std::regex_search(operation2, sm2, regex2);
		//std::cout << match;
		if (match2 == 0)
		{
			info("no file extension found, use default!");
			contentType = "text/plain"; // if it does't match
		}
		else
		{
			//std::cout<<sm2[0]<<std::endl;

			if (sm2[0] == ".html")
			{
				contentType = "text/html";
			}
			else if (sm2[0] == ".xml")
			{
				contentType = "text/xml";
			}
			else if (sm2[0] == ".css")
			{
				contentType = "text/css";
			}
			else if (sm2[0] == ".png")
			{
				contentType = "image/png";
			}
			else if (sm2[0] == ".gif")
			{
				contentType = "image/gif";
			}
			else if (sm2[0] == ".jpg")
			{
				contentType = "image/jpg";
			}
			else if (sm2[0] == ".jpeg")
			{
				contentType = "image/jpeg";
			}
			else if (sm2[0] == ".ico")
			{ //TODO this is wrong!
				contentType = "image/ico";
			}
			else
			{
				contentType = "text/plain"; //TODO default not match!
			}
		}

		//std::cout <<"[debug] file at:"<< fileBase+operation2<<std::endl;
		std::ifstream t(fileBase + operation2, std::ios::binary);
		if (!t) //404 response!
		{
			comming.socketStringStream << PAGE_404;
			comming.socketOutFlush();
			info("file not found!");
			break; // force the conn to close!!!
		}
		//reference
		//http://www.cplusplus.com/reference/fstream/ifstream/rdbuf/
		std::filebuf *tmp = t.rdbuf();
		int size = tmp->pubseekoff(0, t.end, t.in);
		tmp->pubseekpos(0, t.in);
		// new a buf to keep the dataS
		char *buffer = new char[size];
		// get data
		tmp->sgetn(buffer, size);
		t.close(); //close the file, but we've got the data!

		comming.socketStringStream << "HTTP/1.1 200 OK"
								   << "\r\n"
								   << "Server: Y00\r\n"
								   << "Content-Length: " << size << "\r\n"
								   << "Connection: close\r\n"
								   << "Content-Type: " << contentType << "\r\n\r\n";
		comming.socketOutFlush();

		comming.write(buffer, size);
		delete buffer; //clean up!
	}
	comming.close(); //close the conn!
};

HandlerPool::~HandlerPool()
{
	running = false;
	//info("HandlerPool stoped!");
}
