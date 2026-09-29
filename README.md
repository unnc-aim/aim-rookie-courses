# UNNC AIM 新生培训课程 · 仓库总览

> 本仓库（`aim-rookie-courses`）是 UNNC AIM 战队新生培训课程的**总览与整体使用指南**。各学年课程放在独立的 `aim-<学年>-rookie-courses` 仓库中，学年结束后归档。

## 仓库家族

| 仓库 | 状态 | 内容 |
| --- | --- | --- |
| [aim-rookie-courses](https://github.com/unnc-aim/aim-rookie-courses)（本仓库） | 长期维护 | 仓库总览、整体使用指南、[贡献指南](./CONTRIBUTING.md)（含学年换届流程） |
| [aim-2627-rookie-courses](https://github.com/unnc-aim/aim-2627-rookie-courses) | **当前学年** | 2026-2027 学年培训课程：计算方向（控制 / 导航 / 算法三平行组）+ 机械方向 |
| [aim-2526-rookie-courses](https://github.com/unnc-aim/aim-2526-rookie-courses) | 已归档 | 2025-2026 学年培训课程（Routes / Contents 分离架构） |

**命名约定**：`aim-<学年>-rookie-courses`，学年取起止年份后两位（`2627` = 2026-2027 学年）。每个学年一个仓库，学年结束后在 GitHub 上归档（Archive），只读不再更新。

## 食用指南

### 第一步：进入当前学年仓库

所有课程内容都在**当前学年**仓库里（见上表，每个学年初会更换）。请先去当前学年仓库的 [README](https://github.com/unnc-aim/aim-2627-rookie-courses/blob/main/README.md) 了解整体结构。

### 第二步：配置本地环境

按当前学年仓库根目录的 [ENV_SETUP.md](https://github.com/unnc-aim/aim-2627-rookie-courses/blob/main/ENV_SETUP.md) 安装 VS Code、Git 等工具，并把仓库 clone 到本地。教程文档会持续更新，`git pull` 即可同步最新内容。

### 第三步：确定专业方向

```mermaid
graph TD
    A[RoboMaster 战队培训] --> B[Computing 计算方向]
    A --> C[Mechanic 机械方向]
    B --> F[Algorithm 算法组]
    B --> G[Navigation 导航组]
    B --> E[Control 控制组]
    C --> D[Mechanic 机械组]

    F --> H[Aiming 自瞄系统]
    F --> I[Radar 雷达系统]
    G --> J[Behavior Tree 行为树]
    G --> K[Navigation 导航]
    E --> L[AIMEtherCat 以太猫]
    E --> M[STM32]
    D --> N[Inventor 画图]
    D --> O[Assembling 组装]
```

- **计算方向（Computing）**：适合对编程、算法、电路设计感兴趣的同学。先完成 `01-Python → 02-Linux → 03-Cpp → 04-ROS2` 公共基础，再进入平行分组：
   - **控制组（Control）**：EtherCAT 通信、电机与底盘控制、嵌入式开发 → [学习路线](https://github.com/unnc-aim/aim-2627-rookie-courses/blob/main/Computing/Control/README.md)
   - **导航组（Navigation）**：SLAM 定位建图、路径规划、运动控制 → [学习路线](https://github.com/unnc-aim/aim-2627-rookie-courses/blob/main/Computing/Navigation/README.md)
   - **算法组（Algorithm）**：OpenCV 视觉基础、自瞄 / 雷达系统 → [学习路线](https://github.com/unnc-aim/aim-2627-rookie-courses/blob/main/Computing/Algorithm/README.md)
- **机械方向（Mechanic）**：适合对机械设计、结构分析、制造工艺感兴趣的同学，使用 Inventor 进行 3D 建模 → [学习路线](https://github.com/unnc-aim/aim-2627-rookie-courses/blob/main/Mechanic/README.md)

### 第四步：按路线学习

进入所在方向的组目录，按其 `README.md` 中的学习路径与课程安排推进即可。遇到问题可以在对应仓库提 issue，或直接联系各组负责人。

## 布局演变

### 2526 学年（已归档）：路线 / 内容分离

- `Contents/` 存放课程内容（Python / Linux / Cpp / ROS2 / OpenCV / Mechanic），`Routes/` 按组存放学习路线；
- 计算方向分**算法组**（下辖导航、视觉两个子方向）和**电控组**。

### 2627 学年（当前）：组目录合并 + 三个平行组

- 取消 Routes / Contents 分离，学习路线与课程内容统一放在组目录下（组目录 `README.md` 即入口）；
- **控制、导航、算法三个组平行**，同属 `Computing/`：
   - 电控组更名为**控制组**（Electronic → Control）；
   - **导航**从算法组独立成组；
   - **算法组**聚焦视觉方向（自瞄 / 雷达），原 Vision 路线并入；
- 课程全局编号：公共基础 `01`-`04` 全组必修，其后按开课顺序连续编号（`05-OpenCV`…）。

组级别的迁移对照：

| 2526 | 2627 | 说明 |
| --- | --- | --- |
| `Routes/Computing/Electronic/` | `Computing/Control/` | 电控组更名控制组 |
| `Routes/Computing/Algorithm/Navigation/` | `Computing/Navigation/` | 导航独立成组 |
| `Routes/Computing/Algorithm/Vision/` | `Computing/Algorithm/` | Vision 并入算法组 |
| `Contents/` + `Routes/` | `Computing/<组>/`、`Mechanic/` | 课程与路线合并 |

完整路径级对照表见 [2627 仓库 README](https://github.com/unnc-aim/aim-2627-rookie-courses/blob/main/README.md)。

## 相关链接

- [贡献指南（含学年换届流程）](./CONTRIBUTING.md)
- [unnc-aim 组织主页](https://github.com/unnc-aim)
- [AI 规范 skill（aim-common-agentic-skills）](https://github.com/unnc-aim/aim-common-agentic-skills)

## 维护人员名单

- [Robert He](https://github.com/hnrobert)
- [Xiaoyan Gong](https://github.com/Calc1te)
- [Animex77](https://github.com/Animex77)
- [lv_xin](https://github.com/lvxin1024)
- [HappyDog](https://github.com/HappyDog060713)
- [AnthonyBvvd](https://github.com/AnthonyBvvd)
