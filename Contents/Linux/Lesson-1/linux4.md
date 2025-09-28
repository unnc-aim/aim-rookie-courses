# Linux 命令快速上手（4）--权限

## sudo 和 root 权限

在《Linux 命令快速上手（1）》当中笔者提到了用户`root`的存在。`root`是存在于用户组`root`的一个用户，拥有**整个系统的最高权限**，可以对文件系统进行完全的操作。而`sudo`命令则是**给予`sudoer`用户一个暂时的 root 权限**

> `/etc/sudoers`文件决定了哪个用户可以成为`sudoer`。非`sudoer`无法调用`root`权限。

```bash
animex@LAPTOP-6966S4BS:~$ sudo su
[sudo] password for animex:
root@LAPTOP-6966S4BS:/home/animex# groups
root
root@LAPTOP-6966S4BS:/home/animex#
//groups命令用于查看当前用户所在的组
```

> 强烈不建议各位平时使用`su`用户来运行程序，输入密码的过程实际上是一个 Think twice 的机会。需要使用 sudo 的操作往往会产生不可挽回的影响。

## 用户组

如上文所述，使用`groups`命令可以查看用户所在的组。单个用户可以在不同的组当中，一个组也可也有大量的用户。一些应用会通过组进行文件的权限管理，比如`samba`就需要创建特定的组并将用户加入组中才能正常运行`smb`服务。

> 更多的内容参考 <https://www.runoob.com/linux/linux-user-manage.html>

## 文件所有者

在根目录使用`ll`命令，会得到类似以下结果：

```bash
animex@LAPTOP-6966S4BS:/$ ll
total 2056
drwxr-xr-x  27 root root    4096 Aug 18 12:01 ./
drwxr-xr-x  27 root root    4096 Aug 18 12:01 ../
lrwxrwxrwx   1 root root       7 May 31 05:39 bin -> usr/bin/
drwxr-xr-x   2 root root    4096 May 31 05:46 boot/
drwxr-xr-x  16 root root    3560 Aug 18 12:01 dev/
drwxr-xr-x 140 root root   12288 Aug 18 12:41 etc/
drwxr-xr-x   3 root root    4096 Jul 25 11:05 home/
-rwxrwxrwx   1 root root 1978872 Apr 20 06:55 init*
lrwxrwxrwx   1 root root       7 May 31 05:39 lib -> usr/lib/
lrwxrwxrwx   1 root root       9 May 31 05:39 lib32 -> usr/lib32/
lrwxrwxrwx   1 root root       9 May 31 05:39 lib64 -> usr/lib64/
lrwxrwxrwx   1 root root      10 May 31 05:39 libx32 -> usr/libx32/
drwx------   2 root root   16384 Jul 25 11:05 lost+found/
drwxr-xr-x   2 root root    4096 May 31 05:39 media/
drwxr-xr-x  11 root root    4096 Jul 30 20:41 mnt/
drwxr-xr-x   3 root root    4096 Jul 25 11:30 opt/
dr-xr-xr-x 330 root root       0 Aug 18 12:01 proc/
drwx------   8 root root    4096 Aug  4 14:09 root/
drwxr-xr-x  27 root root     820 Aug 18 12:37 run/
lrwxrwxrwx   1 root root       8 May 31 05:39 sbin -> usr/sbin/
drwxr-xr-x   6 root root    4096 May 31 05:41 snap/
drwxr-xr-x   2 root root    4096 May 31 05:39 srv/
dr-xr-xr-x  11 root root       0 Aug 18 12:01 sys/
drwxrwxrwt  12 root root   12288 Aug 18 12:41 tmp/
drwxr-xr-x  14 root root    4096 May 31 05:40 usr/
drwxr-xr-x  13 root root    4096 May 31 05:41 var/
```

如你所见，绝大部分目录都是只有用户`root`（拥有者）拥有完整访问权限，其他用户拥有执行以及读的权限，但是不可写。而`sys`甚至不可被任何用户修改--从名字就可以看出来为什么这是一个只可读的文件夹。
