---
title: "树莓派"
date: 2020-02-10
---

树莓派（raspberriPi）是一个微型的，信用卡大小的可以运行Linux的单板机。它使用的是基于精简指令集（RISC）的ARM架构的处理器，相比于Intel采用的x86的复杂指令集（CISC），它的结构简单，功耗低，价格低，非常适合(穷)学生。

<!--more-->

这学习开了一门《嵌入式系统导论》，像我这种学生其实完全不学的，但刚好轮到我做这门课的实验，于是我借了块板子，开始了与树莓派的奇妙冒险（最后这门课只得了70分，史上最低），实验内容主要是使用GPIO控制传感器，电子电气的同学肯定很熟悉，但对于学计算机的同学就有另一套玩法了。

比如说之前心心念念的[GameShell](https://www.clockworkpi.com/)，一个模块化的开源掌机，但它太贵了（1000￥），然而现在你可以单独购买电池、屏幕、扬声器手柄等配件，制作属于自己的掌机，还可以用来学习Linux和计算机网络等，我最开始是借的同学的3B，后来忍不住自己又去买了4B，最新版本是V1.2，不要跟我一样买到旧款了，旧款的不支持高端usb-c充电器，影响不大，推荐使用官方的充电设备，不要使用移动电源和电脑端的USB口。

## 系统安装

首先需要一个SD卡格式化软件[SDFormatter](https://www.sdcard.org/downloads/formatter/)，每次安装新系统前都推荐先格式化

### NOOBS

[下载地址](https://www.raspberrypi.org/downloads/)，即New Out of Box System（全新开箱即用系统），只需要去官网下载然后拷贝到SD卡就可以了

优点：

- 简单
- 可以安装多系统

缺点

- 体积大
- 安装过程慢

### 手动烧录系统

[下载地址](https://www.raspberrypi.org/downloads/raspbian/)可以使用一键烧录软件如win32diskimager和ApplePi-Baker

这里使用MacOS/Linux下的dd命令来烧录

1. 查看当前哪些设备已挂载，找到SD卡，如/dev/sda1
```
df -h
```
2. 卸载设备
```
umount /dev/sda1
```
3. 烧录，PATH为镜像的路径，bs表示一次写入多大的块，一般耗时几分钟不等
```
sudo dd if=PATH.img of=/dev/sda1 bs=4m; 
sync
```
## 开机启动

如果有显示器，直接连上就可以开机了，图形界面谁不爱呢?

如果没有，使用SSH连接，树莓派为了安全考虑默认关闭了SSH，需要你在根目录下新建一个名为SSH（没有扩展名）的文件，推荐直接使用网线连接树莓派

1. 打开命令行，可以在路由器后台查询树莓派的ip地址，但也可以使用以下方式
```
sudo ssh pi@raspberrypi.local
```
默认账号为pi，默认密码为raspberry，登录后系统会提示你修改

2. 开启VNC（Virtual Network Computing），之后你就可以远程通过图形界面使用树莓派了
```
sudo raspi-config
```
3. 选择Interfacing Options，选择VNC，重启
```
sudo reboot
```
4. 在你的电脑上下载[VNCViewer](https://www.realvnc.com/en/connect/download/viewer/)，登录方式与SSH类似

5. 开始折腾！

## 可安装的操作系统

在自己电脑上折腾实体Linux很危险的，但在树莓派上就非常方便，可以多准备几个SD卡换着用

- ArchLinux

  绝配，妙不可言，推荐使用i3桌面管理器，简洁高效，开源社区有很多不错的桌面环境比如sway

- Ubuntu Mate

  图形界面很好用，1G内存稍有不足

- Windows 10 IoT Core

  主要面向物联网开发

- RetroPie

  严格来说并不算是系统，它是一个游戏机模拟器，在上面你可以玩到非常多的复古游戏，推荐直接[下载](https://www.arcadepunks.com/pi-images-downloads-page/)拷满游戏的镜像，为此你需要准备一个相当大的SD卡和一个复古手柄（强烈推荐八位堂8Bitdo），也可以使用PICO-8等复古游戏引擎自己开发游戏

- Android

  没试过

- OSMC

  家庭娱乐中心，也就是机顶盒

- RISC OS

  过于硬核

## 其他用途

-  日常开发

  用来学Python再适合不过

-  机器人控制

  你可以在树莓派上安装摄像头，氢气球和传感器，让它飞向地球的边缘，去探索太空。当然了，这么做的话风险很大，一定要注意安全。这里指的不是你和你的树莓派，而是天上的飞机和住在下面的人们

-  路由器

  最开始的目的其实是为了搭建mentoHUST+ssr的路由器，但前提是电脑和树莓派要连在同一局域网下，渣科的校园网有登陆限制，所以我不得不再买一个路由器，虽然得不偿失但用起来还是很爽的，后来把家里的路由器刷了梅林固件，安装ssr插件，就不用在每个设备上单独配置了，非常方便

-  网络附属存储（NAS）

  3b型号的网口与USB共享300Mbps的带宽，4b升级成了千兆网口和USB3.0，大有一番作为，其实路由器（软路由）也可以实现这个功能，但专业的还是用群晖吧（好贵）

-  私有云&离线下载

  Aira2 ownCloud等，度盘药丸

-  网站服务器

  搭建个人博客，WordPress比较臃肿，静态博客的话推荐hugo

-  计算机集群

  使用多个树莓派搭建分布式系统