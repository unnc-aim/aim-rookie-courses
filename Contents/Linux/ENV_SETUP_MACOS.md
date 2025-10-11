# Parallels 到 Ubuntu 22.04（macOS）完整安装指南

简明步骤：准备 -> 下载 Parallels -> 下载并校验 Ubuntu ISO（注意芯片架构） -> 新建虚拟机（Parallels） -> 安装 Ubuntu -> 安装 Parallels Tools -> 常用配置与排错。

## 0. 为什么在 macOS 上用 Parallels？

当你需要在 mac 上运行另一套完整 Linux 系统，有几种选择：双系统（Boot Camp，只限 Intel）、容器/WSL（不适用于 macOS）和虚拟机。  
Parallels 的优点：集成度高、与 macOS 共享剪贴板与文件夹、图形显示与性能调优方便、界面友好。对于 Apple Silicon 需要使用 ARM 版系统镜像；对于 Intel mac 则使用 x86_64（amd64）镜像。

## 1. 下载、安装与许可 Parallels Desktop

- 如果你很 rich，看这里走流程：
  - 从 Parallels 官方下载合适的版本（确保与 macOS 版本和芯片架构兼容）。
    - 官方站点有试用版或购买选项。
  - 安装：一般为 .dmg -> 将 Parallels 拖到 Applications，首次运行会提示授予权限（系统偏好设置 / 系统设置 → 隐私与安全 → 必要时允许扩展或许可）。
  - 许可密钥：可使用试用期或输入购买的密钥。
- 也可以试试 [学长友情提供资源](http://ug.link/hnrobert-nas/filemgr/share-download/?id=c70ad1d2e1ed4ec2a7aa8696b1a7a7fa)（期限到 25 年 10 月底链接自动关闭）：

注意：无需在 mac 上开启 BIOS 虚拟化（这是 PC 的操作）；但在 macOS 上需允许 Parallels 请求的所有权限（屏幕录制、文件访问、扩展等），否则部分功能受限。

## 2. 下载 Ubuntu 镜像（ISO）

- 官方下载： <https://ubuntu.com/download/alternative-downloads>
- 关键点：根据 Mac 的芯片选择镜像：
  - Apple Silicon：选择 ARM（aarch64 / arm64）版本的 Ubuntu 22.04 LTS（Desktop 的 ARM 版本）。
  - Intel（x86_64）：选择 amd64（x86_64）版本的 Ubuntu 22.04 LTS Desktop。
- 国内镜像（可选）：
  - 清华： <https://mirrors.tuna.tsinghua.edu.cn/ubuntu-releases/>
  - 阿里： <https://mirrors.aliyun.com/ubuntu-releases/>
- 校验 ISO：建议比对 SHA256 校验和以确认下载完整。

## 3. 在 Parallels 中创建虚拟机

1. 打开 Parallels Desktop → File → New（新建）。
2. 选择 “Install Windows or another OS from a DVD or image file” 或者直接把下载好的 ISO 拖入 Parallels 的新建窗口，Parallels 会自动识别。
3. 选择 Ubuntu 22.04 对应的 ISO（确保架构正确：arm64 vs amd64）。
4. 设置虚拟机名称和保存位置（默认放 Applications/Parallels 或你指定的位置）。
5. 配置虚拟机硬件（可后续调整）：
   - CPU：分配 2–4 个核心（或更多，取决于主机资源）。
   - 内存：建议 4GB 或更高（至少 2048 MB，开发/编译建议 8GB+）。
   - 磁盘：20–40GB 动态分配（建议 40GB 起，按需扩展）。
   - 网络：Shared（默认，便于上网）；需局域网访问可选 Bridged。
6. 完成创建并启动虚拟机。

提示：Parallels 有预设配置（开发者、设计师、游戏等），可按需选择快速设置。

## 4. 在虚拟机中安装 Ubuntu 22.04

1. 启动虚拟机后进入 Ubuntu 安装界面，选择语言并点击 “Install Ubuntu”。
2. 键盘布局、更新与其它软件：建议勾选安装第三方软件以支持 Wi‑Fi、显卡驱动（如适用）。
3. 分区：使用推荐的“Erase disk and install Ubuntu”（这是虚拟磁盘，仅影响 VM）。
4. 设置用户名、密码、时区（例如上海）。
5. 等待安装完成，按提示重启虚拟机。

注意：如果使用 ARM 镜像并在 Apple Silicon 上运行，安装过程与 x86 类似，但某些第三方驱动或软件包可能需要额外注意。

## 5. 安装 Parallels Tools（增强功能）

- 安装完成并登录后，从 Parallels 菜单选择：Actions → Install Parallels Tools（或在窗口提示中点击安装）。
- Parallels Tools 提供：
  - 更好的显示分辨率与自动调整。
  - 共享文件夹、共享剪贴板、拖放、无缝模式。
  - 时间同步、VM 驱动与性能改进。
- 若安装失败：通常需要在虚拟机内安装 build-essential、linux-headers（`sudo apt update && sudo apt install build-essential dkms linux-headers-$(uname -r)`），然后重新运行 Parallels Tools 安装脚本。

## 6. 常用配置与排错

- 共享文件夹/剪贴板：在 Parallels 配置里开启 Shared Folders 与 Shared Clipboard。
- 分辨率/全屏：安装 Parallels Tools 后自动工作；手动可调整 Display 设置。
- 网络问题：尝试切换 Shared / Bridged；检查 mac 防火墙设置。
- 无法引导 ISO：确认 ISO 架构与主机芯片一致（虽然 Apple Silicon 能运行 x86_64 ISO，但是需要转译）。
- Parallels 权限提示：在 macOS 系统设置 → 隐私与安全 中允许 Parallels 的相关权限和扩展。
- 性能优化：关闭不需要的 macOS 应用，增加 VM 内存/CPU，使用 SSD 存储 VM 文件。
- 常见命令：安装常用编译依赖 sudo apt update && sudo apt install build-essential curl git

结束语：按以上步骤可以在 macOS（Intel 或 Apple Silicon）上通过 Parallels 快速搭建 Ubuntu 22.04 虚拟机。如遇特定错误，把错误信息贴出来可进一步定位解决方法。
