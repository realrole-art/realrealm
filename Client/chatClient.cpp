/***************************************
 *         客户端函数认领表
 *  请在对应函数上方填写负责人姓名
 ***************************************/

/*
 * 函数：ChatClient::ChatClient(const char*, int, const string&)
 * 功能：构造函数，创建socket、连接服务器、发送登录消息
 * 负责人：[星奔川骛]
 */

/*
 * 函数：ChatClient::~ChatClient()
 * 功能：析构函数，关闭套接字
 * 负责人：[___________]
 */

/*
 * 函数：void ChatClient::errLog(const char*)
 * 功能：打印错误日志
 * 负责人：[realrole]
 */

/*
 * 函数：void ChatClient::sendMsg(int, const string&)
 * 功能：序列化消息并通过socket发送
 * 负责人：[___________]
 */

/*
 * 函数：void ChatClient::recvMsg()
 * 功能：接收服务器消息、反序列化并显示
 * 负责人：[___________]
 */

/*
 * 函数：void ChatClient::run()
 * 功能：主循环，使用select监听标准输入和socket
 * 负责人：[___________]
 */

// ========== 以下是函数实现代码，请在对应函数内编写 ==========
#include "chatClient.h"
// 构造函数的定义
ChatClient::ChatClient(const char *ip, int port, const string &name) : name(name), running(true)
{
    // 1. 创建套接字
    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd < 0)
    {
        errLog("socket 创建失败");
        exit(EXIT_FAILURE);
    }

    // 2. 设置服务器地址信息
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;           // IPv4
    sin.sin_port = htons(port);         // 端口号
    sin.sin_addr.s_addr = inet_addr(ip); // 服务器 IP

    // 3. 连接服务器
    if (connect(cfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        errLog("connect 连接失败");
        close(cfd);
        exit(EXIT_FAILURE);
    }

    // 4. 发送登录消息
    MSG msg;
    memset(&msg, 0, sizeof(msg));
    msg.type = LOGIN;
    strncpy(msg.name, name.c_str(), sizeof(msg.name) - 1);
    strncpy(msg.text, "", sizeof(msg.text) - 1);

    string data = msg.serialize();
    if (send(cfd, data.c_str(), data.size(), 0) < 0)
    {
        errLog("send 发送登录消息失败");
        close(cfd);
        exit(EXIT_FAILURE);
    }
}
// 析构函数的定义
ChatClient::~ChatClient()

// 定义运行客户端函数
void ChatClient::run()
// 定义输出错误日志函数
void ChatClient::errLog(const char *msg){
    cerr << __FILE__ << " " << __func__ << " " << __LINE__ << endl;
    perror(msg);
}
// 定义向服务器发送消息的函数
void ChatClient::sendMsg(int type, const string &text)
// 定义接收服务器发来消息的函数
void ChatClient::recvMsg()