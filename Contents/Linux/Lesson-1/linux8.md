# Linux 命令快速上手（8）--进程管理与系统监控

## 进程基础概念

### 什么是进程

**进程（Process）** 是正在运行的程序实例，具有以下特点：

- **独立的内存空间**：每个进程都有自己的内存地址空间
- **进程标识符（PID）**：系统为每个进程分配唯一的 ID
- **进程状态**：运行、就绪、阻塞、僵尸等状态
- **父子关系**：进程之间存在层次关系
- **资源管理**：CPU 时间、内存、文件句柄等资源的使用

### 进程状态

```bash
# 常见进程状态
R (Running)     # 正在运行或可运行
S (Sleeping)    # 可中断睡眠状态
D (Disk sleep)  # 不可中断睡眠状态
T (Stopped)     # 停止或被追踪
Z (Zombie)      # 僵尸进程
```

### 进程层次结构

Linux 系统中的进程形成树状结构：

- **init 进程**：系统启动后的第一个进程（PID=1）
- **父进程**：创建其他进程的进程
- **子进程**：由父进程创建的进程
- **孤儿进程**：父进程已终止的进程
- **僵尸进程**：已终止但父进程未回收的进程

---

## 查看进程信息

### ps 命令

最基本的进程查看命令：

```bash
# 基本用法
ps                      # 显示当前终端的进程
ps -e                   # 显示所有进程
ps -f                   # 显示完整格式
ps -u username          # 显示特定用户的进程

# 常用组合
ps aux                  # 显示所有进程详细信息
ps -ef                  # 另一种全进程显示格式
ps -ejH                 # 显示进程树
ps -eLf                 # 显示线程信息

# 自定义输出格式
ps -eo pid,ppid,cmd,pcpu,pmem,time --sort=-pcpu
# 按 CPU 使用率排序显示进程信息
```

**ps aux 输出字段说明：**

```bash
USER    # 进程所有者
PID     # 进程 ID
%CPU    # CPU 使用百分比
%MEM    # 内存使用百分比
VSZ     # 虚拟内存大小（KB）
RSS     # 物理内存大小（KB）
TTY     # 控制终端
STAT    # 进程状态
START   # 启动时间
TIME    # CPU 时间
COMMAND # 命令行
```

### top 命令

实时显示系统进程信息：

```bash
# 启动 top
top

# top 界面操作：
q           # 退出
h           # 显示帮助
k           # 终止进程
r           # 调整进程优先级
P           # 按 CPU 使用率排序
M           # 按内存使用率排序
T           # 按 CPU 时间排序
u           # 显示特定用户的进程
1           # 显示/隐藏 CPU 核心信息
```

**top 显示信息解读：**

```bash
# 第一行：系统概况
# load average: 1分钟、5分钟、15分钟平均负载

# 第二行：任务统计
# Tasks: 总数 total, 运行 running, 睡眠 sleeping, 停止 stopped, 僵尸 zombie

# 第三行：CPU 使用率
# %Cpu(s): us用户空间, sy系统空间, ni优先级调整, id空闲, wa等待IO, hi硬中断, si软中断

# 第四行：内存使用
# KiB Mem: total总内存, free空闲, used已用, buff/cache缓存

# 第五行：交换空间
# KiB Swap: total总交换, free空闲, used已用, cached缓存
```

### htop 命令

htop 是 top 的增强版，提供更友好的界面：

```bash
# 安装 htop
sudo apt install htop

# 启动 htop
htop

# htop 特点：
# - 彩色显示
# - 支持鼠标操作
# - 显示进程树
# - 更直观的系统信息展示
```

### btop 命令

btop 是一个现代化的系统监控工具，具有丰富的功能和美观的界面：

```bash
# 安装 btop
sudo apt install btop
# 启动 btop
btop
# btop 特点：
# - 现代化的用户界面
# - 支持鼠标操作
# - 丰富的系统信息展示
# - 可自定义主题和布局
```

---

## 进程控制

### 终止进程

```bash
# kill 命令
kill PID                # 发送 TERM 信号（温和终止）
kill -9 PID             # 发送 KILL 信号（强制终止）
kill -15 PID            # 发送 TERM 信号（同默认）
kill -STOP PID          # 暂停进程
kill -CONT PID          # 继续进程

# killall 命令
killall process_name    # 终止所有指定名称的进程
killall -9 process_name # 强制终止

# pkill 命令
pkill pattern           # 根据模式终止进程
pkill -u username       # 终止特定用户的所有进程
pkill -f "python.*script.py"  # 根据完整命令行匹配
```

### 信号类型

```bash
# 常用信号
SIGTERM (15)    # 请求进程终止（默认）
SIGKILL (9)     # 立即终止进程（无法被忽略）
SIGSTOP (19)    # 暂停进程
SIGCONT (18)    # 继续执行进程
SIGHUP (1)      # 挂起信号（重新加载配置）
SIGINT (2)      # 中断信号（Ctrl+C）
SIGQUIT (3)     # 退出信号（Ctrl+\）

# 查看所有信号
kill -l
```

---

## 后台进程管理

### 后台运行

```bash
# 启动后台进程
command &               # 在后台运行命令

# 查看后台任务
jobs                    # 显示当前 shell 的后台任务
jobs -l                 # 显示任务的 PID

# 前后台切换
fg                      # 将后台任务切换到前台
fg %1                   # 将任务 1 切换到前台
bg                      # 将暂停的任务在后台继续运行
bg %1                   # 将任务 1 在后台继续运行

# 暂停和继续
Ctrl+Z                  # 暂停当前前台进程
Ctrl+C                  # 终止当前前台进程
```

### nohup 命令

让进程在用户退出后继续运行：

```bash
# 基本用法
nohup command &         # 后台运行，输出重定向到 nohup.out
nohup command > output.log 2>&1 &  # 指定输出文件

# 示例
nohup python script.py &
nohup ./long_running_script.sh > script.log 2>&1 &
```

### disown 命令

将任务从当前 shell 的任务列表中移除：

```bash
# 启动后台任务
command &

# 移除任务
disown %1               # 移除任务 1
disown -a               # 移除所有任务
disown -h %1            # 标记任务 1 为不接收 SIGHUP 信号
```

### screen 和 tmux

```bash
# screen 命令
screen                  # 启动一个新的 screen 会话
screen -S session_name  # 创建命名会话
screen -r session_name  # 恢复会话
screen -ls              # 列出所有会话
Ctrl+A D                # 分离当前会话
```

```bash
# tmux 命令
tmux                    # 启动 tmux 会话
tmux new -s session_name # 创建命名会话
tmux attach -t session_name # 恢复会话
tmux ls                 # 列出所有会话
Ctrl+B D                # 分离当前会话
```

---

## 系统监控

### 系统负载监控

```bash
# uptime 命令
uptime                  # 显示系统运行时间和负载

# w 命令
w                       # 显示当前登录用户和系统负载

# 负载平均值解释：
# 1.0 表示系统完全利用
# > 1.0 表示系统过载
# < 1.0 表示系统有空闲
```

### CPU 监控

```bash
# vmstat 命令
vmstat                  # 显示系统统计信息
vmstat 1                # 每秒显示一次
vmstat 1 10             # 每秒显示一次，共 10 次

# sar 命令（需要安装 sysstat）
sudo apt install sysstat
sar -u 1                # 每秒显示 CPU 使用率
sar -u 1 10             # 每秒显示 CPU 使用率，共 10 次
```

### 内存监控

```bash
# free 命令
free                    # 显示内存使用情况
free -h                 # 人类可读格式
free -m                 # 以 MB 为单位显示
free -s 1               # 每秒更新一次

# /proc/meminfo 文件
cat /proc/meminfo       # 详细内存信息

# 内存使用率计算
# 实际使用率 = (total - available) / total * 100%
```

---

## 系统服务管理

### systemctl 命令

systemd 系统和服务管理器：

```bash
# 服务控制
sudo systemctl start service_name      # 启动服务
sudo systemctl stop service_name       # 停止服务
sudo systemctl restart service_name    # 重启服务
sudo systemctl reload service_name     # 重新加载配置
sudo systemctl enable service_name     # 设置开机自启
sudo systemctl disable service_name    # 取消开机自启

# 查看服务状态
systemctl status service_name          # 查看服务状态
systemctl is-active service_name       # 检查服务是否运行
systemctl is-enabled service_name      # 检查服务是否开机自启

# 列出服务
systemctl list-units --type=service    # 列出所有服务
systemctl list-units --type=service --state=running  # 列出运行中的服务
systemctl list-unit-files --type=service  # 列出所有服务文件
```

### service 命令

传统的服务管理命令：

```bash
# 基本用法
sudo service service_name start        # 启动服务
sudo service service_name stop         # 停止服务
sudo service service_name restart      # 重启服务
sudo service service_name status       # 查看服务状态

# 列出所有服务
service --status-all                   # 显示所有服务状态
```

---

## 日志监控

### 系统日志

```bash
# 查看系统日志
sudo tail -f /var/log/syslog         # 实时查看系统日志
sudo tail -f /var/log/messages       # 系统消息日志
sudo tail -f /var/log/auth.log       # 认证日志
sudo tail -f /var/log/kern.log       # 内核日志

# journalctl 命令（systemd 日志）
journalctl                           # 查看所有日志
journalctl -f                        # 实时跟踪日志
journalctl -u service_name           # 查看特定服务日志
journalctl --since "2024-01-01"     # 查看指定时间后的日志
journalctl --until "2024-01-02"     # 查看指定时间前的日志
journalctl -p err                    # 只显示错误级别的日志
```

### 应用程序日志

```bash
# Web 服务器日志
sudo tail -f /var/log/apache2/access.log
sudo tail -f /var/log/apache2/error.log
sudo tail -f /var/log/nginx/access.log
sudo tail -f /var/log/nginx/error.log

# 数据库日志
sudo tail -f /var/log/mysql/error.log
sudo tail -f /var/log/postgresql/postgresql-*.log

# 应用程序自定义日志
tail -f /path/to/application.log
```
