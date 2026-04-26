/***************************************
 *         客户端函数认领表
 *  请在对应函数上方填写负责人姓名
 ***************************************/

/*
 * 函数：ChatClient::ChatClient(const char*, int, const string&)
 * 功能：构造函数，创建socket、连接服务器、发送登录消息
 * 负责人：[___________]
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
 * 负责人：[懒惰鬼]
 */

// ========== 以下是函数实现代码，请在对应函数内编写 ==========
#include "chatClient.h"
// 构造函数的定义
ChatClient::ChatClient(const char *ip, int port, const string &name) : name(name), running(true)
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
void ChatClient::recvMsg(){
    //接收消息
    char buf[sizeof(MSG)] = "";
    while(running){
        //非阻塞接收
        int rec = recv(cfd,buf,size(buf),MSG_DONTWAIT);
        if(rec < 0){
            if(errno == EAGAIN){
                usleep(100000);

            }
            else{
                errLog("recv error");
                running = false;
                break;
            }
        }
         else if (recv_len == 0){
            errLog("recv error");
            running = false;
            break; 
        }
        else{
            MSG msg;
            msg.deserialize(string(buf, rec));
            cout << msg.name << ':' << msg.text << endl;
        }
    }
}