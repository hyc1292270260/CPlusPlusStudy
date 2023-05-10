#pragma once
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")

class SocketServer
{
public:
    void init();
    void send();
private:
    void cleanUp(SOCKET& socket);
};


