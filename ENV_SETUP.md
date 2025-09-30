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
> 在搜索栏输入 `扩展名称` or `ID` （下面列举的都是 `ID`， 复制 `#` 前的一串即可搜索到唯一对应的插件），点击 install 即可。
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
  - github.copilot # AI 编程助手
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

为了更好地在 VS Code 中阅读 Markdown 文件（本教程使用的格式），推荐安装 ⬇️

- bierner.markdown-mermaid # 支持 mermaid 流程图
- yzhang.markdown-all-in-one # Markdown 增强，可选
- DavidAnson.vscode-markdownlint # Markdown 语法检查，可选

#### Jupyter Notebook

以及，为了更好地阅读 Jupyter Notebook 文件（.ipynb），推荐安装拓展包 ⬇️

- ms-toolsai.jupyter # Jupyter Notebook 支持
