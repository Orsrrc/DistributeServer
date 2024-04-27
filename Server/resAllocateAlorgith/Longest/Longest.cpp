#include "Longest.h"

int longest::allocate(std::map<int, std::string> resourceSet)
{
    for (auto iterator = resourceSet.begin(); iterator != resourceSet.end(); iterator++)
    {



    }
    return OK;
}

int longest::get_longest_shard_id (std::map<int, int> shard_length)
{
    int ID = 0;
    int longest = 0;
    for (auto iterator = shard_length.begin(); iterator != shard_length.end(); iterator++)
    {
        if (iterator->second > longest)
        {
            ID = iterator->first;
        }
    }

    return ID;
}