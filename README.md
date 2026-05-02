C++11版本 linux环境下开发
运行Qt版客户端的方法：

一、linux虚拟机上运行(我使用的是Ubuntu，如果用的是centOS，指令可能会有少量区别，如安装软件)：
1.安装Qt必要组件（考虑到大家一般开的虚拟机内存不足以下载完整的Qt，改起来也没那么简单，就只下必要组件）：

sudo apt update
sudo apt install qt6-base-dev cmake build-essential
sudo apt install qtcreator

第一步的验证，检查是不是输出就行，而不是not found这种或者没有输出：
qmake6 -v
dpkg -l | grep qt6-base
dpkg -l | grep qt6


2.安装补充依赖：
sudo apt install libgl1-mesa-dev mesa-common-dev libglu1-mesa-dev

# 安装文泉驿微米黑（Linux 上常用的开源中文字体）
sudo apt update
sudo apt install fonts-wqy-microhei
第二步验证，应该有三个“ii”开头的输出，而不是没有输出：
dpkg -l | grep -E "libgl1-mesa-dev|libglu1-mesa-dev|mesa-common-dev"

3.编译项目：
（先打开你的gui目录）
mkdir build
cd build
cmake ..
make -j2

4.运行：
运行前请确保server已经在运行

（gui的build目录下，注意这里要在虚拟机本体输入，远程连接命令行当然显示不出图形化界面）ps:其实也可以弹出来
./ChatGuiClient 即可

或者手动点图形化界面中的相应文件也行，点几次就出来几个客户端
