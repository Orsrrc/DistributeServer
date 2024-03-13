
#include <string>
#include <openssl/rand.h>
#include "../Common.h"

class IDServer
{
    IDServer(std::string id)
        :ID(id)
    {
        ;
    }

    ~IDServer();
    int generateIDinfo();

    private:
        std::string ID;
};