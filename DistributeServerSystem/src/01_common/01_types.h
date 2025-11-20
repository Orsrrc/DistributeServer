#ifndef __TYPES__
#define __TYPES__

#include <netinet/in.h>

//////////////////////////////函数返回值/////////////////////////////
#define OK               0   //成功
#define ERROR           -1   //本地错误
#define SOCKET_ERROR    -2   //套接字通信错误
#define STATUS_ERROR    -3   //服务器状态异常 

/*
enum class RTN_STATUS : int64_t
{
    OK = 20,
    ERROR = -21,
    SOCKET_ERROR = -22,
    STATUS_ERROR = -23
};
*/
////////////////////////////////////////////////////////////////////


//////////////////////////////缓存//////////////////////////////////
#define TRACKER_REDIS_PREFIX "tracker" // 跟踪服务器Redis前缀
#define STORAGE_REDIS_PREFIX "storage" // 存储服务器Redis前缀


enum class REDIS_PREFIX
{
    TRACKER_REDIS_PREFIX_2,
    STORAGE_REDIS_PREFIX_3
};


////////////////////////////////////////////////////////////////////


//////////////////////////////存储服务器状态/////////////////////////
typedef enum storage_status {
    STORAGE_STATUS_OFFLINE, // 存储服务器离线
    STORAGE_STATUS_ONLINE,  // 存储服务器在线
    STORAGE_STATUS_ACTIVE   // 存储服务器活动
}   storage_status_t;       // 存储服务器状态
////////////////////////////////////////////////////////////////////

































#endif
