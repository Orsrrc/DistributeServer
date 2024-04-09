#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <ctime>
#include <openssl/sha.h>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
//
// define log number
//
#define OK 0
#define ERROR -1
#define STABLISH 0
#define SERVER_PORT 9800
#define PROTOCOL_TCP 0
#define PROTOCOL_UDP 1

////////////////////////////////GLOBAL////////////////////////////////////////////////////////////////////////////

int shardNum = 0;
int SourceNum = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////GLOBAL FUNCTION///////////////////////////////////////////////////////////////

std::string get_current_time()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::string time = std::ctime(&now_time);
    return time;
}

std::string generateRandomString(int length = ((rand() + 100) % 10))
{
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+{}[]|;:,.<>?";
    const int charsetLength = charset.length();
    std::string result;
    srand(time(0)); // Seed the random number generator
    for (int i = 0; i < length; ++i)
    {
        result += charset[rand() % charsetLength];
    }

    return result;
}

std::string generateRandomDigit(int length = ((rand() + 100) % 10))
{
    const std::string charset = "0123456789";
    const int charsetLength = charset.length();
    std::string result;
    srand(time(0)); // Seed the random number generator
    for (int i = 0; i < length; ++i)
    {
        result += charset[rand() % charsetLength];
    }
}

// how to compel :g++ -o main main.cpp -lssl -lcrypto
std::string SHA256(const std::string &input)
{
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size());
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////define the data struct/////////////////////////////////////////////////////////////////////

//
// the struct of block node
//

struct IDinfo
{
    std::string ID;
};

//
// the struct of queues
//
struct block_queue
{
};

//
// the struct of block resouce
//
struct block_resouce
{
};

//
// the struct of timeslots
//
struct block_time
{
};

//
// the struct of Block
//
struct Block
{
};

struct shard
{
    std::map<std::string, double> resouceAllocateInfo;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////// SYMBOLS AND NOTIFIACTION ////////////////////////////////////////////////////////////////////

void init_queue();                                                        // initliation queue
void inject_actual_queues_set();                                          // inject the vector of actual queues
void inject_virtual_queues_set();                                         // inject the vector of virtual queues
void get_resource_allocated(const block_time &t, const Block &ID);        // the IDth vector of resouces allocated for shard at t
void get_resource_allocated(const block_time &t, const block_resouce &k); // the kth resouce allocated to shard
void get_budget(const block_resouce &k);                                  // the budget of the kth resouce
void get_queue_length(const block_time &t, const block_queue &i);         // the queue length of shard
void get_arrival_transaction(const block_time &t, const block_queue &i);  // the arrival transactions of queue
void get_dequeued_transaction(const block_time &t, const block_queue &i); // the dequeued transaction of queue
void set_reward();                                                        // the reward to easure each unit of dequeued data
void set_penalty_weight(const std::string &id, const double &weight);     // set the weight of penalty 0 -> perfer queue stability  >0 consider queue stability and resource consume
void set_consensus_difficulty();                                          // set the parameter reverse to the consensus difficulty
void Lyapunov();                                                          // the Lyapunov function of Q(t)
void lyapunov_drift();                                                    // the Lyapunov drift
void get_increment(const block_resouce &k, const block_time &t);          // the increment arrived in virtual queue k at timeslot t
void concatenated_actual_and_virtual();                                   // the concatenated vector




void init_queue();                                                        // initliation queue
void inject_actual_queues_set();                                          // inject the vector of actual queues
void inject_virtual_queues_set();                                         // inject the vector of virtual queues
void get_resource_allocated(const block_time& t, const Block& ID);        // the IDth vector of resouces allocated for shard at t
void get_resource_allocated(const block_time& t, const block_resouce& k); // the kth resouce allocated to shard
double get_budget(const int resourceType);                                  // the budget of the kth resouce
void get_queue_length(const block_time& t, const block_queue& i);         // the queue length of shard
void get_arrival_transaction(const block_time& t, const block_queue& i);  // the arrival transactions of queue
void get_dequeued_transaction(const block_time& t, const block_queue& i); // the dequeued transaction of queue
void set_reward();                                                        // the reward to easure each unit of dequeued data
void set_penalty_weight(const std::string& id, const double& weight);     // set the weight of penalty 0 -> perfer queue stability  >0 consider queue stability and resource consume
void set_consensus_difficulty();                                          // set the parameter reverse to the consensus difficulty
void Lyapunov();                                                          // the Lyapunov function of Q(t)
void lyapunov_drift();                                                    // the Lyapunov drift
void get_increment(const block_resouce& k, const block_time& t);          // the increment arrived in virtual queue k at timeslot t
double get_increment(int resoureceType);
void concatenated_actual_and_virtual();                                   // the concatenated vector
double get_the_weight_of_the_resource(double resourceType);

double get_the_length_of_the_actual_shard(int shardIndex);


double get_the_kth_resource_allocated_to_shard(const double& index,const double& resourceType)
{
    return OK;
}

double get_the_data_amount_processed(double resourceWeight)
{
    return OK;
}





void alter_the_kth_resource_allocated_to_shard(int resourceType, int shardIndex, double allocate);

void alter_the_shard_i_dequeued_transaction(int shardIndex, double transaction);

double get_the_shard_ith_dequeue_transaction(int shardIndex);


int compareToResourceBudget(std::map<int, double> resourceAllocate)
{
    for (auto iterator = resourceAllocate.begin();iterator != resourceAllocate.end(); iterator++)
    {
        if(iterator->second > get_budget(iterator->first))
        {
            perror("超出资源最大分配数量!");  
            std::cout << "info" << iterator->first << iterator->second << std::endl;
            return ERROR;
        }
    }
}

int compareToIterval(std::vector<int> shardSet, double BlockSize, double BlockInterval, double SlotsInterval)
{
    for(int i = 0; shardSet[i] != NULL; i++)
    {
        if(get_the_shard_ith_dequeue_transaction(shardSet[i]) < (BlockSize*BlockInterval/SlotsInterval) )
        {
            perror("不满足区块间隔");
            std::cout << "info:" << shardSet[i] << " " << get_the_shard_ith_dequeue_transaction(shardSet[i]) << " " << BlockSize*BlockInterval/SlotsInterval << std::endl;
            return ERROR;
        }
    }
}


double get_kth_resource_gamma_value(int resourceIndex);

int alter_kth_resource_gamma_value(int resouceIndex, double gammaValue);


double get_ith_shard_lamba_value(int shardIndex);

int alter_ith_shard_lamba_value(int shardIndex);






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////// CONTINER /////////////////////////////////////////////////////////////////////////
extern std::vector<block_queue> queues_set;         // the set of queues
extern std::vector<block_queue> actual_queues_set;  // vector of actual queues
extern std::vector<block_queue> virtual_queues_set; // vector of virtual queues
extern std::vector<block_time> timeslots_set;       // the set of all timeslots
extern std::vector<block_resouce> resouce_set;      // the # of all types of resouces
extern std::map<int, double> resourceWeightList;
extern std::map<int, std::string> resourceNameList;
extern std::map<int, shard *> shardAddress;
extern std::map<int, long double> dequeuedQueues;
extern std::map<int, long double> arrivalQueues;



extern std::map<int, double> shardSet;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // COMMON_H
