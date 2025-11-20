/*
    报文规约
*/
#ifndef _PROTO_H_
#define _PROTO_H_

#include "types.h"

/*
 |包体长度|命令|状态|  包体  |
 |    8   |  1 |  1 |包体长度|
*/

#define BODYLEN_SIZE    8 //包体长度
#define COMMAND_SIZE    1 //命令
#define STATUS_SIZE     1 //状态
#define HEADLEN (BODYLEN_SIZE + COMMAND_SIZE + STATUS_SIZE)


/* 
|包体长度|命令|状态|错误号|错误描述|
|    8   |  1 |  1 |   2  | <=1024 |
*/

#define ERROR_NUMB_SIZE  2      //错误号字节数
#define ERROR_DESC_SIZE 1024    //错误描述最大字节数(含结尾空字符)

/*
|包体长度|命令|状态|应用ID|用户ID|文件ID|
|    8   |  1 |  1 |  16  |  256 |  128 |
*/
#define APPID_SIZE  16  //应用ID最大字节数(含结尾空字符)
#define USERID_SIZE 256 //用户ID最大字节数(含结尾空字符)
#define FILEID_SIZE 128 //文件ID最大字节数(含结尾空字符)



#endif
