// HTTP服务器
// 声明服务器类

#ifndef __SERVICE_H__
#define __SERVICE_H__

#include <lib_acl.hpp>//该头文件里面包含多个引入头文件代码 引入该文件相当于引入一个库文件


//
// 业务服务类
//
class service_c: public acl::HttpServlet {
public:
    service_c(acl::socket_stream* conn, acl::session* sess)
     : HttpServlet(conn, sess) {}

    ~service_c(){}
protected:
    //处理GET请求
    bool doGet(acl::HttpServletRequest& req,
        acl::HttpServletResponse& res);

    //处理POST请求
    bool doPost(acl::HttpServletRequest& req,
        acl::HttpServletResponse& res);

    //处理GET请求
    bool doOptions(acl::HttpServletRequest& req,
        acl::HttpServletResponse& res);

    //处理GET请求
    bool doError(acl::HttpServletRequest& req,
        acl::HttpServletResponse& res);

    //处理GET请求
    bool doOther(acl::HttpServletRequest& req,
        acl::HttpServletResponse& res, char const* method);

private:
    // 处理文件路由
    bool files(acl::HttpServletRequest& req,
        acl::HttpServletResponse& res);
    //所有请求统一在该位置进行实现
};


#endif