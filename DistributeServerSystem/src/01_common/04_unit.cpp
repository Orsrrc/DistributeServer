#include <string>
#include <vector>
#include <cstring>
#include "unit.h"
#include "types.h"

//主机序 即小端序
//网络序 即大端序
//参数n代表接收到的字符串

// long long类型整数主机序转网络序
// long long类型整数网络序转主机序  注意小端序变为大端序

using byte = unsigned char;

// 主机序转网络序
void llton(int64_t ll, byte* n) {
    for (size_t i = 0; i < sizeof(ll); ++i) {
        n[i] = (ll >> ((sizeof(ll) - i - 1) * 8)) & 0xFF;
    }
}

void lton(int32_t l, byte* n) {
    for (size_t i = 0; i < sizeof(l); ++i) {
        n[i] = (l >> ((sizeof(l) - i - 1) * 8)) & 0xFF;
    }
}

void ston(int16_t s, byte* n) {
    for (size_t i = 0; i < sizeof(s); ++i) {
        n[i] = (s >> ((sizeof(s) - i - 1) * 8)) & 0xFF;
    }
}

//网络序转主机序
//注意 网络序在转换为主机序的时候网络序的第一个字节是主机序的最后一个字节
//因此对于0x12 就需要移位为0x1200000000000000 然后主机会将其最高位存储在低地址
//如果我们直接将网络序拿来用那么其在内存中的时候就是倒过来的
int64_t ntoll(const byte* n) {
    int64_t ll = 0;
    for (size_t i = 0; i < sizeof(ll); ++i) {
        ll |= static_cast<int64_t>(n[i]) << ((sizeof(ll) - i - 1) * 8);
    }
    return ll;
}

int32_t ntol(const byte* n) {
    int32_t l = 0;
    for (size_t i = 0; i < sizeof(l); ++i) {
        l |= static_cast<int32_t>(n[i]) << ((sizeof(l) - i - 1) * 8);
    }
    return l;
}

int16_t ntos(const byte* n) {
    int16_t s = 0;
    for (size_t i = 0; i < sizeof(s); ++i) {
        s |= static_cast<int16_t>(n[i]) << ((sizeof(s) - i - 1) * 8);
    }
    return s;
}

//用模板实现
#include <cstdint>
#include <type_traits>
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
host_to_network(T value, unsigned char* bytes) {
    for (size_t i = 0; i < sizeof(T); ++i) {
        bytes[i] = static_cast<unsigned char>(
            (value >> ((sizeof(T) - i - 1) * 8)) & 0xFF
        );
    }
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
network_to_host(const unsigned char* bytes) {
    T result = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        result |= static_cast<T>(bytes[i]) << ((sizeof(T) - i - 1) * 8);
    }
    return result;
}

// 字符串是否合法，即是否只包含26个英文字母大小写和0到9十个阿拉伯数字
int valid(const char* str)
{
    if (!str)
    {
        return ERROR;
    }
        
    //遍历字符串 逐个检查 判断其ASCII码 A~Z 65-90 0~9 48-57 a~z 97-122

    //for(int i = 0; str[i] != '\0'; i++)
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++)
    {
       if (!(('a' <= str[i] && str[i] <= 'z') ||
              ('A' <= str[i] && str[i] <= 'Z') ||
              ('0' <= str[i] && str[i] <= '9')))
        {
            return ERROR;
        }
           

        return OK;
    }

    return OK;
}

// 以分号为分隔符将一个字符串拆分为多个子字符串
int split(const char* str, std::vector<std::string>& substrs)
{
    if (!str)
    {
        return ERROR;
    }
        
    size_t len = strlen(str);

    if (!len)
    {
        return ERROR;
    }
        
    std::string temp = "";
    int j = 0;
    for(int i = 0; str[i] != '\0'; i++)
    {
        for(j = i; str[j] != ';' && str[j] != '\0' ; j++)
        {
            temp += str[j];
        }
        substrs.push_back(temp);
        temp = "";
        i = j;
        
    }
    return 0;
}


std::string to_string(REDIS_PREFIX pre)
{
    switch(pre)
    {
        case REDIS_PREFIX::TRACKER_REDIS_PREFIX_2:
        {
            return "tracker";
        }

        case REDIS_PREFIX::STORAGE_REDIS_PREFIX_3:
        {
            return "storage";
        }
            
    }

    return nullptr;
}



