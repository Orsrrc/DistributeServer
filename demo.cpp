
#include <cstring>
#include <iostream>
#include <sstream>

int main(void)
{
    std::string str = "ID:123123\nServerName:12312312312\nIPAddress:2131132313\n";

    std::istringstream ss(str);
    std::string ID;
    std::string ServerName;
    std::string IPAddress;


    std::getline(ss,ID,'\n');

    std::getline(ss,ServerName, '\n' );

    std::getline(ss, IPAddress, '\n');

    if (ID.compare(0, 3, "ID:") == 0) 
    {
        ID = ID.substr(3);
    }
    if (ServerName.compare(0, 11, "ServerName:") == 0) 
    {
        ServerName = ServerName.substr(11);
    }
    if (IPAddress.compare(0, 10, "IPAddress:") == 0) 
    {
       IPAddress = IPAddress.substr(10);
    }

    std::cout << "ID: " << ID << std::endl;
    std::cout << "ServerName: " << ServerName << std::endl;
    std::cout << "IPAddress: " << IPAddress << std::endl;





    return 0;
}