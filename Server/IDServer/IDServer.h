
#include <string>
#include <openssl/rand.h>
#include <mysql/mysql.h>
#include "../Common.hpp"
#include "../Network.hpp"



class IDServer
{
public:
    IDServer()
        : ID(SHA256(generateRandomString()))
    {
        
    }
    ~IDServer();

    std::string generateServerID() // generate Server's ID length == 10
    {
        return generateRandomDigit(10);
    }

    std::string getID()
    {
        return ID;
    }
    
    int connectToMysql(MYSQL* conn, const char* host, const char* user, const char* password, const char* database);
    int insertServerInfo(MYSQL *conn, const char* ID, const char* ServerName, const char* IPAddress);


private:
    std::string ID;
};
