# Environment Setup

## Visual Studio Code (IDE)

> 在课上我们会使用 VS Code 作为示例的代码编辑器。  
> 注意：不是 ~~Visual Studio~~，那个比较 heavy，不太适合课堂教学。  
> 几年前如果你说它是个 `IDE` 时，不少人会纠正你说，这个只是“轻量级”的「代码编辑器」，但现在它已经非常强大，完全可以胜任 Python 等几乎所有语言的基础开发任务，thanks to 它丰富的插件生态。  
> 所以叫它 IDE 也没毛病。

### 安装 VS Code

- **Windows**：[Windows VS Code 官网下载链接](https://code.visualstudio.com/sha/download?build=stable&os=win32-x64-user)
- **macOS**：[macOS VS Code 官网下载链接](https://code.visualstudio.com/sha/download?build=stable&os=darwin-universal)

### 推荐拓展

> 打开 VS Code。  
> 点击左侧扩展图标（四个方块组成的图标）。
> 在搜索栏输入 `扩展名称` or `ID` （下面列举的都是 `ID`， 复制 `#` 前的一串即可搜索到唯一对应的插件），点击 install 就可以开始安装。(如果提示是否信任，点 `Trust` 即可)
> 我已经将这些插件放入项目的 `.vscode/extensions.json` 文件中，打开本项目时，VS Code 会提示你安装推荐的插件。

#### 啥项目都能用的

- 远程开发
  - ms-vscode-remote.remote-ssh # 远程 SSH
  - ms-vscode-remote.remote-ssh-edit # 远程 SSH 编辑
  - ms-vscode-remote.remote-containers # 远程容器
  - ms-vscode.remote-explorer # 远程资源管理器
  - ms-vscode.remote-server # 远程隧道 （支持非局域网设备远程连接）
- 报错 inline 显示
  - usernamehw.errorlens # 报错 inline 显示
- 文件图标
  - PKief.material-icon-theme # 文件图标主题
- Git / GitHub 相关
  - eamodio.gitlens # Git 增强 / inline 显示
  - github.vscode-pull-request-github # GitHub PR 管理
  - github.copilot # AI 编程助手 （GitHub Education 免费申请教程请移步 [这里](https://github.com/unnc-aim/aim-tutorial/tree/main/GitHubEducation)）
  - github.copilot-chat # AI 编程助手聊天
- 拼写检查
  - streetsidesoftware.code-spell-checker # 拼写检查
- 本地路径智能提示
  - christian-kohler.path-intellisense # 路径补全
- 容器相关
  - ms-azuretools.vscode-containers # 容器工具
- 实时协作
  - ms-vsliveshare.vsliveshare # 实时协作开发

#### Markdown

为了更好地在 VS Code 中阅读 Markdown 文件（本教程也使用的格式），推荐安装 ⬇️

- bierner.markdown-mermaid # 支持 mermaid 流程图
- yzhang.markdown-all-in-one # Markdown 增强，可选
- DavidAnson.vscode-markdownlint # Markdown 语法检查，可选

#### Jupyter Notebook

以及，为了更好地阅读 Jupyter Notebook 文件（.ipynb），推荐安装拓展包 ⬇️

- ms-toolsai.jupyter # Jupyter Notebook 支持

## 关于本项目

本项目使用 Markdown 作为文档格式，所有的代码均托管在 GitHub 上。

你可以在线阅读所有的文档，但更推荐的方式是将这个项目 clone 到本地，然后使用 VS Code 打开。

> 为什么用 `git clone` 而不是直接下载 ZIP 包？因为后续我们会不断更新文档，使用 git 可以方便地同步最新的内容。  
> 为什么用 VS Code 在本地打开而不是直接在浏览器里看？因为 VS Code 支持更多 Markdown 语法高亮，阅读体验更好。我们教程中还会涉及到 ipynb (Jupyter Notebook) 文件，VS Code 也能直接打开并在本地运行 Python 代码。

如果你还没有安装 git，可以参考[这里](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)进行安装。所有选项默认即可。如有疑问可以 google 教程。

### 克隆项目

#### GUI

你可以下载安装好的 Git GUI 工具（比如 [GitHub Desktop](https://desktop.github.com/)）

点进去上面的链接，根据指示安装好后，打开 GitHub Desktop，选择 `File -> Clone Repository`，然后在弹出的窗口中选择 `URL` 标签页，输入项目的 URL：

```text
https://github.com/unnc-aim/aim-rookie-courses.git
```

选择你想存放项目的本地路径，然后点击 `Clone` 按钮即可。

**或者**，也可以在 GitHub 项目的主页上点击 `Code -> Open with GitHub Desktop`，然后选择存放路径，点击 `Clone` 即可。

GitHub Desktop 甚至可以有个按钮让你可以直接用 VS Code / PyCharm (默认先装的那个) 打开项目。

#### Command Line

也可以直接在命令行中使用 git 进行 clone 操作 ⬇️

```bash
# 记得连 eduroam 或者开魔法
# 打开命令行（Windows 下可以使用 PowerShell 或者 Git Bash，macOS 下可以使用 Terminal）
# cd 到你喜欢的目录，然后输入以下命令
git clone https://github.com/unnc-aim/aim-rookie-courses.git
```

> 什么？ 你不会用命令行？  
> 没关系，Google 一下 `Windows/macOS如何打开命令行`  
> 记得 cd 跳转到你想存放项目的目录下再执行 `git clone` 命令，或者干脆在你喜欢的目录直接打开也行。自己搜怎么做到。  
> 比如你想放在桌面上，可以先执行 `cd Desktop` (macOS 下是 `cd ~/Desktop`)。
>
> Git 和 命令行 这一块的内容我们 CPU 周常很快会有课程讲到，我们 AIM 后续 Linux 课程也会讲到 Linux Shell，如果不够熟悉建议现在开始补课。

然后你就可以在本地看到一个 `aim-rookie-courses` 的文件夹，里面就是本项目的所有内容。用 VS Code 打开这个文件夹即可。

```bash
# 如果你想装逼：
cd aim-rookie-courses
code .

# 如果你发现你装逼失败了：
# https://code.visualstudio.com/docs/setup/mac#_launch-vs-code-from-the-command-line
```

### 同步更新

当我们更新了文档内容，你可以在命令行中使用以下命令同步最新的内容：

```bash
git pull
```

你也可以在 VS Code 的 Source Control 面板中点击 `...` 按钮，然后选择 `Pull`。

## 其他

- 如果你在使用 VS Code 的过程中遇到任何问题，可以参考[官方文档](https://code.visualstudio.com/docs)或者在网上搜索相关的解决方案。
- 如果你对本项目有任何建议或者发现了错误，欢迎在 GitHub 上提出 issue 或者 pull request。
- 如果你希望参与到本项目的维护中来，也欢迎联系我我们老队员。

## 维护人员名单

- [Robert He](https://github.com/hnrobert)
- [Xiaoyan Gong](https://github.com/Calc1te)
- [Animex77](https://github.com/Animex77)
- [lv_xin](https://github.com/lvxin1024)

祝你食用愉快！
