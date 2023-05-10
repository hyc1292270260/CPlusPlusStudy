#include"SocketServer.h"
int main()
{
	SocketServer* socket = new SocketServer();
	socket->init();
	socket->send();

	return 0;
}