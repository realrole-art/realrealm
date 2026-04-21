#include "chatClient.h"
// 构造函数的定义
ChatClient::ChatClient(const char *ip, int port, const string &name) : name(name), running(true)
// 析构函数的定义
ChatClient::~ChatClient()

// 定义运行客户端函数
void ChatClient::run()
// 定义输出错误日志函数
void ChatClient::errLog(const char *msg)
// 定义向服务器发送消息的函数
void ChatClient::sendMsg(int type, const string &text)
// 定义接收服务器发来消息的函数
void ChatClient::recvMsg()