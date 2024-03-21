#ifndef __TRANSACTION__HPP_
#define __TRANSACTION__HPP_



#include "Common.hpp"
#include "Network.hpp"



///////////////////////////////////////////////////////////////////////////////////////
/*
Sender Address: <Sender's Public Key>
Recipient Address: <Recipient's Public Key>
Amount: <Amount of Cryptocurrency>
Transaction Fee: <Fee amount>
Timestamp: <Timestamp of the transaction>
Transaction ID: <Transaction Hash>
Signature: <Digital Signature>
Metadata: <Optional additional information>
*/
///////////////////////////////////////////////////////////////////////////////////////


class transaction
{
    public:
    transaction(IPAddress* senderAddress,IPAddress* recipientAddress, double fee,  std::string signature, std::string metaData)
    :ID(SHA256(generateRandomString(( rand() + 100) % 10))),
    TimeStamp(get_current_time()),
    SenderAddress(senderAddress),
    RecipientAddress(recipientAddress),
    fee(fee),
    signature(signature),
    MetaData(metaData)
    {
        ;
    }


    ~transaction();
    private:
    std::string ID;
    std::string TimeStamp;
    IPAddress* SenderAddress;
    IPAddress* RecipientAddress;
    double fee;
    std::string signature;
    std::string MetaData;
};

transaction::transaction(IPAddress* senderAddress,IPAddress* recipientAddress, double fee,  std::string signature, std::string metaData)
{
    ;
}

 
transaction::~transaction()
{
    ;
} 

#endif //__TRANSACTION__HPP_