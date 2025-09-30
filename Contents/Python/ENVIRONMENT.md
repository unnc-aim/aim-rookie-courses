# Python 课程环境准备

本教程将指导你在 Windows 和 macOS 上安装 Python，并配置开发环境。

## Python 本身

> 首先这肯定是最重要的

### 1. 下载 Python

- **Windows**：[Windows Python 3.12.10 官网下载链接](https://www.python.org/ftp/python/3.12.10/python-3.12.10-amd64.exe)
- **macOS**：[macOS Python 3.12.10 官网下载链接](https://www.python.org/ftp/python/3.12.10/python-3.12.10-macos11.pkg)

### 2. 安装步骤

#### Windows

1. 下载并运行安装包。
2. 勾选“Add Python to PATH”选项。
3. 点击“Install Now”完成安装。

#### macOS

1. 下载并打开安装包。
2. 按照提示完成安装。如果有 “Add Python to PATH” 选项，勾选它。

### 3. 验证安装

在命令行输入：

```bash
python --version
# 或
python3 --version
```

显示 Python 版本号即安装成功。

## 推荐 IDE 工具

- [VS Code](https://code.visualstudio.com/)：强大的 Python 编辑器
- [PyCharm](https://www.jetbrains.com/pycharm/)：专业的 Python IDE

> 在课上我们会使用 VS Code 作为示例的代码编辑器。如果对自己的能力有信心，也可以使用 PyCharm。

### Visual Studio Code (IDE)

> ~~不是 Visual Studio~~  
> 几年前如果你说它是个 `IDE` 时，不少人会纠正你说，这个只是“轻量级”的「代码编辑器」，但现在它已经非常强大，完全可以胜任 Python 等几乎所有语言的基础开发任务，thanks to 它丰富的插件生态。

#### 安装 VS Code

- **Windows**：[Windows VS Code 官网下载链接](https://code.visualstudio.com/sha/download?build=stable&os=win32-x64-user)
- **macOS**：[macOS VS Code 官网下载链接](https://code.visualstudio.com/sha/download?build=stable&os=darwin-universal)

#### 安装 Python 扩展

1. 打开 VS Code。
2. 点击左侧扩展图标（四个方块组成的图标）。
3. 搜索“Python”，选择由 Microsoft 提供的扩展并安装。

> UNNCers 别老想着装 Chinese 扩展，英文界面更符合编程习惯。
>
> 同时推荐的拓展 ⬇️
>
> - ms-python.autopep8 # 自动格式化代码
> - ms-python.isort # 自动排序 import 语句
> - ms-python.vscode-pylance # 静态检查
> - streetsidesoftware.code-spell-checker # 拼写检查
>
> 以及，为了更好地在 VS Code 中阅读 Markdown 文件（本教程使用的格式），推荐安装 ⬇️
>
> - bierner.markdown-mermaid # 支持 mermaid 流程图
> - yzhang.markdown-all-in-one # Markdown 增强，可选
> - DavidAnson.vscode-markdownlint # Markdown 语法检查，可选
>
> 以及，为了更好地阅读 Jupyter Notebook 文件（.ipynb），推荐安装拓展包 ⬇️
>
> - ms-toolsai.jupyter  # Jupyter Notebook 支持

### 配置 Python 解释器

1. 打开一个 Python 文件（.py）。
2. 在右下角点击 Python 版本号，选择刚安装的 Python 解释器路径。
   如果没有看到版本号，可以按 `Ctrl+Shift+P`（macOS 上是 `Cmd+Shift+P`），输入并选择 `Python: Select Interpreter`，然后选择正确的解释器。
3. 现在你可以在 VS Code 中编写和运行 Python 代码了。

> 你可能会发现一个问题，如果你直接使用系统的 Python 解释器，可能会遇到权限问题，或者不同项目间的依赖冲突。  
> 为了解决这个问题，我们推荐使用虚拟环境（virtual environment），为每一个项目创建一个定制的运行环境，也可以在每个环境中安装每个项目需要的 pip requirements。  
> 你可以使用 `venv` 模块来创建虚拟环境，VS Code 中具体实现步骤如下：
>
> 1. 在右下角点击 Python 版本号，选择 `+ Create Virtual Environment`，然后选 `.venv`。
> 2. 选择 Python 解释器（你之前安装的版本）作为基础，VS Code 会自动为你创建并激活虚拟环境。
>
> 之后你可以在 VS Code 中打开新的终端时，VS Code 会自动帮你激活你项目根目录下的 `.venv` 包含的环境，此时使用 `pip install` 来安装项目所需的包，这些包只会安装在当前虚拟环境中，不会影响全局 Python 环境。  
> 如果你在 VS Code 之外的终端中工作，或者 VS Code 没有正确检测到项目中的 venv 环境，你可能需要手动激活虚拟环境。这部分自己上网搜教程。
