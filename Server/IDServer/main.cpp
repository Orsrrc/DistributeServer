#include "IDserver.h"


int main()
{
	Network server;
	//server.initSocket(PROTOCOL_UDP);
	server.initSocket(PROTOCOL_TCP);
	//server.receiverMessage(PROTOCOL_UDP);
	server.receiver(PROTOCOL_TCP);
	return OK;
}