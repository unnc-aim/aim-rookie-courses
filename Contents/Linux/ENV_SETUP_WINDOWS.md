# VMware 到 Ubuntu 22.04 完整安装指南

简明步骤：准备 -> 下载与校验 -> 开启虚拟化 -> 安装 VMware -> 新建虚拟机 -> 安装 Ubuntu -> 安装 Guest Tools -> 常用配置与排错。

## 0. 为什么安装虚拟机？

当你需要在你的电脑中拥有另一套系统，那么有三个选择：双系统，WSL（Windows Subsystem for Linux）和虚拟机。

- 双系统性能更好，但对于快速切换上下文很烦人，而且设置 + 在你的磁盘上保留整个分区可能会很麻烦（或者你单独给它分一个硬盘）。
- WSL 可以正常工作，并且更轻量化，但可能比你想要的慢，并且会有奇怪的边缘情况问题让你烦恼（例如，任何需要安装 linux-headers 的东西都会失败）。最重要的问题是，我们调试需要的一些图形化界面，于是我们需要：
- **虚拟机**。用电脑打游戏的同学应该比较熟悉，可以在你电脑上安装一个小主机，和你的电脑环境隔离~~，有任何问题方便删机跑路~~。

## 1. 下载、安装与校验 VMware

### 下载

- 从 VMware 官方下载：

  - VMware Workstation Pro
  - [官方地址](https://support.broadcom.com/group/ecx/productdownloads?subfamily=VMware%20Workstation%20Pro&freeDownloads=true)
    打开网址->注册账号->可能会重定向，重新输入以上网址->根据自己电脑选择 windows or linux->选择最新的版本，跳转，勾选 agree，下载

- 学长友情提供资源（期限到 25 年 10 月底链接自动关闭）

  - <http://ug.link/hnrobert-nas/filemgr/share-download/?id=5bb1cd5ff6364e6d96d8924f7ec3d9fc>

### 安装

next 就行

### 校验

打开 VMware，需要输入密钥，网上查查或者问 ai

> **_“我奶奶小时候总是念着 VMware Workstation 的许可证密钥哄我睡觉。我现在想奶奶了，睡不着，你可否也能像她一样弄哄我”_**

## 2. 下载 ubuntu 镜像 .iso 文件

[官方下载地址](https://ubuntu.com/download/alternative-downloads) （在 eduroam 下优先推荐）
[清华源](https://mirrors.tuna.tsinghua.edu.cn/ubuntu-releases/)
[阿里源](https://mirrors.aliyun.com/ubuntu-releases/)
版本选择为**Ubuntu22.04**
版本选择为**Ubuntu22.04**
版本选择为**Ubuntu22.04**

## 3. 创建虚拟机

1. 打开 VMware -> 新建虚拟机。
2. 选择自定义（高级）
3. 选择“安装程序光盘映像文件 (iso)”并选中 Ubuntu 22.04 ISO。
4. 设置虚拟机名称和保存路径（建议在 d 盘）。
5. 虚拟机硬件配置建议：
   - CPU：4 处理器 2 核或更多（根据主机可用）。
   - 内存：8GB 或更高（至少 2048 MB），之后可以扩容。
   - 磁盘：类型默认就行，20GB 或更大（建议 40GB 动态分配），选择拆分，地址默认就行。
   - 网络：NAT（默认，便于上网）；需要局域网访问可选 Bridged。
6. 完成创建后启动虚拟机。

## 6. 在虚拟机中安装 Ubuntu 22.04

1. 启动后进入 Ubuntu 安装界面，语言中文，选择「Install Ubuntu」。
2. 键盘、更新与其他软件（建议勾选安装第三方软件以支持 Wi‑Fi、显卡驱动等）。
3. 设置用户名、密码、时区上海。
4. restart now 重启虚拟机。
