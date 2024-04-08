#include "IDserver.h"

int main()
{
	IDServer idServer;
	std::cout << "ID SERVER:" << idServer.getID() << std::endl;
	Network recv;

	recv.receiver(PROTOCOL_UDP); // receiver to recvBuffer

	/*
		ID:             \n
		ServerName:     \n
		IPAddress:      \n
	*/
	std::string str = recv.getReceiveMessage();

	char ID[10];
	char ServerName[20];
	char IPAddress[37];
	char temp[128];
	for (int i = 0; str[i] != NULL; i++)
	{
		int k = 0;
		for (int j = i; str[j] != '\n'; j++, k++)
		{
			temp[k] = str[j];
		}
		if (strncmp(temp, "ID", 2) == 0)
		{
			strncpy(ID, temp, 3);
		}

		else if (strncmp(temp, "ServerName", 10) == 0)
		{
			strncpy(ServerName, temp, 11);
		}
		else if (strncmp(temp, "IPAddress", 9) == 0)
		{
			strncpy(IPAddress, temp, 10);
		}
	}
}