# Linux 命令快速上手（6）--SSH 远程连接

## SSH 基础概念

### 什么是 SSH

**SSH (Secure Shell)** 是一种安全的远程连接协议，具有以下特点：

- 提供加密的网络连接，保护数据传输安全
- 广泛用于远程服务器管理和文件传输
- RoboMaster 中常用于远程控制机器人系统
- 支持命令行操作和图形界面转发

### SSH 的优势

- **数据传输加密**：所有通信内容都经过加密处理
- **密钥认证**：支持公钥/私钥认证，比密码更安全
- **端口转发**：可以建立安全的网络隧道
- **跨平台支持**：Linux、Windows、macOS 都有相应客户端
- **稳定可靠**：连接断开后可以快速重连

### 在 RoboMaster 中的应用

- **远程调试**：从开发机连接到机器人控制器
- **代码部署**：将代码传输到机器人系统
- **日志收集**：远程查看和下载日志文件
- **系统维护**：远程进行系统更新和配置
- **多机协作**：在不同设备间建立安全连接

---

## SSH 服务端配置

### 安装 SSH 服务

在 Ubuntu 系统中安装和配置 SSH 服务：

```bash
# 更新包列表
sudo apt update

# 安装 openssh-server
sudo apt install openssh-server

# 启动 SSH 服务
sudo systemctl start ssh

# 设置开机自启动
sudo systemctl enable ssh

# 查看服务状态
sudo systemctl status ssh
```

### SSH 配置文件

SSH 服务的主要配置文件位于 `/etc/ssh/sshd_config`：

```bash
# 编辑 SSH 配置文件
sudo vim /etc/ssh/sshd_config

# 常用配置项：
# Port 22                           # SSH 端口号
# Protocol 2                        # 使用 SSH 协议版本 2
# PermitRootLogin no               # 禁止 root 用户直接登录
# MaxAuthTries 3                   # 最大认证尝试次数
# PasswordAuthentication yes       # 允许密码认证
# PubkeyAuthentication yes         # 允许公钥认证
# AuthorizedKeysFile .ssh/authorized_keys  # 公钥文件位置
# ClientAliveInterval 60           # 客户端保活间隔
# ClientAliveCountMax 3            # 最大保活次数

# 重启 SSH 服务使配置生效
sudo systemctl restart ssh
```

**重要配置选项说明：**

- `Port`：更改默认端口可以提高安全性
- `PermitRootLogin`：建议设为 `no` 禁止 root 直接登录
- `PasswordAuthentication`：可以设为 `no` 仅允许密钥认证
- `MaxAuthTries`：限制登录尝试次数，防止暴力破解

---

## SSH 客户端使用

### 基本连接语法

```bash
# 基本连接格式
ssh username@hostname_or_ip

# 示例：连接到 IP 为 192.168.1.100 的主机
ssh user@192.168.1.100

# 指定端口连接
ssh -p 2222 username@hostname

# 指定私钥文件
ssh -i ~/.ssh/id_rsa username@hostname

# 带调试信息连接
ssh -v username@hostname
```

### 常用连接选项

```bash
# 执行远程命令后断开连接
ssh username@hostname 'ls -la /home'

# 保持连接活跃（避免超时断开）
ssh -o ServerAliveInterval=60 username@hostname

# 禁用主机密钥检查（仅用于测试）
ssh -o StrictHostKeyChecking=no username@hostname

# 使用压缩传输（网络较慢时有用）
ssh -C username@hostname

# X11 转发（运行图形界面程序）
ssh -X username@hostname
```

### 实践练习：连接虚拟机

#### 步骤 1：获取虚拟机 IP 地址

在虚拟机中执行：

```bash
# 查看网络接口信息
ip addr show

# 或使用 ifconfig（可能需要先安装）
sudo apt install net-tools
ifconfig

# 记录 IP 地址，例如：192.168.1.100
```

#### 步骤 2：从主机连接虚拟机

在主机终端中执行：

```bash
# Windows 用户可以使用 PowerShell 或 Git Bash
ssh your_username@192.168.1.100

# 首次连接会提示确认主机密钥
The authenticity of host '192.168.1.100 (192.168.1.100)' can't be established.
ECDSA key fingerprint is SHA256:...
Are you sure you want to continue connecting (yes/no/[fingerprint])? yes

# 输入用户密码完成登录
```

---

## SSH 密钥认证

### 密钥认证的优势

相比密码认证，密钥认证具有以下优势：

- **安全性更高**：私钥通常比密码更复杂
- **便捷性更好**：配置后无需每次输入密码
- **防暴力破解**：攻击者无法通过穷举破解
- **支持自动化**：脚本可以自动连接

### 生成 SSH 密钥对

```bash
# 生成 RSA 密钥对（传统方式）
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"

# 生成 Ed25519 密钥对（推荐，更安全更高效）
ssh-keygen -t ed25519 -C "your_email@example.com"

# 交互过程：
# Enter file in which to save the key (/home/user/.ssh/id_ed25519): [回车使用默认]
# Enter passphrase (empty for no passphrase): [可选：输入密钥密码]
# Enter same passphrase again: [再次输入密码确认]
```

**密钥文件说明：**

- `~/.ssh/id_ed25519`：私钥文件（保密，不要分享）
- `~/.ssh/id_ed25519.pub`：公钥文件（可以分享）
- 默认位置：`~/.ssh/` 目录

### 配置免密登录

#### 方法 1：使用 ssh-copy-id（推荐）

```bash
# 自动复制公钥到远程主机（仅 Linux/macOS 系统有此命令）
ssh-copy-id username@remote_host

# 指定密钥文件
ssh-copy-id -i ~/.ssh/id_ed25519.pub username@remote_host

# 指定端口
ssh-copy-id -p 2222 username@remote_host
```

#### 方法 2：手动复制公钥

```bash
# 一条命令完成复制
cat ~/.ssh/id_ed25519.pub | ssh username@remote_host 'mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys'

# 设置正确的权限
ssh username@remote_host 'chmod 700 ~/.ssh && chmod 600 ~/.ssh/authorized_keys'
```

#### 方法 3：在远程主机上手动配置

1. 复制本地公钥内容：

```bash
cat ~/.ssh/id_ed25519.pub
```

1. 在远程主机上创建目录并添加公钥：

```bash
# 在远程主机上执行
mkdir -p ~/.ssh
echo "复制的公钥内容" >> ~/.ssh/authorized_keys

# 设置正确的权限
chmod 700 ~/.ssh
chmod 600 ~/.ssh/authorized_keys
```

### 测试密钥认证

```bash
# 测试连接（应该不需要输入密码）
ssh username@remote_host

# 如果仍然要求密码，检查：
# 1. 权限设置是否正确
# 2. 服务器配置是否允许密钥认证
# 3. 私钥文件路径是否正确
```

---

## SSH 客户端配置

### 客户端配置文件

创建和编辑 SSH 客户端配置文件：

```bash
# 编辑用户配置文件
vim ~/.ssh/config

# 设置文件权限
chmod 600 ~/.ssh/config
```

### 配置文件示例

```bash
# 虚拟机配置
Host myvm
    HostName 192.168.1.100
    User myuser
    Port 22
    IdentityFile ~/.ssh/id_ed25519
    ServerAliveInterval 60

# RoboMaster 开发机
Host robomaster-dev
    HostName 10.0.0.50
    User developer
    Port 2222
    IdentityFile ~/.ssh/robomaster_key
    ServerAliveInterval 60

# 跳板机配置
Host jumpserver
    HostName 203.0.113.10
    User admin
    Port 22
    IdentityFile ~/.ssh/jump_key

# 通过跳板机连接内网服务器
Host internal-server
    HostName 192.168.100.10
    User developer
    Port 22
    ProxyJump jumpserver
    IdentityFile ~/.ssh/internal_key
```

### 使用配置别名连接

```bash
# 使用别名连接，无需记住复杂的参数
ssh myvm
ssh robomaster-dev
ssh internal-server
```

### 常用配置选项

```bash
# 主机别名
Host myserver
    # 实际主机名或 IP
    HostName 192.168.1.100
    # 用户名
    User username
    # 端口号
    Port 22
    # 私钥文件路径
    IdentityFile ~/.ssh/id_ed25519
    # 保活设置
    ServerAliveInterval 60
    ServerAliveCountMax 3
    # 压缩传输
    Compression yes
    # 跳板机
    ProxyJump jumpserver
    # X11 转发
    ForwardX11 yes
```

---

## 文件传输

### SCP 命令

SCP (Secure Copy) 基于 SSH 协议进行安全的文件传输：

```bash
# 从本地复制文件到远程主机
scp local_file.txt username@remote_host:/path/to/destination/

# 从远程主机复制文件到本地
scp username@remote_host:/path/to/file.txt ./

# 复制目录（递归）
scp -r local_directory/ username@remote_host:/path/to/destination/

# 指定端口
scp -P 2222 file.txt username@remote_host:/path/

# 显示传输进度
scp -v file.txt username@remote_host:/path/

# 保持文件权限和时间戳
scp -p file.txt username@remote_host:/path/
```

> 实际情况是，还是那句话，当你觉得某个操纵麻烦到逆天时，也说明几乎没人会这么用。
> 所以我们平常会怎么办呢？
> VS Code 的 Remote - SSH 插件可以让你直接在本地 VS Code 中打开远程目录，进行文件编辑和传输，极大简化了操作流程。

---

## 故障排除

### 常见问题和解决方案

#### 1. 连接被拒绝

```bash
# 检查服务是否运行
sudo systemctl status ssh

# 检查端口是否监听
sudo netstat -tlnp | grep :22

# 检查防火墙设置
sudo ufw status
```

#### 2. 权限被拒绝

```bash
# 检查用户是否存在
id username

# 检查密钥权限
ls -la ~/.ssh/
chmod 700 ~/.ssh
chmod 600 ~/.ssh/id_ed25519
chmod 644 ~/.ssh/id_ed25519.pub
chmod 600 ~/.ssh/authorized_keys
```

#### 3. 主机密钥验证失败

```bash
# 移除旧的主机密钥
ssh-keygen -R hostname_or_ip

# 或编辑 known_hosts 文件
vim ~/.ssh/known_hosts
```

#### 4. 连接超时

```bash
# 检查网络连通性
ping remote_host

# 检查端口是否可达
telnet remote_host 22

# 使用 -v 参数调试
ssh -v username@remote_host
```

### 调试技巧

```bash
# 客户端详细调试
ssh -vvv username@remote_host

# 服务端调试模式
sudo /usr/sbin/sshd -d -p 2223

# 检查配置文件语法
sudo sshd -t
```
