# 贡献指南

欢迎通过 issue 或 pull request 参与本仓库（总览）及各学年课程仓库的维护。

## 通用规范

- 提交 PR 前先阅读当前学年仓库的 README，了解目录布局与课程编号约定；课程内容（讲义、代码、ipynb）的修订提交到**当前学年仓库**，跨学年的总览 / 指南问题提交到本仓库。
- 仓库命名 / 分支 / commit / 代码格式化规范见 [unnc-aim/.github](https://github.com/unnc-aim/.github) `profile/`；使用 AI 编程助手的队员推荐安装 [aim-common-rules](https://github.com/unnc-aim/aim-common-agentic-skills) skill。
- 文档风格：Markdown 嵌套列表 3 空格缩进，代码围栏声明语言，行尾不留多余空白（仓库根目录 `.editorconfig` 与 `.markdownlint.json` 已约定）。

## 学年换届流程（维护者）

每个学年初（约 9 月）执行一次：

1. **建新学年仓库** `aim-<新学年>-rookie-courses`，从上学年仓库复制课程内容；课程内容可按当年教学安排修订，但沿用「组目录 = 路线 + 内容」的布局与课程全局编号约定。
2. **撰写新学年根 README**：说明本学年新变化、目录结构与上学年迁移对照（可参考 [2627 README](https://github.com/unnc-aim/aim-2627-rookie-courses/blob/main/README.md) 的写法），并迁移根目录 `ENV_SETUP.md`（更新其中的克隆地址）。
3. **归档上学年仓库**：GitHub → Settings → Archive repository，归档后不再接受修改。
4. **更新本仓库**：「仓库家族」表格换当前学年指针，把旧学年移入归档行，必要时补充布局演变记录。
5. **组结构调整**（如 2627 学年三组平行）只需在新学年仓库内落地，并在总览 README「布局演变」补一段说明。
