#include"SocketClient.h"
int main() 
{
	SocketClient *socket = new SocketClient();
	socket->init();
	socket->send();

	return 0;
}