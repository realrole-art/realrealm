/***************************************
 *         服务端函数认领表
 *  请在对应函数上方填写负责人姓名
 ***************************************/

/*
 * 函数：chatServer::chatServer(const char*, int, size_t)
 * 功能：构造函数，创建socket、绑定、监听，初始化线程池
 * 负责人：[___________]
 */

/*
 * 函数：chatServer::~chatServer()
 * 功能：析构函数，停止线程池、关闭套接字
 * 负责人：[realrole]
 */

/*
 * 函数：void chatServer::errLog(const char*)
 * 功能：打印错误日志
 * 负责人：[___________]
 */

/*
 * 函数：void chatServer::startThreadPool(size_t)
 * 功能：创建指定数量的工作线程，从任务队列取任务执行
 * 负责人：[___________]
 */

/*
 * 函数：void chatServer::addTask(function<void()>)
 * 功能：向任务队列添加任务，并唤醒一个工作线程
 * 负责人：[___________]
 */

/*
 * 函数：void chatServer::run()
 * 功能：主循环，accept新连接，将客户端加入列表并交给线程池处理
 * 负责人：[___________]
 */

/*
 * 函数：void chatServer::handleClient(int, struct sockaddr_in)
 * 功能：处理单个客户端连接，循环接收消息，根据类型处理登录/聊天/退出
 * 负责人：[___________]
 */

/*
 * 函数：void chatServer::broadcast(const MSG&, int)
 * 功能：向所有在线客户端广播消息，可排除指定fd
 * 负责人：[___________]
 */

// ========== 以下是函数实现代码，请在对应函数内编写 ==========
#include "chatServer.h"

// 构造函数的定义：初始化服务器，创建套接字、绑定地址信息结构体，启动监听
chatServer::chatServer(const char *ip, int port, size_t threadPoolSize) : stop(false)
// 析构函数的定义
chatServer::~chatServer(){
    stop=true;
    task_cv.notify_all(); // 唤醒所有线程
    for(auto &x:workers){
        x.join();
    }
    close(sfd);
}
// 启动线程池函数的定义
void chatServer::startThreadPool(size_t numThreads)
// 将任务加到线程池中
void chatServer::addTask(function<void()> task)
// 打印错误日志函数的定义
void chatServer::errLog(const char *msg)
// 启动服务器函数的定义
void chatServer::run()
// 处理客户端消息的函数定义
void chatServer::handleClient(int client_fd, struct sockaddr_in cin)
// 定义广播函数
void chatServer::broadcast(const MSG &msg, int exclude_fd)