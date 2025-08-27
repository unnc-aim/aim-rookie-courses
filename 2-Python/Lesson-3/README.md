# Python Lesson-3: 面向对象编程和程序设计

## 课程信息

- **课时**: 2 学时
- **难度**: 中级
- **前置要求**: 完成 Lesson-1 和 Lesson-2

## 学习目标

完成本节课后，学员将能够：

1. 理解面向对象编程的核心概念
2. 掌握类和对象的定义与使用
3. 理解继承、封装、多态三大特性
4. 掌握异常处理机制
5. 学会文件操作和数据持久化
6. 应用程序设计原则和最佳实践
7. 完成机器人控制系统模拟器项目

## 课程大纲

### 第一部分：面向对象基础概念（30 分钟）

#### 1.1 什么是面向对象编程

**核心概念：**

- 对象(Object)：现实世界实体的抽象
- 类(Class)：对象的模板或蓝图
- 实例(Instance)：类的具体实现

**RoboMaster 中的对象思维：**

- 机器人 → 对象
- 机器人类型 → 类
- 具体的 Hero-1 机器人 → 实例

#### 1.2 第一个类定义

```python
class Robot:
    """机器人类"""

    # 类属性（所有实例共享）
    game_version = "2024"
    robot_count = 0

    def __init__(self, name, robot_type, hp=200):
        """构造函数：初始化对象"""
        self.name = name          # 实例属性
        self.robot_type = robot_type
        self.hp = hp
        self.max_hp = hp
        self.position = [0, 0]
        self.is_active = True

        # 更新类属性
        Robot.robot_count += 1

    def __str__(self):
        """字符串表示"""
        return f"Robot({self.name}, {self.robot_type}, HP:{self.hp})"

    def __repr__(self):
        """开发者表示"""
        return f"Robot('{self.name}', '{self.robot_type}', {self.hp})"

# 创建对象实例
hero = Robot("Hero-1", "Hero", 400)
infantry = Robot("Infantry-1", "Infantry", 200)

print(hero)  # Robot(Hero-1, Hero, HP:400)
print(f"总机器人数量: {Robot.robot_count}")
```

#### 1.3 实例方法、类方法、静态方法

```python
class Robot:
    robot_count = 0

    def __init__(self, name, robot_type):
        self.name = name
        self.robot_type = robot_type
        Robot.robot_count += 1

    # 实例方法
    def move(self, x, y):
        """移动机器人"""
        self.position = [x, y]
        print(f"{self.name} 移动到位置 ({x}, {y})")

    def take_damage(self, damage):
        """受到伤害"""
        self.hp = max(0, self.hp - damage)
        if self.hp == 0:
            self.is_active = False
            print(f"{self.name} 已被击毁")

    # 类方法
    @classmethod
    def get_robot_count(cls):
        """获取机器人总数"""
        return cls.robot_count

    @classmethod
    def create_hero(cls, name):
        """工厂方法：创建Hero类型机器人"""
        return cls(name, "Hero")

    # 静态方法
    @staticmethod
    def calculate_distance(pos1, pos2):
        """计算两点间距离"""
        return ((pos1[0] - pos2[0])**2 + (pos1[1] - pos2[1])**2)**0.5

    @staticmethod
    def is_valid_position(x, y):
        """验证位置是否有效"""
        return 0 <= x <= 1000 and 0 <= y <= 1000
```

### 第二部分：面向对象三大特性（45 分钟）

#### 2.1 封装(Encapsulation)

```python
class Robot:
    def __init__(self, name, robot_type):
        self.name = name
        self.robot_type = robot_type
        self._hp = 200              # 受保护属性
        self.__serial_number = None  # 私有属性
        self.__generate_serial()

    def __generate_serial(self):
        """私有方法：生成序列号"""
        import random
        self.__serial_number = f"RB{random.randint(1000, 9999)}"

    # 属性访问器(getter)
    @property
    def hp(self):
        """获取血量"""
        return self._hp

    # 属性设置器(setter)
    @hp.setter
    def hp(self, value):
        """设置血量"""
        if 0 <= value <= 400:
            self._hp = value
        else:
            raise ValueError("血量必须在0-400之间")

    @property
    def serial_number(self):
        """获取序列号（只读）"""
        return self.__serial_number

    def get_status(self):
        """获取机器人状态"""
        return {
            "name": self.name,
            "type": self.robot_type,
            "hp": self._hp,
            "serial": self.__serial_number
        }

# 使用示例
robot = Robot("Hero-1", "Hero")
print(robot.hp)         # 200
robot.hp = 150          # 通过setter设置
# robot.hp = 500        # 会抛出ValueError异常
print(robot.serial_number)  # 只读属性
```

#### 2.2 继承(Inheritance)

```python
# 基类
class Robot:
    def __init__(self, name, robot_type, hp=200):
        self.name = name
        self.robot_type = robot_type
        self.hp = hp
        self.max_hp = hp
        self.position = [0, 0]

    def move(self, x, y):
        """基础移动方法"""
        self.position = [x, y]
        print(f"{self.name} 移动到 ({x}, {y})")

    def attack(self):
        """基础攻击方法"""
        print(f"{self.name} 进行基础攻击")

# 派生类：英雄机器人
class HeroRobot(Robot):
    def __init__(self, name):
        super().__init__(name, "Hero", 400)  # 调用父类构造函数
        self.special_weapon = "42mm弹丸"
        self.shield_energy = 100

    def special_attack(self):
        """特殊攻击"""
        if self.shield_energy >= 20:
            self.shield_energy -= 20
            print(f"{self.name} 使用 {self.special_weapon} 进行特殊攻击！")
        else:
            print(f"{self.name} 能量不足，无法使用特殊攻击")

    def activate_shield(self):
        """激活护盾"""
        if self.shield_energy >= 50:
            self.shield_energy -= 50
            print(f"{self.name} 激活护盾")
        else:
            print(f"{self.name} 能量不足，无法激活护盾")

# 派生类：步兵机器人
class InfantryRobot(Robot):
    def __init__(self, name):
        super().__init__(name, "Infantry", 200)
        self.ammo = 100
        self.reload_speed = 1.5

    def attack(self):
        """重写攻击方法"""
        if self.ammo > 0:
            self.ammo -= 1
            print(f"{self.name} 射击！剩余弹药：{self.ammo}")
        else:
            print(f"{self.name} 弹药耗尽，需要补给")

    def reload(self):
        """装弹"""
        self.ammo = 100
        print(f"{self.name} 完成装弹")

# 派生类：工程机器人
class EngineerRobot(Robot):
    def __init__(self, name):
        super().__init__(name, "Engineer", 300)
        self.resources = 50

    def repair(self, target_robot):
        """修复其他机器人"""
        if self.resources >= 10 and target_robot.hp < target_robot.max_hp:
            self.resources -= 10
            target_robot.hp = min(target_robot.max_hp, target_robot.hp + 50)
            print(f"{self.name} 修复了 {target_robot.name}")
        else:
            print(f"{self.name} 无法修复 {target_robot.name}")

    def collect_resources(self):
        """收集资源"""
        self.resources = min(100, self.resources + 20)
        print(f"{self.name} 收集资源，当前资源：{self.resources}")
```

#### 2.3 多态(Polymorphism)

```python
def robot_battle_simulation(robots):
    """机器人战斗模拟 - 展示多态性"""
    print("=== 战斗模拟开始 ===")

    for robot in robots:
        print(f"\n{robot.name} 的回合:")

        # 所有机器人都有attack方法，但实现不同
        robot.attack()

        # 根据机器人类型调用特有方法
        if isinstance(robot, HeroRobot):
            robot.special_attack()
        elif isinstance(robot, InfantryRobot):
            if robot.ammo == 0:
                robot.reload()
        elif isinstance(robot, EngineerRobot):
            robot.collect_resources()

# 创建不同类型的机器人
robots = [
    HeroRobot("Hero-1"),
    InfantryRobot("Infantry-1"),
    InfantryRobot("Infantry-2"),
    EngineerRobot("Engineer-1")
]

# 运行战斗模拟
robot_battle_simulation(robots)
```

### 第三部分：异常处理（20 分钟）

#### 3.1 异常的基本概念

```python
# 常见异常类型
def demonstrate_exceptions():
    try:
        # ZeroDivisionError
        result = 10 / 0
    except ZeroDivisionError:
        print("除零错误")

    try:
        # IndexError
        robots = ["Hero", "Infantry"]
        print(robots[5])
    except IndexError:
        print("索引超出范围")

    try:
        # KeyError
        robot_config = {"name": "Hero"}
        print(robot_config["hp"])
    except KeyError:
        print("键不存在")

    try:
        # ValueError
        hp = int("abc")
    except ValueError:
        print("值转换错误")
```

#### 3.2 异常处理最佳实践

```python
class RobotControlSystem:
    def __init__(self):
        self.robots = {}

    def add_robot(self, robot_id, robot):
        """添加机器人"""
        try:
            if not isinstance(robot_id, str):
                raise TypeError("机器人ID必须是字符串")

            if robot_id in self.robots:
                raise ValueError(f"机器人ID {robot_id} 已存在")

            if not isinstance(robot, Robot):
                raise TypeError("必须是Robot类型的对象")

            self.robots[robot_id] = robot
            print(f"机器人 {robot_id} 添加成功")

        except (TypeError, ValueError) as e:
            print(f"添加机器人失败: {e}")
            return False
        except Exception as e:
            print(f"未知错误: {e}")
            return False
        else:
            return True
        finally:
            print("添加机器人操作完成")

    def move_robot(self, robot_id, x, y):
        """移动机器人"""
        try:
            robot = self.robots[robot_id]

            if not (0 <= x <= 1000 and 0 <= y <= 1000):
                raise ValueError("坐标超出场地范围")

            robot.move(x, y)

        except KeyError:
            print(f"机器人 {robot_id} 不存在")
        except ValueError as e:
            print(f"移动失败: {e}")
        except Exception as e:
            print(f"移动过程中发生错误: {e}")

# 自定义异常
class RobotDestroyedException(Exception):
    """机器人已损坏异常"""
    def __init__(self, robot_name):
        self.robot_name = robot_name
        super().__init__(f"机器人 {robot_name} 已损坏，无法执行操作")

class InsufficientEnergyException(Exception):
    """能量不足异常"""
    def __init__(self, required, current):
        self.required = required
        self.current = current
        super().__init__(f"能量不足：需要 {required}，当前 {current}")
```

### 第四部分：文件操作（15 分钟）

#### 4.1 基本文件操作

```python
import json
import pickle
from datetime import datetime

class RobotDataManager:
    """机器人数据管理器"""

    @staticmethod
    def save_robot_to_file(robot, filename):
        """保存机器人数据到文件"""
        try:
            robot_data = {
                "name": robot.name,
                "type": robot.robot_type,
                "hp": robot.hp,
                "max_hp": robot.max_hp,
                "position": robot.position,
                "is_active": robot.is_active,
                "save_time": datetime.now().isoformat()
            }

            with open(filename, 'w', encoding='utf-8') as f:
                json.dump(robot_data, f, ensure_ascii=False, indent=2)

            print(f"机器人数据保存到 {filename}")

        except Exception as e:
            print(f"保存失败: {e}")

    @staticmethod
    def load_robot_from_file(filename):
        """从文件加载机器人数据"""
        try:
            with open(filename, 'r', encoding='utf-8') as f:
                robot_data = json.load(f)

            # 重建机器人对象
            robot = Robot(
                robot_data["name"],
                robot_data["type"],
                robot_data["hp"]
            )
            robot.position = robot_data["position"]
            robot.is_active = robot_data["is_active"]

            print(f"从 {filename} 加载机器人数据")
            return robot

        except FileNotFoundError:
            print(f"文件 {filename} 不存在")
        except json.JSONDecodeError:
            print(f"文件 {filename} 格式错误")
        except Exception as e:
            print(f"加载失败: {e}")

        return None

    @staticmethod
    def save_battle_log(events, filename):
        """保存战斗日志"""
        try:
            with open(filename, 'a', encoding='utf-8') as f:
                for event in events:
                    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                    f.write(f"[{timestamp}] {event}\n")

            print(f"战斗日志已追加到 {filename}")

        except Exception as e:
            print(f"保存日志失败: {e}")
```

### 第五部分：程序设计原则（10 分钟）

#### 5.1 SOLID 原则简介

```python
# 单一责任原则 (Single Responsibility Principle)
class RobotRenderer:
    """专门负责机器人显示"""
    def render_robot_status(self, robot):
        return f"[{robot.name}] HP: {robot.hp}/{robot.max_hp}"

class RobotController:
    """专门负责机器人控制"""
    def __init__(self, robot):
        self.robot = robot

    def execute_move_command(self, x, y):
        self.robot.move(x, y)

# 开闭原则 (Open/Closed Principle)
class Weapon:
    """武器基类"""
    def attack(self):
        raise NotImplementedError

class Gun(Weapon):
    def attack(self):
        return "射击攻击"

class Cannon(Weapon):
    def attack(self):
        return "炮弹攻击"

# 机器人可以扩展新武器，而不需要修改原有代码
class AdvancedRobot(Robot):
    def __init__(self, name, robot_type):
        super().__init__(name, robot_type)
        self.weapons = []

    def add_weapon(self, weapon):
        self.weapons.append(weapon)

    def attack_with_weapon(self, weapon_index):
        if 0 <= weapon_index < len(self.weapons):
            return self.weapons[weapon_index].attack()
```

### 第六部分：实践项目 - 机器人控制系统模拟器（20 分钟）

```python
import json
import random
from datetime import datetime
from enum import Enum

class RobotState(Enum):
    """机器人状态枚举"""
    IDLE = "待机"
    MOVING = "移动中"
    ATTACKING = "攻击中"
    DEFENDING = "防御中"
    DESTROYED = "已损坏"

class Command:
    """命令基类"""
    def __init__(self, robot_id, timestamp=None):
        self.robot_id = robot_id
        self.timestamp = timestamp or datetime.now()

    def execute(self, robot):
        raise NotImplementedError

class MoveCommand(Command):
    def __init__(self, robot_id, x, y):
        super().__init__(robot_id)
        self.x = x
        self.y = y

    def execute(self, robot):
        robot.move(self.x, self.y)
        return f"{robot.name} 移动到 ({self.x}, {self.y})"

class AttackCommand(Command):
    def __init__(self, robot_id, target_id):
        super().__init__(robot_id)
        self.target_id = target_id

    def execute(self, robot):
        robot.attack()
        return f"{robot.name} 攻击目标 {self.target_id}"

class RobotSimulator:
    """机器人控制系统模拟器"""

    def __init__(self):
        self.robots = {}
        self.command_queue = []
        self.battle_log = []
        self.simulation_running = False

    def add_robot(self, robot_id, robot_type, name=None):
        """添加机器人"""
        try:
            if robot_id in self.robots:
                raise ValueError(f"机器人ID {robot_id} 已存在")

            name = name or f"{robot_type}-{robot_id}"

            if robot_type == "Hero":
                robot = HeroRobot(name)
            elif robot_type == "Infantry":
                robot = InfantryRobot(name)
            elif robot_type == "Engineer":
                robot = EngineerRobot(name)
            else:
                raise ValueError(f"不支持的机器人类型: {robot_type}")

            robot.state = RobotState.IDLE
            self.robots[robot_id] = robot

            log_entry = f"机器人 {name} ({robot_type}) 已加入战场"
            self.battle_log.append(log_entry)
            print(log_entry)

            return True

        except Exception as e:
            print(f"添加机器人失败: {e}")
            return False

    def remove_robot(self, robot_id):
        """移除机器人"""
        if robot_id in self.robots:
            robot_name = self.robots[robot_id].name
            del self.robots[robot_id]

            log_entry = f"机器人 {robot_name} 已离开战场"
            self.battle_log.append(log_entry)
            print(log_entry)
            return True
        else:
            print(f"机器人 {robot_id} 不存在")
            return False

    def add_command(self, command):
        """添加命令到队列"""
        self.command_queue.append(command)

    def execute_commands(self):
        """执行命令队列"""
        results = []

        while self.command_queue:
            command = self.command_queue.pop(0)

            if command.robot_id not in self.robots:
                error_msg = f"机器人 {command.robot_id} 不存在"
                print(error_msg)
                results.append(error_msg)
                continue

            robot = self.robots[command.robot_id]

            if robot.hp <= 0:
                error_msg = f"机器人 {robot.name} 已损坏，无法执行命令"
                print(error_msg)
                results.append(error_msg)
                continue

            try:
                result = command.execute(robot)
                results.append(result)
                self.battle_log.append(result)
                print(result)

            except Exception as e:
                error_msg = f"执行命令失败: {e}"
                print(error_msg)
                results.append(error_msg)

        return results

    def simulate_battle(self, rounds=5):
        """模拟战斗"""
        print(f"\n=== 开始 {rounds} 轮战斗模拟 ===")
        self.simulation_running = True

        for round_num in range(1, rounds + 1):
            print(f"\n--- 第 {round_num} 轮 ---")

            # 随机生成命令
            active_robots = [rid for rid, robot in self.robots.items() if robot.hp > 0]

            if len(active_robots) < 2:
                print("战斗结束：可战斗机器人不足")
                break

            for robot_id in active_robots[:2]:  # 选择前两个机器人
                # 随机移动
                x = random.randint(0, 100)
                y = random.randint(0, 100)
                self.add_command(MoveCommand(robot_id, x, y))

                # 随机攻击
                if len(active_robots) > 1:
                    target_id = random.choice([r for r in active_robots if r != robot_id])
                    self.add_command(AttackCommand(robot_id, target_id))

            # 执行这轮的命令
            self.execute_commands()

            # 随机造成伤害
            for robot_id in active_robots:
                if random.random() < 0.3:  # 30%概率受伤
                    damage = random.randint(10, 50)
                    robot = self.robots[robot_id]
                    robot.hp = max(0, robot.hp - damage)

                    log_entry = f"{robot.name} 受到 {damage} 点伤害，剩余HP: {robot.hp}"
                    self.battle_log.append(log_entry)
                    print(log_entry)

                    if robot.hp <= 0:
                        robot.state = RobotState.DESTROYED
                        log_entry = f"{robot.name} 已被击毁"
                        self.battle_log.append(log_entry)
                        print(log_entry)

        self.simulation_running = False
        print("\n=== 战斗模拟结束 ===")
        self.show_battle_summary()

    def show_battle_summary(self):
        """显示战斗总结"""
        print("\n=== 战斗总结 ===")

        for robot_id, robot in self.robots.items():
            status = "存活" if robot.hp > 0 else "损坏"
            print(f"{robot.name}: HP {robot.hp}/{robot.max_hp} - {status}")

        print(f"\n总共执行了 {len(self.battle_log)} 个操作")

    def save_battle_report(self, filename):
        """保存战斗报告"""
        try:
            report = {
                "timestamp": datetime.now().isoformat(),
                "robots": {
                    robot_id: {
                        "name": robot.name,
                        "type": robot.robot_type,
                        "hp": robot.hp,
                        "max_hp": robot.max_hp,
                        "position": robot.position,
                        "state": robot.state.value if hasattr(robot, 'state') else "Unknown"
                    }
                    for robot_id, robot in self.robots.items()
                },
                "battle_log": self.battle_log
            }

            with open(filename, 'w', encoding='utf-8') as f:
                json.dump(report, f, ensure_ascii=False, indent=2)

            print(f"战斗报告已保存到 {filename}")

        except Exception as e:
            print(f"保存报告失败: {e}")

# 演示程序
def main():
    """主程序演示"""
    simulator = RobotSimulator()

    # 添加机器人
    simulator.add_robot("R001", "Hero", "英雄一号")
    simulator.add_robot("R002", "Infantry", "步兵一号")
    simulator.add_robot("R003", "Infantry", "步兵二号")
    simulator.add_robot("R004", "Engineer", "工程一号")

    # 手动添加一些命令
    simulator.add_command(MoveCommand("R001", 50, 50))
    simulator.add_command(MoveCommand("R002", 30, 70))
    simulator.add_command(AttackCommand("R001", "R002"))

    # 执行命令
    print("\n=== 执行手动命令 ===")
    simulator.execute_commands()

    # 开始战斗模拟
    simulator.simulate_battle(3)

    # 保存战斗报告
    simulator.save_battle_report("battle_report.json")

if __name__ == "__main__":
    main()
```

## 课堂练习

### 练习 1：设计武器系统

创建一个武器系统：

- 定义武器基类和不同类型的武器子类
- 实现武器的升级和属性增强
- 为机器人添加武器装备功能

### 练习 2：异常处理实践

为机器人系统添加完善的异常处理：

- 自定义机器人相关的异常类
- 在关键操作中添加异常处理
- 实现错误日志记录功能

### 练习 3：数据持久化

实现机器人数据的持久化：

- 保存和加载机器人配置
- 实现战斗历史记录
- 支持多种数据格式（JSON、CSV、Binary）

## 课后作业

### 作业 1：完善机器人控制系统

在课堂项目基础上添加功能：

1. 实现更多机器人类型和特殊能力
2. 添加 AI 自动决策系统
3. 实现实时战斗可视化
4. 添加网络对战功能

### 作业 2：设计模式应用

选择并实现以下设计模式之一：

- 工厂模式：机器人创建工厂
- 观察者模式：事件通知系统
- 策略模式：不同的战斗策略
- 命令模式：操作撤销和重做

## 学习检查点

完成本节课后，请确保你能够：

- [ ] 理解并应用面向对象编程思想
- [ ] 熟练定义和使用类与对象
- [ ] 掌握继承、封装、多态的实现
- [ ] 正确处理程序异常和错误
- [ ] 进行文件读写和数据持久化
- [ ] 应用基本的程序设计原则
- [ ] 完成机器人控制系统模拟器项目
- [ ] 调试复杂的面向对象程序

## Python 课程总结

### 技能成长路径

1. **Lesson-1**: 掌握 Python 基础语法 → 能编写简单程序
2. **Lesson-2**: 掌握数据结构和控制流 → 能处理复杂逻辑
3. **Lesson-3**: 掌握面向对象编程 → 能设计复杂系统

### 下一步学习建议

- 深入学习 Python 标准库
- 学习第三方库（NumPy、Pandas、OpenCV）
- 掌握 Web 开发框架（Flask/Django）
- 学习数据科学和机器学习
- 参与开源项目实践

### RoboMaster 应用方向

- 机器人控制程序开发
- 视觉识别算法实现
- 数据分析和策略优化
- 自动化测试和调试工具
- 比赛数据统计分析

## 扩展阅读

- [Python 面向对象编程](https://docs.python.org/3/tutorial/classes.html)
- [Python 异常处理](https://docs.python.org/3/tutorial/errors.html)
- [Python 文件操作](https://docs.python.org/3/tutorial/inputoutput.html)
- [设计模式 Python 实现](https://python-patterns.guide/)
