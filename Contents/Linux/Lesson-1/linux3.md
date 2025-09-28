# Linux 命令快速上手（3）--操作/管理文件

> 上一章节的学习后，你已经了解了如何通过命令浏览 Linux 系统的文件。在这一讲当中，你将学习如何创建/删除你的目录/文件，以及如何压缩/解压缩常见格式的压缩包。

## 创建目录和文件：mkdir，touch

`mkdir`命令使用方式为 ：

```bash
mdkir [Option] &{Directory}
```

`touch`使用方式类似：

```bash
touch [Option] &{File}
```

例如：

```bash
animex@LAPTOP-6966S4BS:~$ cd
animex@LAPTOP-6966S4BS:~$ mkdir linux_example
animex@LAPTOP-6966S4BS:~$ cd linux
linux-tutorial/ linux_example/
animex@LAPTOP-6966S4BS:~$ cd linux_example/
animex@LAPTOP-6966S4BS:~/linux_example$ ls
animex@LAPTOP-6966S4BS:~/linux_example$ touch test01
animex@LAPTOP-6966S4BS:~/linux_example$ ls
test01
animex@LAPTOP-6966S4BS:~/linux_example$
```

如上所示，输入`mkdir linux_example`后，我在当前目录下创建了一个叫做`linux_example`，进入该目录后又创建了一个叫做`test01`的文件。**这个文件是没有文件类型的，因为后面并没有后缀**。对于这样的文件，我们可以使用一些文本编辑器打开，本章节后面的部分将会提到如何对这些文件进行编辑。

`mkdir`和`touch`也可以利用**绝对路径**或者**更长的相对路径**进行文件/目录的创建，只需在输入`mkdir`或`touch`后输入目标路径，加上分隔符`/`，再输入想创建的文件/目录名即可。

但是，有两点是需要大家注意的：

> 1、Linux 系统中**一定不要创建任何带有中文，空格以及各类特殊字符的文件/目录**，因为这样会给你带来很多不可预测的麻烦。你可以使用"-"或者"\_"来代表空格，就像我做的一样。
> 2、如果你在创建文件目录的时候想同时创建一个它的子目录，请使用`-p`的 Option。例如：
>
> ```bash
> animex@LAPTOP-6966S4BS:~$ mkdir workspace/src
> mkdir: cannot create directory ‘workspace/src’: No such file or directory
> animex@LAPTOP-6966S4BS:~$ mkdir -p workspace/src
> animex@LAPTOP-6966S4BS:~$ ls workspace
> src
> animex@LAPTOP-6966S4BS:~$
> ```
>
> 在没有 Option 的情况下，系统会认为你希望在`workspace`文件目录中再创建一个新的目录，而不是创建一个带有一个二级目录的目录。

## 删除文件：rm

> 这是一个极度危险的命令。对于 Linux 而言，Linux 会假定任何一个使用 rm 命令的人足够聪明而不会因为使用这条命令导致系统崩溃。
> 不同于回收站机制，rm 命令是彻底删除而不是放入一个缓存区域。

`rm`的使用方式依旧和`mkdir`、`touch`类似：

```bash
rm [Option] &{File/Directory}
```

一般而言，大家最常用的命令是`rm -rf`，其中`-r`代表**递归**，即删除该目录下的其他目录；`-f`代表强制删除。例如以下操作：

```bash
animex@LAPTOP-6966S4BS:~$ rm linux_example/
rm: cannot remove 'linux_example/': Is a directory
animex@LAPTOP-6966S4BS:~$ ls linux_example/
src  test01
animex@LAPTOP-6966S4BS:~$ rm -r linux_example/
animex@LAPTOP-6966S4BS:~$
```

> rm 命令的使用一定要慎之又慎。一大 Linux 笑话就算是`sudo rm -rf /*`，这个命令的意思是**删除根目录下所有文件**。但是，对于 WSL 用户而言，WSL 在设计上将 Windows 磁盘挂载在了`/mnt/x`（小写字母 x 代表了 Windows 文件管理系统下的盘符），这一操作甚至会让 Windows 丢失文件以及崩溃。
>
> > 忽然意识到笔者并未提到`*`的作用。这里可以直接参考 <https://laigedemo.com/linux_shell/wildcard_asterisk.html>。
