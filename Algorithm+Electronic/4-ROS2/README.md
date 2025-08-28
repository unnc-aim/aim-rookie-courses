[cpp版](https://github.com/UNNC-AIM/2026-AIM-Courses/tree/main/Algorithm%2BElectronic/4-ROS2/README.cpp.md)

# ROS 2 Lesson-1：虚拟机环境下的节点、订阅与服务实战

> 目标：在虚拟机里完成一个最小可跑的 ROS 2 项目（Python 实现），包含一个发布者节点、一个订阅者节点，以及一个简单的加法服务与客户端。

> 适用：Ubuntu + ROS 2（任意发行版，文中以环境变量 `$ROS_DISTRO` 表示，如 `humble` / `iron` / `jazzy` 等）。

---

## 1. 创建工作空间（workspace）

```bash
# 建立一个 ROS 2 工作空间
mkdir -p ~/ros2-ws/src
cd ~/ros2-ws
```

> 工作空间标准结构为 `ros2-ws/src`。之后所有包都放在 `src` 下面，用 `colcon build` 统一构建。

---

## 2. 准备依赖与环境

确保已安装 ROS 2（任意发行版均可）。若尚未安装，请参考 ROS 2 官方安装指引（根据你的 Ubuntu 版本与目标发行版选择）。下面仅安装常用开发工具：

```bash
sudo apt update
sudo apt install -y python3-colcon-common-extensions python3-rosdep \
                    python3-argcomplete git

# 初始化 rosdep（第一次用需要）
sudo rosdep init || true
rosdep update
```

> 建议把 ROS 2 的环境自动写入 `~/.bashrc`：

```bash
echo 'source /opt/ros/$ROS_DISTRO/setup.bash' >> ~/.bashrc
source ~/.bashrc
```

---

## 3. 创建演示包（Python）

在 `src` 下新建一个 Python 包，依赖 `rclpy`、`std_msgs`、`example_interfaces`（用于示例服务 `AddTwoInts`）：

```bash
cd ~/ros2-ws/src
ros2 pkg create --build-type ament_python ros2_basics_demo \
  --dependencies rclpy std_msgs example_interfaces
```

生成的包结构大致如下：

```
ros2_basics_demo/
  package.xml
  setup.cfg
  setup.py
  resource/ros2_basics_demo
  ros2_basics_demo/__init__.py
```

---

## 4. 编写节点与服务

进入包目录，新增 4 个 Python 节点文件。

```bash
cd ~/ros2-ws/src/ros2_basics_demo/ros2_basics_demo
```

### 4.1 发布者：`talker.py`（发布到 `/chatter`）

```python
# ros2_basics_demo/talker.py
import platform
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class MinimalPublisher(Node):
    def __init__(self):
        super().__init__('talker')
        self.publisher_ = self.create_publisher(String, 'chatter', 10)
        self.timer = self.create_timer(0.5, self.timer_callback)  # 2Hz
        self.count = 0

    def timer_callback(self):
        msg = String()
        msg.data = f'Hello from {platform.node()} #{self.count}'
        self.publisher_.publish(msg)
        self.get_logger().info(f'Published: "{msg.data}"')
        self.count += 1

def main(args=None):
    rclpy.init(args=args)
    node = MinimalPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
```

### 4.2 订阅者：`listener.py`（订阅 `/chatter`）

```python
# ros2_basics_demo/listener.py
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class MinimalSubscriber(Node):
    def __init__(self):
        super().__init__('listener')
        self.subscription = self.create_subscription(
            String, 'chatter', self.callback, 10)
        self.subscription  # prevent unused variable warning

    def callback(self, msg: String):
        self.get_logger().info(f'I heard: "{msg.data}"')

def main(args=None):
    rclpy.init(args=args)
    node = MinimalSubscriber()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
```

### 4.3 服务端：`add_two_ints_server.py`（提供 `/add_two_ints`）

```python
# ros2_basics_demo/add_two_ints_server.py
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

class AddTwoIntsServer(Node):
    def __init__(self):
        super().__init__('add_two_ints_server')
        self.srv = self.create_service(AddTwoInts, 'add_two_ints', self.handle)

    def handle(self, request: AddTwoInts.Request, response: AddTwoInts.Response):
        response.sum = request.a + request.b
        self.get_logger().info(f'Request: {request.a} + {request.b} = {response.sum}')
        return response

def main(args=None):
    rclpy.init(args=args)
    node = AddTwoIntsServer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
```

### 4.4 客户端：`add_two_ints_client.py`（调用 `/add_two_ints`）

```python
# ros2_basics_demo/add_two_ints_client.py
import sys
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts

class AddTwoIntsClient(Node):
    def __init__(self, a: int, b: int):
        super().__init__('add_two_ints_client')
        self.cli = self.create_client(AddTwoInts, 'add_two_ints')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Service not available, waiting...')
        self.req = AddTwoInts.Request()
        self.req.a = a
        self.req.b = b

    def send_request(self):
        future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, future)
        return future.result()

def main(args=None):
    rclpy.init(args=args)
    if len(sys.argv) != 3:
        print('用法: ros2 run ros2_basics_demo add_two_ints_client <a> <b>')
        return
    a = int(sys.argv[1]); b = int(sys.argv[2])
    node = AddTwoIntsClient(a, b)
    resp = node.send_request()
    node.get_logger().info(f'Result: {a} + {b} = {resp.sum}')
    node.destroy_node()
    rclpy.shutdown()
```

---

## 5. 注册可执行入口（`setup.py`）

打开包根目录下的 `setup.py`，在 `entry_points` 增加 4 个可执行脚本：

```python
# ~/ros2-ws/src/ros2_basics_demo/setup.py
from setuptools import setup

package_name = 'ros2_basics_demo'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
         ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='you',
    maintainer_email='you@example.com',
    description='ROS 2 basics: talker, listener, add_two_ints service & client',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'talker = ros2_basics_demo.talker:main',
            'listener = ros2_basics_demo.listener:main',
            'add_two_ints_server = ros2_basics_demo.add_two_ints_server:main',
            'add_two_ints_client = ros2_basics_demo.add_two_ints_client:main',
        ],
    },
)
```

> `package.xml` 里 `rclpy`、`std_msgs`、`example_interfaces` 依赖已由 `ros2 pkg create` 帮你写好；如需新增依赖，记得同时更新 `package.xml` 与 `setup.py`。

---

## 6. 构建与运行

### 6.1 构建

```bash
cd ~/ros2-ws
# 确保已加载 ROS 2 环境
source /opt/ros/$ROS_DISTRO/setup.bash

colcon build --symlink-install
# 构建成功后，加载本工作空间环境
source install/setup.bash
```

> 每次新增/修改入口脚本或依赖，记得重新 `colcon build` 并 `source install/setup.bash`。

### 6.2 运行发布者与订阅者

打开两个终端（都要 `source` 工作空间环境）：

**终端 A（发布者）**

```bash
source ~/ros2-ws/install/setup.bash
ros2 run ros2_basics_demo talker
```

**终端 B（订阅者）**

```bash
source ~/ros2-ws/install/setup.bash
ros2 run ros2_basics_demo listener
```

可用 CLI 观察话题数据：

```bash
ros2 topic list
ros2 topic echo /chatter
```

### 6.3 运行服务与客户端

**终端 C（服务端）**

```bash
source ~/ros2-ws/install/setup.bash
ros2 run ros2_basics_demo add_two_ints_server
```

**终端 D（客户端）**

```bash
source ~/ros2-ws/install/setup.bash
ros2 run ros2_basics_demo add_two_ints_client 7 35
# 期望输出：Result: 7 + 35 = 42
```

也可以用命令行直接调用服务（无需客户端节点）：

```bash
ros2 service list
ros2 service call /add_two_ints example_interfaces/srv/AddTwoInts "{a: 3, b: 9}"
```

---

## 7. （可选）添加一个简单的 launch 文件

如果想一次拉起 talker + listener，新建：

```bash
mkdir -p ~/ros2-ws/src/ros2_basics_demo/launch
nano ~/ros2-ws/src/ros2_basics_demo/launch/demo_launch.py
```

填入：

```python
# launch/demo_launch.py
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(package='ros2_basics_demo', executable='talker', name='talker'),
        Node(package='ros2_basics_demo', executable='listener', name='listener'),
    ])
```

把它安装到包里：在 `setup.py` 的 `data_files` 增加一行（与其他条目并列）：

```python
('share/' + package_name + '/launch', ['launch/demo_launch.py']),
```

然后重建并运行：

```bash
cd ~/ros2-ws && colcon build && source install/setup.bash
ros2 launch ros2_basics_demo demo_launch.py
```

---

## 8. 常见问题排查

* **明明编译过但找不到可执行**：忘了 `source install/setup.bash`；或修改了 `entry_points` 却没重建。
* **话题没数据**：确认 talker 正在运行、话题名一致（都是 `chatter`），`ros2 topic list` 查看是否存在。
* **服务不可用**：客户端启动时会等待服务注册；确认服务端处于运行态，或用 `ros2 service list` 检查。
* **环境冲突**：同机多发行版并存时，务必检查当前 `source` 的是哪个 `$ROS_DISTRO`。

---

## 9. 拓展与思考

* 把 `String` 换成自定义消息（在 `msg/` 里定义，再修改 `package.xml` 与 `setup.py`）。
* 给 `listener` 加一点简单“业务逻辑”，例如统计消息速率、写入日志文件。
* 在服务中引入参数服务器（`declare_parameter/get_parameter`），比如设置一个偏置量 `bias`，返回 `a+b+bias`。
* 尝试用 `rqt_graph` / `ros2 doctor` 观察图结构与健康状态。

---

**恭喜完成本节课！你已掌握在虚拟机环境下创建 ROS 2 工作空间、编写节点、发布/订阅话题与提供/调用服务的完整最小闭环。**
