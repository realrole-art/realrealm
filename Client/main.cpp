#include "chatClient.h"

#include <vector>            
#include <thread>            
#include <queue>             
#include <condition_variable> 
#include <mutex>             
#include <functional>         
#include <iostream>       
#include <string>            
#include <cstring>           
#include <cstdlib>          
#include <unistd.h>          
#include <sys/socket.h>      
#include <netinet/in.h>      
#include <arpa/inet.h>       
#include <sys/select.h>      
#include <sys/time.h>        
#include <fcntl.h>           
#include <errno.h>
#include <thread> 

int main(int argc, const char *argv[])
{
    // 确保执行时，外部传入了ip地址、端口号、用户名
    if (argc < 4)
    {
        cout << "请输入 ip  端口号  用户名" << endl;
        return -1;
    }

    // 实例化一个客户端
    ChatClient client(argv[1], atoi(argv[2]), argv[3]);

    // 运行客户端
    client.run();

    return 0;
}