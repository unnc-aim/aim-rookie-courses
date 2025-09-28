# Linux 命令快速上手（2）--浏览文件系统

> 终于，我们开始正式讨论 Linux 命令使用本身了。为了保证学习效率，你可以再翻开上一章一起看。
> 在这一章节中，你会学习以下命令：pwd, ls, cd, man

**操作小技巧：在输入命令或者参数的时候，可以使用 tab 补全，省去大量麻烦的同时也能保证拼写正确率。比如说如果你的某个文件名又臭又长还被包了好几层目录，你也不想输半天吧？**

## Linux 的文件系统架构

不同于 Windows，其根目录分为多个盘符，每个盘符对应了一个存储器或者一个存储器内的一个分区。Linux 系统的根目录只有大量的其他文件目录。这些内容会被存储在安装 Linux 的硬盘中。如果用户希望使用更多的存储设备，则需要**创建一个目录，并将该设备挂载到这个目录上**。此后，当用户对此文件目录进行操作时，物理层面上将会把数据写入该文件目录所对应的存储器中。

> 为什么要用存储器的称呼？显然你可以使用的存储介质是不限于硬盘的。其他的存储介质包括存储卡（SD，TF，CF-Express...），软盘甚至磁带。如果你使用了“软驱”（和光驱类似，但是插入软盘），你就会发现 A、B 这两个盘符--实际上，他们是专门为软盘预留的。不过到了今天，除了在一些老掉牙的工业设备上操作的工程师，恐怕只有日本的公务员还会使用这种玩意。

Linux 的根目录包括了以下目录：

```bash
bin boot dev etc home lib mnt opt proc root sbin tmp usr var
```

> 眼花缭乱，不是吗？不过接下来的学习中，笔者会一步步地带你挖掘这些目录，让你明白这些目录存储的内容以及他们的作用。

根据发行版和用户操作这些内容会有一定的差异，不过这些目录是一定会包含在内的。**那么，我们的用户根目录在什么位置呢？**

## 知道你在哪：pwd

打开终端，输入`pwd`命令，应该会有类似以下的效果：

```bash
animex@LAPTOP-6966S4BS:~$ pwd
/home/animex
```

> 细心观察会发现，Windows 上分隔父/子目录时使用的是`\`，而 Linux 是`/`。这是由于 Windows 基于 MS-DOS 开发，而`/`键在 MS-DOS 被移作他用（软盘的装载命令？找不到资料了）。Windows CMD 也可以识别`/`，但是 Linux 无法识别`\`。因此，在程序开发的时候统一使用`/`即可。

pwd 命令会输出用户所在的目录的**绝对路径**。绝对路径即以根目录为参考点，目录/文件的所在位置，类似的还有**相对路径**，即以当前终端所操作的文件目录位置为参考点，目标目录/文件的位置。

> 在这里需要提一下，Linux 中，`/`代表着系统根目录，`~`代表用户根目录。因此，使用不同用户登录时，`/`一定会指向特定的位置，即根目录；但是`~`却不同。

是时候讲解根目录的第一个一级目录，`home` 了。这一目录用于存储用户的根目录，结构类似下图：

```txt
home-|--Usr1
     |
     |--Usr2
     |
     |--Usr3
     ...
```

> 你希望的话，可以将用户的根目录放在任何地方，但是后果自负。

**既然知道了你在哪，那么，如何知道你有什么东西呢？**

## 知道你有啥：ls

> 这一节写的又臭又长，因为我必须介绍一些通用的操作。之后的章节会简短地介绍命令用法。

直接输入 ls，可以看到当前目录下的二级目录/文件。 例如：

```bash
animex@LAPTOP-6966S4BS:~$ ls
Control-ECAT-Master-noetic-dev  SOEM  SOES  ecat_servo  linux-tutorial  robomaster_ws
```

这些文件内容仅代表我个人计算机上的状况，而不是通用的。根据个人操作，**根目录下的内容是不相同的**，就像两台电脑的桌面也不会一样。

> 如果你是带有图形化桌面环境的 Linux 发行版，比如虚拟机或者就在硬盘上直接装上了 Linux，你应该还有一些叫做 Desktop，Downloads，Music 等等等等的文件夹，这些是桌面环境在你的用户根目录下创建的。不过对于没有桌面环境的用户而言，这些文件夹自然也就不存在了。
> 看到了那个 linux-tutorial 吗？这篇教程就是被存放在这里的。

还记得在上一讲中笔者提到的 Linux 命令的一般格式吗？这时候，如果**在命令后添加不同的参数**，会发生什么？

```bash
animex@LAPTOP-6966S4BS:~$ ls -a
.              .config      .profile                        SOEM
..             .dotnet      .ros                            SOES
.bash_history  .gitconfig   .sudo_as_admin_successful       ecat_servo
.bash_logout   .landscape   .viminfo                        linux-tutorial
.bashrc        .local       .vscode-server                  robomaster_ws
.cache         .motd_shown  Control-ECAT-Master-noetic-dev

animex@LAPTOP-6966S4BS:~$ ls -l
total 24
drwxr-xr-x  6 animex animex 4096 Jul 28 15:07 Control-ECAT-Master-noetic-dev
drwxr-xr-x 12 animex animex 4096 Jul 28 15:25 SOEM
drwxr-xr-x  9 animex animex 4096 Jul 27 13:25 SOES
drwxr-xr-x  6 animex animex 4096 Jul 26 17:11 ecat_servo
drwxr-xr-x  4 animex animex 4096 Jul 30 16:00 linux-tutorial
drwxr-xr-x  5 animex animex 4096 Jul 25 12:25 robomaster_ws
```

> Linux 文件系统中，"."开头的文件或目录代表着隐藏文件/目录，不过"."以及".."则代表了当前目录以及父目录（上一级目录）。隐藏文件一般是一些配置文件。
> `-a`代表列出所有文件（包括隐藏文件），`-l`代表输出长信息

如你所见，通过添加不同的参数，ls 命令会有不同的返回信息。像是`-a`，`-l`，这样的参数被称为`Option`，格式为`-[Option]`，类似的还有`Long Option`，格式为`--[Long Option]`。
顾名思义，`Long Option`会更长，一般而言是一个或多个英文单词，比如`--all`。

操作会有对应的`Option`以及`Long Option`，或者只有两者其一。

那么，刚刚输出的内容，各个部分分别代表什么呢？

> `total 24`：代表所示文件/目录总占用空间。注意，**占用空间不代表文件大小**，因为文件存储会以**块**为单位，哪怕块没有满，这个块也会被占用。  
> **以下从左到右**：  
> `drwxr-xr-x`：代表文件属性。第一个小格是特殊表示格，表示目录或连结文件等等，`d`表示目录，`l`表示连结文件，`-`则表示这是文件。之后的内容每三个一组，分别代表了文件所有者、文件所有者的组、所有用户的访问权限。`w, x, r`分别代表拥有对文件的写、执行和读的权限。这部分内容将在权限管理的章节被提到。  
> `12, 6, 9`：文件属性右侧的数字代表了文件数量。如果它是文件而不是目录就会是`1`。  
> `animex animex`：左侧内容代表文件所有用户，而右侧内容代表用户所属的组。这一部分内容依旧是会在权限管理的部分提到。  
> `4096`：代表文件大小，以 Byte 为单位。  
> `Jul 28 15:25`：代表建档时间，即创建时间。  
> `linux-tutorial`：代表了文件名。之后你可能还会看见`-->`，左右各有一个文件名。这代表**软链接**，以后的章节会提到。
> 请注意，不同命令的 Option 或者 Long Option，即使使用相同的字母或单词，可能会有不同的含义。

除此之外，尝试在`ls`命令后添加文件路径，你还会得到目标文件路径下所包含的内容。例如：

```bash
animex@LAPTOP-6966S4BS:~$ ls ./SOEM
CMakeLists.txt  Doxyfile  README.md  cmake  drvcomment.txt  oshw  test
ChangeLog       LICENSE   build      doc    osal            soem
```

或者使用绝对路径：

```bash
animex@LAPTOP-6966S4BS:~$ ls /home/animex/SOEM
CMakeLists.txt  Doxyfile  README.md  cmake  drvcomment.txt  oshw  test
ChangeLog       LICENSE   build      doc    osal            soem
```

> 敲黑板：可以使用“操作小技巧”以方便路径输入。如果你不知道“操作小技巧”是什么，请从头看一遍，因为你没有认真看。本章中稍后会介绍的 cd 命令同理。

再试试加上`Option`：

```bash
animex@LAPTOP-6966S4BS:~$ ls /home/animex/SOEM -laF
total 156
drwxr-xr-x 12 animex animex  4096 Jul 28 15:25 ./
drwxr-xr-x 15 animex animex  4096 Jul 30 16:47 ../
drwxr-xr-x  8 animex animex  4096 Jul 28 15:24 .git/
-rw-r--r--  1 animex animex   430 Jul 28 15:24 .gitattributes
...
-rw-r--r--  1 animex animex  3765 Jul 28 15:24 CMakeLists.txt
-rw-r--r--  1 animex animex  3954 Jul 28 15:24 ChangeLog
-rw-r--r--  1 animex animex 79469 Jul 28 15:24 Doxyfile
-rw-r--r--  1 animex animex  1740 Jul 28 15:24 LICENSE
-rw-r--r--  1 animex animex  1133 Jul 28 15:24 README.md
drwxr-xr-x  4 animex animex  4096 Jul 28 15:24 build/
...
```

> `Option`和路径的顺序是无所谓的。`-laF`实际上也等价于`-l -a -F`。如果你乐意甚至可以写成`ls -a /home/animex/SOEM -lF`。
> 一些 Option 可能会有冲突，比如`-a`和`-A`。这种情况下会以某个有更高优先级的命令为准，当然也有可能出错。
> 你也可以干脆直接输`ll`命令。一样的。

一个命令往往会有大量可用参数，那么，如何获得详细的使用指导呢？一个方法是添加`[Command] --help`，比如：

```bash
animex@LAPTOP-6966S4BS:~$ ls --help
Usage: ls [OPTION]... [FILE]...
List information about the FILEs (the current directory by default).
Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.

Mandatory arguments to long options are mandatory for short options too.
  -a, --all                  do not ignore entries starting with .
  -A, --almost-all           do not list implied . and ..
      --author               with -l, print the author of each file...

```

> *The Linux Command Line*的第 15 页，*Table 3-1*列出了部分 ls 常用`Option/Long Option`

篇幅有限，不展示完整内容了。或者使用另一种方式获取指导：`man`命令。

## 我没有性别，只是个 manual：man

> 毕竟计算机只有 0 和 1，没有性别这一说，不是吗？

将你想要获取指导的命令作为参数，使用 man 命令，以使用命令`man man`为例获取`man`的`man`，结果如下：

```bash
man man
```

```txt
MAN(1)                       Manual pager utils                      MAN(1)

NAME
       man - an interface to the system reference manuals

SYNOPSIS
       man [man options] [[section] page ...] ...
       man -k [apropos options] regexp ...
       man -K [man options] [section] term ...
       man -f [whatis options] page ...
       man -l [man options] file ...
       man -w|-W [man options] page ...

DESCRIPTION
       man  is  the system's manual pager.  Each page argument given to man
       is normally the name of a program, utility or function.  The  manual
       page  associated with each of these arguments is then found and dis‐
       played.  A section, if provided, will direct man  to  look  only  in
       that  section of the manual.  The default action is to search in all
       of the available sections following a  pre-defined  order  (see  DE‐
       FAULTS),  and to show only the first page found, even if page exists
       in several sections.

       The table below shows the section numbers of the manual followed  by
       the types of pages they contain.

       1   Executable programs or shell commands
       2   System calls (functions provided by the kernel)

 Manual page man(1) line 1 (press h for help or q to quit)
```

使用你的方向键翻页，底侧有贴心的指引。

## 挪个屁股：cd

> 上一节结束的很快，不是吗？

`cd`用于切换当前终端所处的目录。直接输入`cd`，并且使用`pwd`检查所处的目录，你会得到这样的输出：

```bash
animex@LAPTOP-6966S4BS:~$ cd
animex@LAPTOP-6966S4BS:~$ pwd
/home/animex
animex@LAPTOP-6966S4BS:~$ cd
animex@LAPTOP-6966S4BS:~$ pwd
/home/animex
```

看起来什么都没有发生是吗？其实这是因为，输入`cd`代表**进入当前用户的根目录**。那么，如果希望切换到其他位置，应当如何操作？

使用`cd [Directory]`，即可访问相应的目录。`[Directory]`可以是绝对路径，也可以是相对路径。以绝对路径为例：

```bash
animex@LAPTOP-6966S4BS:~$ cd /home/animex/SOEM
animex@LAPTOP-6966S4BS:~/SOEM$ pwd
/home/animex/SOEM
```

> 在这台电脑上，对于用户 animex 而言，`~`与`/home/animex/`等价，你也可以用`~`替换。正如前文所述，`~`代表用户根目录

以相对路径为例，输入：

```bash
animex@LAPTOP-6966S4BS:~$ cd SOEM
```

或者

```bash
animex@LAPTOP-6966S4BS:~$ cd ./SOEM
```

都可以进入该文件夹。因为`SOEM`用户根目录下的一个一级目录。

如果希望回退到父目录，输入`cd ..`即可，也可以使用父目录的绝对路径。遇到需要跨过多层目录是可以使用`cd ../../..`的方式，这代表回退三层路径--根据你的需要调整命令中`/`以及`.`的数量即可。例如：

```bash
animex@LAPTOP-6966S4BS:~/SOEM/build/test$ pwd
/home/animex/SOEM/build/test
animex@LAPTOP-6966S4BS:~/SOEM/build/test$ cd ..
animex@LAPTOP-6966S4BS:~/SOEM/build$ pwd
/home/animex/SOEM/build
animex@LAPTOP-6966S4BS:~/SOEM/build$ cd ../../..
animex@LAPTOP-6966S4BS:/home$ pwd
/home
```

**以上就是本章内容，在这一章后，你已经具备了浏览 Linux 文件系统的基本能力了。你可以试一试自己探索根目录其他文件夹的一些内容--当然，不要瞎操作。**

> 以后的章节里我会尽量简短地介绍其他命令，因为你已经对 Linux 的操作规则已经有了基础的了解。
