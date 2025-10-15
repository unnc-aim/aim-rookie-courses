# Linux 命令快速上手（5）--包管理系统

## 包管理

对于 Debian 系的 Linux 而言，用户可以方便地使用`apt(apt-get)`以及`dpkg`来安装应用。`apt`是建立在`dpkg`之上的管理系统，关系类似于你的安卓手机安装软件会需要安装包（`dpkg`）但是有一个应用市场（`apt`）来给你提供安装包。

### apt/apt-get

> 本质上来讲，`apt`是`apt-get`、`apt-cache`和 `apt-config`中最常用命令选项的集合。Linux 的大量包管理功能被分散到了这三个命令当中，但是这三个命令又包含了许多几乎不会被用到的功能。`apt`则解决了这些问题。

使用命令`sudo apt update`，可以从源更新`apt`的软件清单。可能早些时候你会发现，如果在使用`apt`命令时并未加上`sudo`提权，`apt`将无法使用：

```bash
animex@LAPTOP-6966S4BS:~$ apt update
Reading package lists... Done
W: Unable to read /etc/apt/apt.conf.d/ - DirectoryExists (13: Permission denied)
W: Unable to read /etc/apt/sources.list.d/ - DirectoryExists (13: Permission denied)
W: Unable to read /etc/apt/sources.list - RealFileExists (13: Permission denied)
E: Could not open lock file /var/lib/apt/lists/lock - open (13: Permission denied)
E: Unable to lock directory /var/lib/apt/lists/
W: Problem unlinking the file /var/cache/apt/pkgcache.bin - RemoveCaches (13: Permission denied)
W: Problem unlinking the file /var/cache/apt/srcpkgcache.bin - RemoveCaches (13: Permission denied)
```

一方面`apt`操作相关的文件权限只被`root`所有。上一章当中你应当发现`/etc`文件夹只能被用户`root`所读取。另一方面，由于`apt`依赖`dpkg`，而`dpkg`的文件也是被`root`所有并且访问权限。

`/etc/apt`文件夹中包含了`apt`的一些配置文件。

```bash
animex@LAPTOP-6966S4BS:~$ cd /etc/apt/
animex@LAPTOP-6966S4BS:/etc/apt$ ls
apt.conf.d  auth.conf.d  backup  preferences.d  sources.list  sources.list.d  trusted.gpg  trusted.gpg.d  trusted.gpg~
animex@LAPTOP-6966S4BS:/etc/apt$
```

`sources.list`文件决定了用户使用的源。通过配置这个文件，`apt`在被调用时会访问相应的服务器/镜像站。换源操作网上有大量教程，建议使用清华源和中科大源。

> <https://mirrors.ustc.edu.cn/help/ubuntu.html> 这是中科大镜像站 apt 源的使用说明。由于网络问题，不建议使用官方源，包括安全更新的源。

`sources.list.d`文件夹则包含了用户手动添加的一些源。

通过`apt`，用户可以十分方便地配置大量需要使用的库。比如配置 OpenCV,可以简短地使用`apt`进行安装而不需要下载源码并编译安装。

```bash
animex@LAPTOP-6966S4BS:~$ sudo apt install libopencv
libopencv-apps-dev        libopencv-dev             libopencv-highgui4.2      libopencv-objdetect4.2    libopencv-superres4.2     libopencv-viz-dev
...
```

> 实际上可选择的版本更多，这里展示一小部分。

安装后，在编程的过程中就可以直接`#include`对应的头文件了。

使用`apt upgrade`可以升级目前已安装的包，想要知道安装了哪些包使用`apt list`即可。如果不再需要该包，使用`apt purge`即可卸载。

> `apt autoremove`命令可以卸载不再被需要的库或者包，理想状态下这一命令只会删除不需要的内容，但这仅限于理想状态--笔者出现过使用这一命令导致 ROS 部分功能包崩溃的情况，不过也仅限于此了。修复起来还是相当容易的，重新安装一些功能包即可。

### dpkg

对于一些应用而言，尽管他们不需要繁琐的编译安装，但是这些应用往往会因为一些原因而不在 apt 源当中。开发者会提供一个后缀名为`.deb`的安装包，类似于 Windows 的`.msi`文件。使用命令`dpkg -i xxx.deb`就可以对这个文件进行安装。

> 然而，需要注意的是，apt 安装的过程中会自动帮助用户安装所需的依赖，而 dpkg 并不会。这时候可以使用`-f`来强制安装，之后再为该应用添加依赖。

相对应的，`dpkg -r xxx`可以用来卸载不需要的包，而`dpkg -l`可以列出已安装的包。

> 编译安装部分自行参考 cmake 教程，这里不再深入展开。
