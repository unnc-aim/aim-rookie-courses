# Linux 命令快速上手（7）--文本编辑与处理

## Vim 编辑器详解

### Vim 简介

**Vim (Vi iMproved)** 是一个功能强大的文本编辑器，具有以下特点：

- **模式化编辑**：不同模式具有不同功能
- **高效操作**：大量快捷键和命令组合
- **高度可定制**：支持插件和配置
- **无处不在**：几乎所有 Linux 系统都预装
- **轻量级**：占用资源少，启动快速

### Vim 的三种主要模式

#### 1. 普通模式（Normal Mode）

进入 Vim 后的默认模式，用于移动光标和执行命令：

```bash
# 启动 vim
vim filename.txt

# 普通模式下的基本操作：
h, j, k, l      # 左、下、上、右移动光标
w, b            # 向前/向后移动一个单词
0, $            # 移动到行首/行尾
gg, G           # 移动到文件开头/结尾
Ctrl+f, Ctrl+b  # 向前/向后翻页
```

#### 2. 插入模式（Insert Mode）

用于编辑文本内容：

```bash
# 进入插入模式的方式：
i               # 在光标前插入
a               # 在光标后插入
o               # 在下一行插入
O               # 在上一行插入
I               # 在行首插入
A               # 在行尾插入

# 退出插入模式：
Esc             # 返回普通模式
```

#### 3. 命令模式（Command Mode）

用于执行文件操作和高级命令：

```bash
# 进入命令模式：
:               # 从普通模式按冒号进入

# 常用命令：
:w              # 保存文件
:q              # 退出
:wq             # 保存并退出
:q!             # 不保存强制退出
:x              # 保存并退出（同 :wq）
```

---

## Vim 基本操作

### 文本编辑

```bash
# 删除操作
x               # 删除光标下的字符
dw              # 删除一个单词
dd              # 删除当前行
D               # 删除到行尾
d$              # 删除到行尾（同 D）
d0              # 删除到行首

# 复制操作
yy              # 复制当前行
yw              # 复制一个单词
y$              # 复制到行尾

# 粘贴操作
p               # 在光标后粘贴
P               # 在光标前粘贴

# 撤销和重做
u               # 撤销上一次操作
Ctrl+r          # 重做（撤销的撤销）
```

### 查找和替换

```bash
# 查找
/pattern        # 向前查找
?pattern        # 向后查找
n               # 查找下一个
N               # 查找上一个

# 替换
:s/old/new/     # 替换当前行第一个匹配
:s/old/new/g    # 替换当前行所有匹配
:%s/old/new/g   # 替换整个文件所有匹配
:%s/old/new/gc  # 替换时需要确认
```

### 高级编辑技巧

```bash
# 选择文本（可视模式）
v               # 字符选择模式
V               # 行选择模式
Ctrl+v          # 块选择模式

# 缩进
>>              # 向右缩进当前行
<<              # 向左缩进当前行
=               # 自动缩进

# 大小写转换
~               # 切换光标下字符的大小写
gU              # 转换为大写
gu              # 转换为小写
```

---

## Vim 配置

### 基本配置文件

创建和编辑 Vim 配置文件：

```bash
# 编辑用户配置文件
vim ~/.vimrc

# 基本配置示例：
set number          " 显示行号
set relativenumber  " 显示相对行号
set tabstop=4       " Tab 宽度为 4
set shiftwidth=4    " 缩进宽度为 4
set expandtab       " 将 Tab 转换为空格
set autoindent      " 自动缩进
set smartindent     " 智能缩进
set hlsearch        " 高亮搜索结果
set incsearch       " 增量搜索
set ignorecase      # 搜索时忽略大小写
set smartcase       " 智能大小写匹配
syntax on           " 启用语法高亮
set ruler           " 显示光标位置
set showcmd         " 显示命令
set wildmenu        " 命令补全菜单
```

---

## 其他文本编辑器

### VS Code 编辑器

安装和使用 VS Code：

```bash
# 使用 apt 安装 (不要使用snap)
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
sudo install -o root -g root -m 644 packages.microsoft.gpg /etc/apt/trusted.gpg.d/
echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/trusted.gpg.d/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" | sudo tee /etc/apt/sources.list.d/vscode.list
sudo apt update
sudo apt install code

# 启动 VS Code
code filename.txt
code .              # 打开当前目录。如果是在 VS Code SSH Session 下的命令行窗口运行，会直接在你本机上打开一个新的远程目录 Session，有妙用
```

**VS Code 特点：**

- 图形界面，易于使用
- 语法高亮和智能补全
- 丰富的插件生态系统
- 集成终端和 Git 工具
- 支持远程开发

---

## 文本处理工具

### cat 命令

显示文件内容：

```bash
# 显示文件内容
cat filename.txt

# 显示行号
cat -n filename.txt

# 显示非打印字符
cat -A filename.txt

# 合并多个文件
cat file1.txt file2.txt > combined.txt

# 创建文件
cat > newfile.txt
# 输入内容，Ctrl+D 结束
```

### head 和 tail 命令

查看文件开头和结尾：

```bash
# 显示前 10 行（默认）
head filename.txt

# 显示前 n 行
head -n 20 filename.txt

# 显示后 10 行（默认）
tail filename.txt

# 显示后 n 行
tail -n 20 filename.txt

# 实时监控文件变化
tail -f logfile.txt
```

### less 和 more 命令

分页查看文件：

```bash
# 分页查看文件
less filename.txt
more filename.txt

# less 命令中的操作：
# Space: 下一页
# b: 上一页
# /pattern: 搜索
# q: 退出
# G: 到文件末尾
# g: 到文件开始
```

### grep 命令详解

强大的文本搜索工具：

```bash
# 基本搜索
grep "pattern" filename.txt

# 常用参数
grep -i "pattern" file          # 忽略大小写
grep -n "pattern" file          # 显示行号
grep -v "pattern" file          # 反向匹配（不包含）
grep -r "pattern" directory/    # 递归搜索目录
grep -l "pattern" *.txt         # 只显示匹配的文件名
grep -c "pattern" file          # 计算匹配行数

# 正则表达式
grep "^start" file              # 以 start 开头的行
grep "end$" file                # 以 end 结尾的行
grep "[0-9]" file               # 包含数字的行
grep "colou?r" file             # ? 表示前面字符可选
```

### sed 流编辑器

用于文本替换和处理：

```bash
# 基本替换
sed 's/old/new/' filename.txt                  # 替换每行第一个匹配
sed 's/old/new/g' filename.txt                 # 替换所有匹配
sed 's/old/new/gi' filename.txt                # 忽略大小写替换

# 行操作
sed '5d' filename.txt                          # 删除第 5 行
sed '2,5d' filename.txt                        # 删除第 2-5 行
sed '/pattern/d' filename.txt                  # 删除匹配的行

# 修改原文件
sed -i 's/old/new/g' filename.txt             # 直接修改文件

# 多个操作
sed -e 's/old/new/g' -e '/pattern/d' file.txt
```

---

## 管道和重定向

### 输出重定向

```bash
# 重定向到文件
command > file.txt              # 覆盖文件
command >> file.txt             # 追加到文件
command 2> error.txt            # 重定向错误输出
command > file.txt 2>&1         # 重定向所有输出

# 丢弃输出
command > /dev/null             # 丢弃标准输出
command 2> /dev/null            # 丢弃错误输出
command > /dev/null 2>&1        # 丢弃所有输出
```

### 输入重定向

```bash
# 从文件读取输入
command < input.txt

# Here Document
cat << EOF > file.txt
这是多行文本
可以包含变量 $USER
EOF
```

### 管道操作

```bash
# 基本管道
command1 | command2

# 常用管道组合
ps aux | grep python            # 查找 python 进程
ls -l | sort -k5 -n            # 按文件大小排序
cat file.txt | wc -l            # 统计行数
history | tail -10              # 显示最近 10 条命令

# 多级管道
cat /var/log/syslog | grep error | head -10 | sort
```

---

## 实际应用示例

### 日志文件分析

```bash
# 分析 Apache 访问日志
# 统计访问最多的 IP
awk '{print $1}' access.log | sort | uniq -c | sort -nr | head -10

# 统计状态码分布
awk '{print $9}' access.log | sort | uniq -c

# 查找错误日志
grep " 404 " access.log
grep " 50[0-9] " access.log
```

### 配置文件处理

```bash
# 提取配置文件中的有效配置（去除注释和空行）
grep -v '^#' /etc/ssh/sshd_config | grep -v '^$'

# 查找特定配置项
grep "^Port" /etc/ssh/sshd_config

# 批量修改配置
sed -i 's/^#Port 22/Port 2222/' /etc/ssh/sshd_config
```

### 代码文件处理

```bash
# 统计代码行数
find . -name "*.py" -exec wc -l {} + | tail -1

# 查找函数定义
grep -n "^def " *.py

# 查找 TODO 注释
grep -r "TODO" --include="*.py" .
```
