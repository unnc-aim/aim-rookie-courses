# Python Lesson-1: 基础语法和数据类型

## 课程信息

- **课时**: 2 学时
- **难度**: 入门级
- **前置要求**: 无编程经验要求

## 学习目标

完成本节课后，学员将能够：

1. 配置 Python 开发环境
2. 理解 Python 基本语法规则
3. 掌握 Python 基础数据类型
4. 进行基本的变量操作和运算
5. 处理简单的输入输出
6. 编写第一个 Python 程序

## 课程大纲

### 第一部分：环境配置与认识 Python（30 分钟）

#### 1.1 Python 简介

- Python 的历史和特点
- Python 的应用领域
- 在 RoboMaster 中的应用场景

#### 1.2 开发环境配置

- Python 安装和版本选择
- VS Code 配置
- Python 扩展插件安装
- 第一个"Hello World"程序

```python
print("Hello, RoboMaster!")
```

#### 1.3 Python 交互模式

- REPL 环境的使用
- IPython 介绍
- Jupyter Notebook 基础

### 第二部分：基础语法规则（20 分钟）

#### 2.1 代码风格和规范

- PEP 8 编码规范
- 缩进和代码块
- 注释的编写

```python
# 这是单行注释
"""
这是多行注释
用于详细说明
"""

def greet_robot(name):
    """问候机器人的函数"""
    print(f"Hello, {name}!")
```

#### 2.2 标识符和关键字

- 变量命名规则
- Python 关键字
- 命名约定

### 第三部分：数据类型详解（40 分钟）

#### 3.1 数字类型

```python
# 整数
robot_id = 42
hero_hp = 600  # 英雄机器人血量较厚
infantry_hp = 200  # 步兵机器人标准血量

# 浮点数
battery_voltage = 12.5
distance = 3.14159

# 复数（了解即可）
complex_num = 3 + 4j
```

#### 3.2 字符串类型

```python
# 字符串定义
robot_name = "Hero"  # 英雄机器人
team_name = 'AIM'

# 字符串操作
message = "Robot " + robot_name + " is ready!"
formatted_msg = f"Battery level: {battery_voltage}V"

# 字符串方法
print(robot_name.upper())
print(robot_name.lower())
print(len(team_name))
```

#### 3.3 布尔类型

```python
is_robot_active = True
has_ammunition = False

# 布尔运算
can_shoot = is_robot_active and has_ammunition
```

#### 3.4 类型转换

```python
# 显式类型转换
score_str = "95"
score_int = int(score_str)
score_float = float(score_str)

# 隐式类型转换
result = 10 + 3.5  # 结果为浮点数
```

### 第四部分：运算符（20 分钟）

#### 4.1 算术运算符

```python
a = 10
b = 3

print(a + b)    # 加法: 13
print(a - b)    # 减法: 7
print(a * b)    # 乘法: 30
print(a / b)    # 除法: 3.333...
print(a // b)   # 整除: 3
print(a % b)    # 取余: 1
print(a ** b)   # 幂运算: 1000
```

#### 4.2 比较运算符

```python
x = 5
y = 10

print(x == y)   # False
print(x != y)   # True
print(x < y)    # True
print(x > y)    # False
print(x <= y)   # True
print(x >= y)   # False
```

#### 4.3 逻辑运算符

```python
a = True
b = False

print(a and b)  # False
print(a or b)   # True
print(not a)    # False
```

### 第五部分：输入输出（15 分钟）

#### 5.1 输出函数 print()

```python
# 基本输出
print("Hello World")

# 多个参数
print("Robot ID:", robot_id)

# 格式化输出
print(f"英雄机器人{robot_name}的血量是{hero_hp}HP")

# 控制输出格式
print("A", "B", "C", sep="-")  # A-B-C
print("Loading", end="...")    # 不换行
```

#### 5.2 输入函数 input()

```python
# 基本输入
user_name = input("请输入你的姓名: ")

# 类型转换输入
age = int(input("请输入年龄: "))
height = float(input("请输入身高(米): "))

print(f"你好 {user_name}, 你今年 {age} 岁，身高 {height} 米")
```

### 第六部分：实践项目（15 分钟）

#### 项目：简单计算器

编写一个简单的计算器程序，能够：

1. 接收用户输入的两个数字
2. 选择运算类型（+、-、\*、/）
3. 计算并显示结果
4. 处理基本的错误情况

```python
def simple_calculator():
    """简单计算器程序"""
    print("=== RoboMaster 简单计算器 ===")

    # 获取用户输入
    num1 = float(input("请输入第一个数字: "))
    operator = input("请输入运算符 (+, -, *, /): ")
    num2 = float(input("请输入第二个数字: "))

    # 执行计算
    if operator == '+':
        result = num1 + num2
    elif operator == '-':
        result = num1 - num2
    elif operator == '*':
        result = num1 * num2
    elif operator == '/':
        if num2 != 0:
            result = num1 / num2
        else:
            print("错误：除数不能为零！")
            return
    else:
        print("错误：不支持的运算符！")
        return

    print(f"计算结果: {num1} {operator} {num2} = {result}")

# 运行计算器
simple_calculator()
```

## 课堂练习

### 练习 1：个人信息收集器

编写程序收集用户的基本信息并格式化输出：

- 姓名、年龄、专业、兴趣爱好
- 使用 f-string 格式化输出

### 练习 2：单位转换器

编写程序实现基本单位转换：

- 摄氏度转华氏度
- 米转换为英尺
- 公斤转换为磅

### 练习 3：机器人状态检查器

模拟机器人状态检查：

- 输入机器人类型（Hero/Infantry/Engineer）
- 输入当前血量，判断血量状态
- 根据机器人类型判断是否可以攻击
- 输出机器人整体状态

## 课后作业

### 作业 1：增强计算器

在课堂项目基础上增加功能：

1. 支持连续计算
2. 添加更多运算符（如求余、幂运算）
3. 增加计算历史记录
4. 优化用户界面和错误处理

### 作业 2：个人名片生成器

编写程序生成 ASCII 艺术风格的个人名片：

- 包含姓名、联系方式、技能等信息
- 使用字符画装饰
- 支持不同的名片样式选择

## 学习检查点

完成本节课后，请确保你能够：

- [ ] 独立安装和配置 Python 开发环境
- [ ] 理解 Python 基本语法规则和代码风格
- [ ] 熟练使用各种数据类型和运算符
- [ ] 编写包含输入输出的基本程序
- [ ] 调试简单的语法错误
- [ ] 完成简单计算器项目

## 下节课预告

### Lesson-2: 数据结构和控制流程

- 学习列表、字典等复合数据类型
- 掌握条件语句和循环语句
- 开始函数式编程思维
- 项目：学生成绩管理系统

## 扩展阅读

- [Python 官方教程 - 第 3 章](https://docs.python.org/3/tutorial/introduction.html)
- [PEP 8 编码规范](https://www.python.org/dev/peps/pep-0008/)
- [Python 数据类型详解](https://docs.python.org/3/library/stdtypes.html)
