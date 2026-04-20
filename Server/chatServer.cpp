#include "chatServer.h"

// 构造函数的定义：初始化服务器，创建套接字、绑定地址信息结构体，启动监听
chatServer::chatServer(const char *ip, int port, size_t threadPoolSize) : stop(false)
// 析构函数的定义
chatServer::~chatServer()
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