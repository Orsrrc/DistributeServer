#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

//
// define log number
//
#define OK 0
#define ERROR -1
#define STABLISH 0


///////////////////////define the data struct/////////////////////////////////////////////////////////////////////

//
// the struct of block node
//

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////// symbols and Notations ////////////////////////////////////////////////////////////////////

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
            std::cout << "info:" << shard[i] << " " << get_the_shard_ith_dequeue_transaction(shardSet[i]) << " " << BlockSize*BlockInterval/SlotsInterval << std::endl;
            return ERROR;
        }
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void print_hex(const char *label, const uint8_t *v, size_t len);

std::string getMerkleRoot(const std::vector<std::string>& merkle);

std::pair<std::string, std::string> findHash(int index, std::string prevHash, std::vector<std::string>& merkle);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern std::vector<block_queue> queues_set;         // the set of queues
extern std::vector<block_queue> actual_queues_set;  // vector of actual queues
extern std::vector<block_queue> virtual_queues_set; // vector of virtual queues
extern std::vector<block_time> timeslots_set;       // the set of all timeslots
extern std::vector<block_resouce> resouce_set;      // the set of all types of resouces

extern std::map<int, double> shard;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


