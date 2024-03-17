#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <ctime>

//
// define log number
//
#define OK           0
#define ERROR       -1
#define STABLISH     0
#define SERVER_PORT 9800
#define PROTOCOL_TCP 0
#define PROTOCOL_UDP 1

////////////////////////////////GLOBAL////////////////////////////////////////////////////////////////////////////

int shardNum = 0;
int SourceNum = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////GLOBAL FUNCTION///////////////////////////////////////////////////////////////

int get_current_time()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::cout << "Current time: " << std::ctime(&now_time);
    return 0;
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // COMMON_H
