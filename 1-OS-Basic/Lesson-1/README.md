# OS-Basic Lesson-1: Linux 系统基础和命令行操作

## 课程信息

- **课时**: 2 学时
- **难度**: 入门级
- **前置要求**: 基本计算机操作能力

## 学习目标

完成本节课后，学员将能够：

1. 理解 Linux 操作系统的基本概念和特点
2. 独立安装和配置 Ubuntu 系统
3. 熟练使用 Linux 桌面环境
4. 掌握命令行基本操作
5. 进行文件和目录管理
6. 使用包管理器安装软件
7. 配置 RoboMaster 开发环境

## 课程大纲

### 第一部分：Linux 系统概述（20 分钟）

#### 1.1 什么是 Linux

**Linux 的特点：**

- 开源免费：源代码公开，可自由使用和修改
- 多用户多任务：支持多个用户同时使用，多个程序并发运行
- 稳定可靠：服务器和嵌入式系统的首选
- 安全性高：完善的权限管理机制
- 可定制性强：可根据需求进行深度定制

**为什么选择 Ubuntu：**

- 用户友好的桌面环境
- 丰富的软件源和社区支持
- 适合开发和学习使用
- RoboMaster 官方推荐的开发环境

#### 1.2 Linux 在 RoboMaster 中的应用

- **机器人控制系统**：大部分 RoboMaster 机器人使用 Linux 作为操作系统
- **开发环境**：编译工具链、调试工具、版本控制
- **视觉处理**：OpenCV、深度学习框架通常在 Linux 上运行
- **仿真环境**：Gazebo、RViz 等机器人仿真工具
- **服务器部署**：数据分析、云端处理服务

### 第二部分：Ubuntu 系统安装与配置（30 分钟）

#### 2.1 虚拟机安装准备

**下载必要软件：**

1. VirtualBox（免费）或 VMware Workstation
2. Ubuntu 20.04 LTS Desktop ISO 镜像
3. 确保主机有足够的资源（内存 8GB+，硬盘空间 20GB+）

**虚拟机配置建议：**

```text
内存：4GB（推荐8GB）
硬盘：动态分配，最小20GB
处理器：2核心（支持虚拟化）
网络：NAT或桥接模式
```

#### 2.2 Ubuntu 安装过程

**安装步骤演示：**

1. 创建新虚拟机，加载 Ubuntu ISO
2. 选择语言和键盘布局
3. 网络配置（可选）
4. 磁盘分区设置
5. 用户账户创建
6. 安装完成后的首次启动配置

**安装后的初始设置：**

```bash
# 更新系统
sudo apt update
sudo apt upgrade -y

# 安装中文语言包
sudo apt install language-pack-zh-hans

# 安装常用工具
sudo apt install curl wget git vim tree htop
```

#### 2.3 桌面环境介绍

**GNOME 桌面组件：**

- Activities overview：应用程序启动器
- Files (Nautilus)：文件管理器
- Settings：系统设置
- Software：软件中心
- Terminal：终端模拟器

**常用快捷键：**

```text
Super键：打开Activities overview
Ctrl+Alt+T：打开终端
Alt+Tab：切换应用程序
Super+L：锁屏
Ctrl+C：复制（终端中为中断命令）
Ctrl+V：粘贴（终端中为Ctrl+Shift+V）
```

### 第三部分：命令行基础（40 分钟）

#### 3.1 终端和 Shell 介绍

**什么是 Shell：**

- Shell 是用户与 Linux 内核交互的接口
- 常见的 Shell：bash, zsh, fish
- Ubuntu 默认使用 bash

**终端基本概念：**

```bash
user@hostname:~$
# user: 当前用户名
# hostname: 计算机名
# ~: 当前目录（~表示家目录）
# $: 普通用户提示符（#表示root用户）
```

#### 3.2 文件系统结构

**Linux 目录结构：**

```text
/                   # 根目录
├── home/          # 用户家目录
│   └── username/  # 具体用户目录
├── usr/           # Unix系统资源
├── etc/           # 系统配置文件
├── var/           # 变量数据文件
├── tmp/           # 临时文件
├── bin/           # 基本命令
├── sbin/          # 系统管理命令
└── dev/           # 设备文件
```

**路径概念：**

- 绝对路径：从根目录开始，如 `/home/user/Documents`
- 相对路径：从当前目录开始，如 `./file.txt` 或 `../parent`
- 特殊目录：`.`（当前目录）、`..`（父目录）、`~`（家目录）

#### 3.3 基本文件操作命令

**目录操作：**

```bash
# 显示当前目录
pwd

# 切换目录
cd /home/user/Documents
cd ~                    # 回到家目录
cd ..                   # 回到父目录
cd -                    # 回到上一次所在目录

# 列出文件和目录
ls                      # 基本列表
ls -l                   # 详细信息
ls -la                  # 包含隐藏文件
ls -lh                  # 人类可读的文件大小

# 创建目录
mkdir new_folder
mkdir -p path/to/deep/folder  # 创建多级目录

# 删除目录
rmdir empty_folder      # 删除空目录
rm -rf folder_name      # 递归删除目录及内容（危险命令！）
```

**文件操作：**

```bash
# 创建文件
touch filename.txt
echo "Hello World" > file.txt

# 复制文件
cp source.txt destination.txt
cp -r source_folder/ dest_folder/  # 复制目录

# 移动/重命名文件
mv old_name.txt new_name.txt
mv file.txt /path/to/destination/

# 删除文件
rm filename.txt
rm -i filename.txt      # 交互式删除（确认）

# 查看文件内容
cat filename.txt        # 显示全部内容
head filename.txt       # 显示前10行
tail filename.txt       # 显示后10行
less filename.txt       # 分页查看（按q退出）

# 搜索文件内容
grep "pattern" filename.txt
grep -r "pattern" directory/  # 递归搜索目录
```

**文件权限管理：**

```bash
# 查看权限
ls -l filename.txt
# 结果示例：-rw-r--r-- 1 user group 1024 Dec 7 10:30 filename.txt

# 权限含义：
# -rw-r--r--
# 第1位：文件类型（-文件，d目录，l链接）
# 2-4位：所有者权限（rwx：读写执行）
# 5-7位：组权限
# 8-10位：其他用户权限

# 修改权限
chmod 755 script.sh     # 数字方式
chmod +x script.sh      # 添加执行权限
chmod -w file.txt       # 移除写权限

# 修改所有者
sudo chown user:group filename.txt
```

### 第四部分：文本编辑工具（20 分钟）

#### 4.1 vim 编辑器（推荐）

```bash
# 编辑文件
vim filename.txt

# vim 常用模式：
# 普通模式：移动光标、删除文本
# 插入模式：编辑文本
# 命令模式：保存、退出等操作

# 常用快捷键：
# i       进入插入模式
# Esc     返回普通模式
# :w      保存文件
# :q      退出
# :wq     保存并退出
# :q!     不保存强制退出
# dd      删除当前行
# yy      复制当前行
# p       粘贴
# /文本   搜索文本
# :help   查看帮助
```

#### 4.3 VS Code 图形编辑器

```bash
# 启动 VS Code 编辑器（需已安装 code 命令）
code filename.txt &

# 特点：
# - 跨平台图形界面，支持多标签和分屏
# - 语法高亮和智能补全
# - 丰富插件生态，适合开发和文档编辑
# - 集成终端和Git工具
```

### 第五部分：软件包管理（25 分钟）

#### 5.1 APT 包管理器

**APT（Advanced Package Tool）是 Ubuntu 的包管理系统：**

```bash
# 更新包列表
sudo apt update

# 升级所有已安装的包
sudo apt upgrade

# 搜索软件包
apt search python3
apt search "text editor"

# 显示包信息
apt show package_name

# 安装软件包
sudo apt install package_name
sudo apt install git vim curl

# 删除软件包
sudo apt remove package_name
sudo apt purge package_name    # 同时删除配置文件

# 自动清理不需要的依赖
sudo apt autoremove

# 清理下载的包文件
sudo apt autoclean
```

#### 5.2 Snap 包管理器

```bash
# 搜索snap包
snap find code

# 安装snap包
sudo snap install code --classic
sudo snap install discord

# 列出已安装的snap包
snap list

# 更新snap包
sudo snap refresh package_name

# 删除snap包
sudo snap remove package_name
```

#### 5.3 常用软件安装

**开发工具：**

```bash
# Git版本控制
sudo apt install git

# Python开发环境
sudo apt install python3 python3-pip

# Node.js和npm
sudo apt install nodejs npm

# C/C++编译环境
sudo apt install build-essential

# VS Code编辑器
sudo snap install code --classic
```

**系统工具：**

```bash
# 系统监控
sudo apt install btop

# 网络工具
sudo apt install net-tools

# 压缩工具
sudo apt install zip unzip

# 媒体工具
sudo apt install vlc

# 后台运行工具
sudo apt install tmux
```

### 第六部分：系统管理基础（15 分钟）

#### 6.1 进程管理

```bash
# 查看运行中的进程
ps aux
ps -ef

# 实时查看进程
top
htop    # 需要先安装：sudo apt install htop

# 根据名称查找进程
ps aux | grep process_name

# 终止进程
kill process_id
killall process_name
kill -9 process_id  # 强制终止

# 后台运行程序
command &
nohup command &     # 即使关闭终端也继续运行
tmux new -s session_name  # 使用tmux创建新会话
tmux attach -t session_name  # 重新连接到会话
```

#### 6.2 用户管理

```bash
# 查看当前用户
whoami
id

# 查看所有用户
cat /etc/passwd

# 切换用户
su username
sudo su -           # 切换到root用户

# 添加用户（需要root权限）
sudo adduser newuser

# 修改密码
passwd              # 修改当前用户密码
sudo passwd username # 修改指定用户密码
```

#### 6.3 系统信息

```bash
# 系统信息
uname -a            # 系统详细信息
lsb_release -a      # Ubuntu版本信息

# 硬件信息
lscpu               # CPU信息
free -h             # 内存使用情况
df -h               # 磁盘使用情况
lsusb               # USB设备
lspci               # PCI设备
sudo fdisk -l       # 磁盘分区信息

# 网络信息
ifconfig            # 网络接口信息
ip addr show        # 新版本网络信息命令
ping google.com     # 网络连通性测试
```

### 第七部分：SSH 远程连接（20 分钟）

#### 7.1 SSH 基础概念

**什么是 SSH：**

- SSH (Secure Shell) 是一种安全的远程连接协议
- 提供加密的网络连接，保护数据传输安全
- 广泛用于远程服务器管理和文件传输
- RoboMaster 中常用于远程控制机器人系统

**SSH 的优势：**

- 数据传输加密，安全性高
- 支持密钥认证，免密码登录
- 可以进行端口转发和隧道传输
- 跨平台支持，兼容性好

#### 7.2 SSH 服务配置

**安装和启动 SSH 服务：**

```bash
sudo apt update
sudo apt install ssh  # 安装 openssh-server 等 ssh 相关工具

# 启动 SSH 服务
sudo systemctl start ssh

# 设置开机自启
sudo systemctl enable ssh

# 查看 SSH 服务状态
sudo systemctl status ssh

# 查看 SSH 服务是否在监听
sudo netstat -tlnp | grep :22
```

**SSH 配置文件：**

```bash

# 编辑 SSH 配置文件
sudo vim /etc/ssh/sshd_config

# 常用配置项：
# Port 22                    # SSH 端口
# PermitRootLogin no         # 禁止 root 直接登录
# PasswordAuthentication yes # 允许密码认证
# PubkeyAuthentication yes   # 允许公钥认证

# 重启 SSH 服务使配置生效
sudo systemctl restart ssh
```

#### 7.3 SSH 客户端使用

**基本连接语法：**

```bash
# 基本连接格式
ssh username@hostname_or_ip

# 指定端口连接
ssh -p 2222 username@hostname

# 带调试信息连接
ssh -v username@hostname

# 执行远程命令
ssh username@hostname 'ls -la'

# 保持连接活跃
ssh -o ServerAliveInterval=60 username@hostname

# 自动拷贝密钥 (macOS 等 Linux/Unix 系统内置)
ssh-copy-id username@remote_host

# 拷贝文件
scp local_file.txt username@remote_host:/path/to/destination/
```

#### 7.4 **实践练习：连接虚拟机**

- **获取虚拟机 IP 地址：**

```bash
# 在虚拟机中查看 IP
ip addr show
# 或
ifconfig

# 记录 IP 地址，例如：192.168.1.100
```

- **从主机连接虚拟机：**

```bash
# 在主机终端中执行（Windows 可用 PowerShell 或 Git Bash）
ssh your_username@192.168.1.100

# 首次连接会提示确认主机密钥，输入 yes
# 然后输入用户密码
```

- **常见网络配置：**

```bash
# 如果虚拟机使用 NAT 网络，需要设置端口转发
# VirtualBox 设置示例：
# 网络 -> 高级 -> 端口转发
# 名称：SSH，协议：TCP，主机端口：2222，子系统端口：22

# 连接方式：
ssh -p 2222 username@localhost
```

#### 7.4 SSH 密钥认证

**生成 SSH 密钥对：**

```bash
# 本地生成 RSA 密钥对
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"

# 生成 Ed25519 密钥对（推荐）
ssh-keygen -t ed25519 -C "your_email@example.com"

# 密钥默认保存在 ~/.ssh/ 目录
# id_rsa 或 id_ed25519：私钥（保密）
# id_rsa.pub 或 id_ed25519.pub：公钥（可分享）
```

**配置免密登录：**

```bash
# 方法1：使用 ssh-copy-id（推荐， 但是只有 macOS 等 Unix/Linux 系统的 ssh 安装后内置这个命令）
ssh-copy-id username@remote_host

# 方法2：手动复制公钥
cat ~/.ssh/id_rsa.pub | ssh username@remote_host 'mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys'

# 方法3：在远程主机上手动添加
# 1. 复制本地公钥内容
cat ~/.ssh/id_rsa.pub

# 2. 在远程主机上创建目录并添加公钥
mkdir -p ~/.ssh
echo "公钥内容" >> ~/.ssh/authorized_keys
chmod 700 ~/.ssh
chmod 600 ~/.ssh/authorized_keys
```

**SSH 配置文件：**

```bash

# 编辑 SSH 客户端配置
vim ~/.ssh/config

# 配置示例：
Host myvm
    HostName 192.168.1.100
    User myuser
    Port 22
    IdentityFile ~/.ssh/id_rsa

Host robomaster-dev
    HostName 10.0.0.50
    User developer
    Port 2222
    IdentityFile ~/.ssh/robomaster_key

# 使用配置别名连接
ssh myvm
ssh robomaster-dev
```

### 第八部分：RoboMaster 开发环境配置（10 分钟）

#### 8.1 基础开发环境

```bash
# 安装基础开发工具
sudo apt update
sudo apt install -y \
    git \
    vim \
    curl \
    wget \
    build-essential \
    cmake \
    python3 \
    python3-pip \
    python3-dev

# 配置Git
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# 创建开发目录结构
mkdir -p ~/robomaster/{src,build,docs,scripts}
cd ~/robomaster
```

## 课堂练习

### 练习 1：文件系统操作

使用终端在家目录下创建以下目录结构，并在相应位置创建文件：

```text
robomaster/
├── projects/
│   ├── vision/
│   │   └── camera_test.py
│   └── control/
│       └── motor_control.cpp
├── docs/
│   └── notes.md
└── scripts/
    └── setup.sh
```

### 练习 2：权限管理

- 创建一个 shell 脚本文件
- 设置为可执行权限
- 创建一个只有所有者可读写的文件
- 查看并理解权限设置

### 练习 3：软件安装实践

使用 apt 安装以下软件：

- tree（目录树显示工具）
- code（VS Code 编辑器）
- git（版本控制）
- btop（系统监控）

### 练习 4：系统信息收集

编写一个 shell 脚本，收集并显示：

- 系统版本信息
- CPU 和内存信息
- 磁盘使用情况
- 当前运行的进程数量

### 练习 5：SSH 连接实践

完成以下 SSH 相关任务：

1. **SSH 服务配置：**

   - 在虚拟机中安装并启动 SSH 服务
   - 确认 SSH 服务正在运行
   - 查看虚拟机的 IP 地址

2. **远程连接测试：**

   - 从主机系统 SSH 连接到虚拟机
   - 在 SSH 会话中执行基本命令
   - 测试文件传输功能

3. **密钥认证配置：**

   - 生成 SSH 密钥对
   - 配置免密登录
   - 测试密钥认证是否生效

4. **文件传输练习：**
   - 使用 SCP 从主机向虚拟机传输文件
   - 使用 SCP 从虚拟机下载文件到主机
   - 传输一个目录及其所有内容

## 课后作业

### 作业 1：Linux 命令熟练度训练

完成以下任务：

1. 熟练掌握至少 20 个常用 Linux 命令
2. 编写一个文件备份脚本
3. 练习使用 vim 编辑器编写代码
4. 配置个性化的 shell 环境（别名、提示符等）

### 作业 2：开发环境完整配置

根据个人需求配置完整的开发环境：

1. 安装和配置所需的编程语言环境
2. 配置版本控制系统
3. 安装和配置 IDE 或编辑器
4. 设置开发项目目录结构
5. 编写环境验证和自动化配置脚本

### 作业 3：系统维护脚本

编写一个系统维护脚本，包含：

1. 自动更新系统和软件包
2. 清理临时文件和无用的包
3. 检查系统资源使用情况
4. 备份重要配置文件
5. 生成系统状态报告

### 作业 4：SSH 远程管理实践

完成以下 SSH 高级应用任务：

1. **SSH 安全配置：**

   - 修改 SSH 默认端口
   - 禁用密码认证，仅允许密钥认证
   - 配置防火墙规则
   - 设置 SSH 登录日志监控

2. **SSH 自动化脚本：**

   - 编写批量 SSH 连接脚本
   - 实现自动文件同步功能
   - 创建远程命令执行脚本
   - 设置 SSH 隧道自动建立

3. **多主机管理：**

   - 配置多个远程主机的 SSH 别名
   - 实现一键连接不同的开发环境
   - 设置跳板机连接方案
   - 配置 SSH 代理转发

4. **RoboMaster 应用场景：**
   - 模拟远程连接机器人控制系统
   - 实现代码自动部署到远程设备
   - 配置日志文件远程收集
   - 设置远程调试环境

## 学习检查点

完成本节课后，请确保你能够：

- [ ] 理解 Linux 系统的基本概念和特点
- [ ] 独立安装和基本配置 Ubuntu 系统
- [ ] 熟练使用命令行进行文件和目录操作
- [ ] 掌握基本的文本编辑工具使用
- [ ] 使用包管理器安装和管理软件
- [ ] 进行基本的系统管理和故障排除
- [ ] 配置和使用 SSH 远程连接
- [ ] 实现 SSH 密钥认证和文件传输
- [ ] 配置 RoboMaster 开发环境
- [ ] 编写简单的 shell 脚本

## OS 课程总结

### 技能成果

- 掌握了 Linux 系统的基本操作
- 具备了命令行工具的使用能力
- 建立了完整的开发环境
- 为后续 RoboMaster 项目开发做好准备

### 下一步学习方向

- 深入学习 Shell 脚本编程
- 掌握更多系统管理技能
- 学习网络配置和服务器管理
- 了解 Linux 内核和系统原理
- 学习容器技术（Docker）

### 在 RoboMaster 中的应用

- 机器人系统部署和维护
- 开发环境的配置和管理
- 自动化脚本的编写
- 系统性能优化和监控
- 远程调试和问题排查
- SSH 远程控制机器人系统
- 代码远程部署和更新
- 日志文件远程收集和分析

## 扩展阅读

- [Ubuntu 官方文档](https://help.ubuntu.com/)
- [Linux 命令行教程](https://linuxcommand.org/)
- [Bash 脚本编程指南](https://tldp.org/LDP/Bash-Beginners-Guide/html/)
- [Linux 系统管理员指南](https://tldp.org/LDP/sag/html/)
- [SSH 官方文档](https://www.openssh.com/manual.html)
- [SSH 密钥管理最佳实践](https://wiki.archlinux.org/title/SSH_keys)
- [ROS2 Humble 安装指南](https://docs.ros.org/en/humble/Installation.html)

## 常用命令快查表

### 文件操作

```bash
ls          # 列出文件
cd          # 切换目录
pwd         # 显示当前目录
mkdir       # 创建目录
rmdir       # 删除空目录
rm          # 删除文件
cp          # 复制文件
mv          # 移动/重命名
find        # 查找文件
grep        # 搜索文本
```

### 系统信息

```bash
ps          # 进程列表
top         # 系统监控
df          # 磁盘使用
free        # 内存使用
uname       # 系统信息
whoami      # 当前用户
id          # 用户ID信息
```

### 网络工具

```bash
ping        # 网络连通测试
wget        # 文件下载
curl        # 数据传输
ssh         # 远程登录
scp         # 远程文件复制
```
