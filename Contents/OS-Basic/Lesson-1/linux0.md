# Linux 命令快速上手（0）--关于 Linux

## 什么是 Linux？为什么会出现 Linux？

> 叠甲：Linux 史这一部分内容争议较多，并且没有十分清晰的记载。三十年的老烂账了，Linus Torvalds 都还不一定记得。

在上世纪 70 年代，**Unix**系统以及各种**类 Unix 系统**开始崛起。尽管这些系统有着强大的功能以及较强的易用性，但是他们是非开放的，由于知识产权原因，其使用会受到大量的限制。于是，**Linus Torvalds**在 1991 年编写了 Linux 内核以替代 MINIX 这一类 Unix 系统的内核，并在此之上运行用于 MINIX 的软件。然而，这样的作法依然会受到限制--这会使得 Linux 无法应用于商业用途。而从 1984 年就已经立项的**GNU**项目，本**自由软件**的精神，开发了一系列兼容 Unix 内核的软件--在今天，GNU 包括了其特有的 Shell、Gnome 桌面环境、gcc 编译器等应用，这些应用对于程序的运行都是十分重要的--却缺乏一个合适的内核。因此，Linus Torvalds 和 GNU 之父 Richard Matthew Stallman 一拍即合，修改了 Linux 的使用协议，让 Linux 内核改用 GNU 软件。尽管一开始的 Linux 内核并不完善，但是在庞大的社区支持下，Linux 不断更新迭代，同时，不同的公司/组织/个人也在发行各类装有不同特色应用的 Linux**发行版（Distrobution）**，使得 Linux 得到了广泛的应用。

> 实际上，GNU 项目中的《GNU 通用公共许可协议》被大量的开源软件所使用，对今日的开源软件社区有着深厚的影响。
> 对于 Linux 是否应当被成为 GNU/Linux 这一点，开源社区有着巨大的争议。包括 GNU 之父支持者 Richard 认为，Linux 的众多发行版使用了 GNU 应用，并且他们都是至关重要的--在后面的学习中你也会体会到这一点。
> 如果你对计算机硬件很感兴趣，那你一定听过*Nvidia f\*\*k you*这句“至理名言”。实际上，这是 Linus 在一次对大学的访问中，当学生提到 Nvidia 显卡对 Linux 系统的兼容性差这一问题时，Linus 为表达对 Nvidia 公司的不满所言。

总而言之，Linux 系统是一个**类 Unix 系统**。一个类 Unix 系统主要包含两部分：**Kernal 和 Shell**。前者为底层硬件的具体操作提供了途径，而后者方便用户控制系统，只需要在 Shell 中输入相应的命令，就可以对系统进行操作。

> 你需要学的就是通过 Shell 操控那个内核。内核在干什么？管他呢。

## 为什么要使用 Linux？为什么不用 Windows？

~~答：比 Windows 强大~~

因为 Linux 有着庞大的开源社区作为支持，并且是开源的，使用者可以自由的配置各种各样的应用。比如，**ROS（Robot operating system）**，也就是在 AIM 战队的各位，用于使各种程序合作运行的框架，就是（只能）运行在 Linux 上的。同时，配置开发环境时，Linux 往往比 Windows 更加简便。以**Debian**系的 Linux 发行版（包括你将要学习的 Ubuntu）为例，安装某一程序往往只需要输入：

```bash
sudo apt install [program]
```

就完成了。

是的。apt 甚至会帮你同时安装完成依赖项。缺少依赖了？还是使用 `apt install` 一句解决~~而 Windows 用户甚至会因为在打游戏的时候缺少 DirectX 花上半天的功夫装驱动~~。

不仅如此，Linux 运行程序的速度比 Windows 更快。比如在 Blander 上进行渲染，Windows 用户会多花 30%的时间，而在开发环境 ESP32 中，根据乐鑫（ESP32 的厂商）的说法，编译相同程序时，Linux 用户只需要使用 Windows 用户一半的时间。

> Steam Deck 使用的就是 Arch Linux。

除此之外，Linux 内核是可以根据用户的需求进行定制的。比如，在一些对实时性需求较高（工业生产，机器人......）的情境下，Linux 用户可以在内核添加功能，自行编译一个符合自己需求的内核。

最后，Linux 占用的资源更少。当 Windows11 一开机就会使用 8G 的内存空间时......对于 Ubuntu 发行版，即使使用被认为更占用资源的 KDE 桌面环境时仅会使用不到 2G 的内存空间--而不使用桌面环境则会使得你的内存占用远低于 1G。通过删去内核中不必要的功能，Linux 可以在各种低性能的嵌入式系统中运行。

> “‘当 Windows11 一开机就会使用 8G 的内存空间时’没这么多，windows 占多少内存也是看你本来有多少内存的，4G 内存它就只占 2G 了” --mxdh
> 有一个玩笑就是在面包机里用 Linux 系统。
> Ubuntu 默认使用 Gnome 桌面环境，对，就是 GNU 的一部分。使用 KDE 桌面环境、基于 Ubuntu 的发行版被成为 Kubuntu，类似的还有 Lubuntu 和 Mint，当然他们除了桌面环境可能会有变化外也会有一些其他的自带工具。
> Linus 非常讨厌 Debian，因为早期 Debian 十分难以安装。不过对于现在的 Ubuntu 而言，你会有直观的图形安装环境--相信我，它会比安装 Windows 更简单。想要体会一下 1999 年的 Debian 安装有多难受可以观看视频：<https://www.bilibili.com/video/BV1hf4y1N7BS/?spm_id_from=333.337.search-card.all.click&vd_source=271e405cd9556c7b3c77c6d0da84fb3b>
> 对了，Ubuntu 这个发行版是基于 Debian 的一个发行版，这些基于 Debian 的发行版 ~~以及基于 Debian 发行版的发行版或者基于 Debian 发行版的发行版的发行版%#￥！#@%\*&~~ 被成为 Debian 系。类似的还有 REHL 系，Arch 系等。前文提到的 apt 则是 Debian 系 Linux 的一个特有的**包管理系统**，之后的篇章会提到。
> 顺带一提，ROS2 可以运行在 Windows 上，但是为了~~白嫖他人的劳动成果~~使用更多 ROS 社区上已完成的功能包、加快开发进度，我们依然使用 ROS noetic。

**总而言之，希望大家可以享受学习 Linux 的过程。**

~~真的会有人享受这玩意？~~
