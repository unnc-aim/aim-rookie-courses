# Linux 命令快速上手（9）--网络配置与服务

## 网络基础概念

### TCP/IP 协议栈

Linux 网络基于 TCP/IP 协议栈，包含以下层次：

- **应用层**：HTTP、FTP、SSH、DNS 等协议
- **传输层**：TCP、UDP 协议
- **网络层**：IP 协议，负责路由和寻址
- **链路层**：以太网、WiFi 等物理网络接口

### 网络接口

```bash
# 查看网络接口
ip addr show                    # 现代命令
ifconfig                        # 传统命令（需要安装 net-tools）

# 常见接口类型：
# lo：回环接口（127.0.0.1）
# eth0/enp0s3：有线网络接口
# wlan0/wlp2s0：无线网络接口
# docker0：Docker 桥接接口
```

### IP 地址和子网

```bash
# IP 地址分类：
# 私有地址范围：
# 10.0.0.0/8      (10.0.0.0 - 10.255.255.255)
# 172.16.0.0/12   (172.16.0.0 - 172.31.255.255)
# 192.168.0.0/16  (192.168.0.0 - 192.168.255.255)

# 特殊地址：
# 127.0.0.1：本地回环地址
# 0.0.0.0：表示所有接口
# 255.255.255.255：广播地址
```

---

## 网络配置命令

### ip 命令（推荐）

现代 Linux 发行版推荐使用 ip 命令：

```bash
# 查看网络接口
ip addr show                    # 显示所有接口信息
ip addr show eth0               # 显示特定接口信息
ip link show                    # 显示链路层信息

# 配置 IP 地址
sudo ip addr add 192.168.1.100/24 dev eth0     # 添加 IP 地址
sudo ip addr del 192.168.1.100/24 dev eth0     # 删除 IP 地址

# 启用/禁用接口
sudo ip link set eth0 up        # 启用接口
sudo ip link set eth0 down      # 禁用接口

# 路由管理
ip route show                   # 显示路由表
sudo ip route add default via 192.168.1.1      # 添加默认路由
sudo ip route add 10.0.0.0/8 via 192.168.1.1  # 添加静态路由
sudo ip route del 10.0.0.0/8   # 删除路由
```

### ifconfig 命令（传统）

```bash
# 安装 net-tools（如果未安装）
sudo apt install net-tools

# 查看网络接口
ifconfig                        # 显示活动接口
ifconfig -a                     # 显示所有接口
ifconfig eth0                   # 显示特定接口

# 配置网络接口
sudo ifconfig eth0 192.168.1.100 netmask 255.255.255.0    # 设置 IP 和子网掩码
sudo ifconfig eth0 up           # 启用接口
sudo ifconfig eth0 down         # 禁用接口
```

---

## 网络连接测试

### ping 命令

测试网络连通性：

```bash
# 基本用法
ping google.com                 # 持续 ping
ping -c 4 google.com           # ping 4 次后停止
ping -i 2 google.com           # 每 2 秒 ping 一次
ping -s 1000 google.com        # 指定数据包大小

# IPv6 ping
ping6 google.com

# 本地网络测试
ping 192.168.1.1               # ping 网关
ping 127.0.0.1                 # ping 本地回环
```

### wget 和 curl 命令

测试 HTTP 连接：

```bash
# wget 命令
wget http://example.com         # 下载网页
wget -O - http://example.com    # 输出到标准输出
wget --spider http://example.com # 只检查连接，不下载

# curl 命令
curl http://example.com         # 获取网页内容
curl -I http://example.com      # 只获取 HTTP 头
curl -o file.html http://example.com  # 保存到文件
curl -v http://example.com      # 详细输出
```

---

## 网络服务查看

### netstat 命令

查看网络连接和端口：

```bash
# 基本用法
netstat -tuln                   # 显示 TCP/UDP 监听端口
netstat -tun                    # 显示 TCP/UDP 连接
netstat -i                      # 显示网络接口统计
netstat -r                      # 显示路由表

# 参数说明：
# -t: TCP 连接
# -u: UDP 连接
# -l: 只显示监听端口
# -n: 显示数字地址而不解析主机名
# -p: 显示进程 ID 和名称
# -a: 显示所有连接

# 常用组合
netstat -tulnp                  # 显示所有监听端口和进程
netstat -an | grep :80          # 查看 80 端口连接
```

### lsof 命令

查看打开的文件和网络连接：

```bash
# 网络相关用法
lsof -i                         # 显示所有网络连接
lsof -i :80                     # 显示 80 端口的连接
lsof -i tcp                     # 显示 TCP 连接
lsof -i udp                     # 显示 UDP 连接
lsof -i @192.168.1.100         # 显示特定 IP 的连接

# 进程相关
lsof -p PID                     # 显示进程打开的文件
lsof -c nginx                   # 显示 nginx 进程的文件
```

---

## DNS 配置

### DNS 配置文件

```bash
# /etc/resolv.conf - DNS 解析配置
cat /etc/resolv.conf

# 示例内容：
# nameserver 8.8.8.8
# nameserver 8.8.4.4
# search example.com
# options timeout:2

# 手动修改 DNS
sudo vim /etc/resolv.conf

# 永久修改 DNS（Ubuntu 18.04+）
sudo vim /etc/systemd/resolved.conf
sudo systemctl restart systemd-resolved
```

### DNS 查询工具

```bash
# nslookup 命令
nslookup google.com             # 查询域名
nslookup 8.8.8.8               # 反向查询

# dig 命令（更强大）
dig google.com                  # 基本查询
dig google.com A                # 查询 A 记录
dig google.com MX               # 查询 MX 记录
dig @8.8.8.8 google.com        # 指定 DNS 服务器查询
dig +trace google.com           # 跟踪查询过程

# host 命令
host google.com                 # 简单查询
host -t MX google.com          # 查询特定记录类型
```

### 本地 DNS 配置

```bash
# /etc/hosts 文件
sudo vim /etc/hosts

# 添加本地解析：
# 192.168.1.100  myserver.local
# 10.0.0.50      robomaster-dev

# 测试本地解析
ping myserver.local
```

---

## 防火墙配置

### UFW 防火墙

UFW (Uncomplicated Firewall) 是 Ubuntu 的简化防火墙工具：

```bash
# 启用/禁用防火墙
sudo ufw enable                 # 启用防火墙
sudo ufw disable                # 禁用防火墙
sudo ufw reset                  # 重置防火墙规则

# 查看状态
sudo ufw status                 # 查看防火墙状态
sudo ufw status verbose         # 详细状态
sudo ufw status numbered        # 带编号的规则列表

# 基本规则
sudo ufw allow ssh              # 允许 SSH
sudo ufw allow 22               # 允许 22 端口
sudo ufw allow 80/tcp           # 允许 TCP 80 端口
sudo ufw allow 1234:5678/tcp    # 允许端口范围
sudo ufw deny 23                # 拒绝 23 端口

# 高级规则
sudo ufw allow from 192.168.1.0/24           # 允许特定网段
sudo ufw allow from 192.168.1.100 to any port 22  # 允许特定 IP 访问 SSH
sudo ufw deny out 25                          # 拒绝出站 25 端口

# 删除规则
sudo ufw delete allow ssh       # 删除规则
sudo ufw delete 1               # 按编号删除规则
```

### iptables 防火墙

iptables 是更底层的防火墙工具：

```bash
# 查看规则
sudo iptables -L                # 列出所有规则
sudo iptables -L -n             # 不解析主机名
sudo iptables -L -v             # 详细信息

# 基本规则
sudo iptables -A INPUT -p tcp --dport 22 -j ACCEPT    # 允许 SSH
sudo iptables -A INPUT -p tcp --dport 80 -j ACCEPT    # 允许 HTTP
sudo iptables -A INPUT -s 192.168.1.0/24 -j ACCEPT   # 允许特定网段

# 保存规则
sudo iptables-save > /etc/iptables/rules.v4

# 恢复规则
sudo iptables-restore < /etc/iptables/rules.v4
```

---

## 网络服务配置

### SSH 服务配置

```bash
# SSH 配置文件
sudo vim /etc/ssh/sshd_config

# 常用配置项：
# Port 22                        # 端口号
# PermitRootLogin no            # 禁止 root 登录
# PasswordAuthentication yes    # 密码认证
# PubkeyAuthentication yes      # 公钥认证

# 重启 SSH 服务
sudo systemctl restart ssh
```

---

## 网络文件系统

### Samba 文件共享

```bash
# 安装 Samba
sudo apt install samba

# 配置 Samba
sudo vim /etc/samba/smb.conf

# 示例配置：
# [shared]
#     path = /home/shared
#     browseable = yes
#     read only = no
#     guest ok = no
#     valid users = user1,user2

# 添加 Samba 用户
sudo smbpasswd -a username

# 重启 Samba 服务
sudo systemctl restart smbd
sudo systemctl restart nmbd

# 客户端连接 (Windows 也可使用图形界面连接)
smbclient //192.168.1.100/shared -U username
sudo mount -t cifs //192.168.1.100/shared /mnt/samba -o username=user1
```

---

## 网络故障排查

### 连接问题诊断

```bash
# 1. 检查物理连接
ip link show                    # 检查网络接口状态

# 2. 检查 IP 配置
ip addr show                    # 检查 IP 地址配置

# 3. 检查路由
ip route show                   # 检查路由表

# 4. 测试本地连接
ping 127.0.0.1                 # 测试本地回环

# 5. 测试网关连接
ping $(ip route | grep default | awk '{print $3}')

# 6. 测试 DNS 解析
nslookup google.com
dig google.com

# 7. 测试外部连接
ping 8.8.8.8                   # 测试到公网 DNS
ping google.com                 # 测试域名解析和连接
```

### 端口和服务诊断

```bash
# 检查端口监听状态
ss -tulnp | grep :80            # 检查 80 端口

# 检查服务状态
sudo systemctl status apache2  # 检查 Apache 状态

# 检查防火墙规则
sudo ufw status
sudo iptables -L

# 测试端口连通性
telnet localhost 80             # 测试本地端口
nc -zv remote_host 80           # 测试远程端口
```
