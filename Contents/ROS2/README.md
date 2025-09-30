# ROS2 教程：从入门到实战

> **系统要求**：Ubuntu 22.04 + ROS2 Humble
>
> 本教程专为 Ubuntu 22.04 系统配置 ROS2 Humble 发行版
>
> 上课可能会过快导致底层的东西和原理不一定能讲到，也推荐阅读一下 ROS2 [官方文档](https://docs.ros.org/en/rolling/index.html)和[小鱼大佬写的中文文档](https://fishros.com/d2lros2/#/)。

---

## 1. Linux 基础

- 介绍 Linux 与 Ubuntu 22.04
- 安装
- 基本指令

---

## 2. ROS2 入门

[官方环境配置文档+初体验Examples(Ubuntu 22.04 ROS2 Humble deb packages)](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html)
> 跟着步骤走到 Next steps after installing 之前

### 节点，包，工作空间介绍

[概念介绍](https://fishros.com/d2lros2/#/humble/chapt2/get_started/1.ROS2%E8%8A%82%E7%82%B9%E4%BB%8B%E7%BB%8D)

### 节点通信

#### Publisher && Subscribe

[链接](https://fishros.com/d2lros2/#/humble/chapt3/get_started/1.ROS2%E8%AF%9D%E9%A2%98%E5%85%A5%E9%97%A8)

#### Server && Client

[链接](https://fishros.com/d2lros2/#/humble/chapt3/get_started/4.ROS2%E6%9C%8D%E5%8A%A1%E5%85%A5%E9%97%A8)

---

## 3. 创建工作空间（Workspace）

```bash
# 建立一个 ROS 2 工作空间
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws
```

> 工作空间标准结构为 `ros2_ws/src`。之后所有包都放在 `src` 下面，用 `colcon build` 统一构建。

---

## 4. 基础编程示例

### 4.1 简单节点编写

```cpp
#include "rclcpp/rclcpp.hpp"

int main(int argc, char **argv)
{
    /* 初始化rclcpp  */
    rclcpp::init(argc, argv);
    /*产生一个node_01的节点*/
    auto node = std::make_shared<rclcpp::Node>("node_01");
    // 打印一句自我介绍
    RCLCPP_INFO(node->get_logger(), "node_01节点已经启动.");
    /* 运行节点，并检测退出信号 Ctrl+C*/
    rclcpp::spin(node);
    /* 停止运行 */
    rclcpp::shutdown();
    return 0;
}
```

### 4.2 CMakeLists.txt 介绍

> [reference blog](https://blog.csdn.net/qq_38410730/article/details/102477162)

```cmake
project(name_of_your_file)                                          #必须设置变量，下面的代码都可以用到
set(GOOGLE_PROTOBUF_DIR ${PROJECT_SOURCE_DIR}/protobuf)
add_subdirectory(子文件夹名称)                         #父目录必须，子目录不必

add_library(库文件名称 STATIC 文件)                    #通常子目录(二选一)
add_executable(可执行文件名称 文件)                     #通常父目录(二选一)

#规定.h头文件路径
include_directories(路径)                              #必须
link_directories(路径)                                 #必须

target_link_libraries(库文件名称/可执行文件名称 链接的库文件名称)       #必须
```

---

## 5. 话题通信

> [code from here](https://fishros.com/d2lros2/#/humble/chapt3/get_started/2.%E8%AF%9D%E9%A2%98%E4%B9%8BRCLCPP%E5%AE%9E%E7%8E%B0)

### 5.1 创建话题包

在 `src` 下新建一个 cpp 包，依赖 `rclcpp`、`std_msgs`：

```bash
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_cmake ros2_topic_demo \
  --dependencies rclcpp std_msgs
```

- pkg create 是创建包的意思
- --build-type 用来指定该包的编译类型，一共有三个可选项 ament_python、ament_cmake、cmake
- --dependencies 指的是这个功能包的依赖，这里给了一个 ros2 的 C++客户端接口 rclcpp

生成的包结构大致如下：

```text
ros2_topic_demo/
  CMakeLists.txt
  package.xml
  src/
  include/ros2_topic_demo/
```

### 5.2 编写话题包

进入 `src/ros2_topic_demo/src/` 目录，新增 2 个 `.cpp` 文件。

#### Publisher：talker.cpp

```cpp
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicPublisher01 : public rclcpp::Node
{
public:
    // 构造函数,有一个参数为节点名称
    TopicPublisher01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());
        // 创建发布者
        command_publisher_ = this->create_publisher<std_msgs::msg::String>("command", 10);
        // 创建定时器，500ms为周期，定时发布
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&TopicPublisher01::timer_callback, this));
    }

private:
    void timer_callback()
    {
        // 创建消息
        std_msgs::msg::String message;
        message.data = "forward";
        // 日志打印
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        // 发布消息
        command_publisher_->publish(message);
    }
    // 声名定时器
    rclcpp::TimerBase::SharedPtr timer_;
    // 声明话题发布者
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*产生一个的节点*/
    auto node = std::make_shared<TopicPublisher01>("topic_publisher_01");
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
```

#### Subscriber：listener.cpp

```cpp
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicSubscribe01 : public rclcpp::Node
{
public:
    TopicSubscribe01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());
          // 创建一个订阅者订阅话题
        command_subscribe_ = this->create_subscription<std_msgs::msg::String>("command", 10, std::bind(&TopicSubscribe01::command_callback, this, std::placeholders::_1));
    }

private:
     // 声明一个订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscribe_;
     // 收到话题数据的回调函数
    void command_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        double speed = 0.0f;
        if(msg->data == "forward")
        {
            speed = 0.2f;
        }
        RCLCPP_INFO(this->get_logger(), "收到[%s]指令，发送速度 %f", msg->data.c_str(),speed);
    };
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*产生一个的节点*/
    auto node = std::make_shared<TopicSubscribe01>("topic_subscribe_01");
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
```

### 5.3 配置文件

#### package.xml

在 buildtool 依赖项后添加一个新行 ament_cmake，并粘贴与节点的包含语句相对应的以下依赖项：

```xml
<depend>rclcpp</depend>
<depend>std_msgs</depend>
```

#### CMakeLists.txt

在 `ros2_topic_demo/CMakeLists.txt` 里，加入 2 个可执行文件：

```cmake
cmake_minimum_required(VERSION 3.8)
project(ros2_topic_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(talker src/talker.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(listener src/listener.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

install(TARGETS
  talker
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS
  listener
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
```

### 5.4 构建与运行

#### 构建

```bash
cd ~/ros2_ws
colcon build --packages-select ros2_topic_demo
source install/setup.bash
```

#### 运行发布/订阅

> 开两个终端

```bash
# 终端A（发布者）
ros2 run ros2_topic_demo talker

# 终端B（订阅者）
ros2 run ros2_topic_demo listener
```

可用 CLI 观察话题数据：

```bash
ros2 topic list
ros2 topic echo /command
```

### 5.5 Launch 文件

如果想一次拉起 talker + listener：

```bash
mkdir -p ~/ros2_ws/src/ros2_topic_demo/launch
nano ~/ros2_ws/src/ros2_topic_demo/launch/demo_launch.py
```

写入：

```python
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(package='ros2_topic_demo', executable='talker', name='talker'),
        Node(package='ros2_topic_demo', executable='listener', name='listener'),
    ])
```

然后在 CMakeLists.txt 里安装它：

```cmake
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})
```

运行：

```bash
colcon build && source install/setup.bash
ros2 launch ros2_topic_demo demo_launch.py
```

---

## 6. 服务通信

> ament_cmake 类型功能包导入消息接口分为三步：
>
> 1. 在 CMakeLists.txt 中导入，具体是先 find_packages 再 ament_target_dependencies。
> 2. 在 packages.xml 中导入，具体是添加 depend 标签并将消息接口写入。
> 3. 在代码中导入，C++中是#include"消息功能包/xxx/xxx.hpp"。

[code from here](https://fishros.com/d2lros2/#/humble/chapt3/get_started/5.%E6%9C%8D%E5%8A%A1%E4%B9%8BRCLCPP%E5%AE%9E%E7%8E%B0)

### 6.1 创建服务包

```bash
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_cmake example_service_rclcpp \
  --dependencies rclcpp example_interfaces

touch example_service_rclcpp/src/service_server_01.cpp
touch example_service_rclcpp/src/service_client_01.cpp
```

### 6.2 编写服务包

#### Server：service_server_01.cpp

```cpp
#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

class ServiceServer01 : public rclcpp::Node {
public:
  ServiceServer01(std::string name) : Node(name) {
    RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());
    // 创建服务
    add_ints_server_ =
      this->create_service<example_interfaces::srv::AddTwoInts>(
        "add_two_ints_srv",
        std::bind(&ServiceServer01::handle_add_two_ints, this,
                  std::placeholders::_1, std::placeholders::_2));
  }

private:
  // 声明一个服务
  rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr
    add_ints_server_;

  // 收到请求的处理函数
  void handle_add_two_ints(
    const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
    std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response) {
    RCLCPP_INFO(this->get_logger(), "收到a: %ld b: %ld", request->a,
                request->b);
    response->sum = request->a + request->b;
  };
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ServiceServer01>("service_server_01");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
```

#### Client: service_client_01.cpp

```cpp
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class ServiceClient01 : public rclcpp::Node {
public:
  // 构造函数,有一个参数为节点名称
  ServiceClient01(std::string name) : Node(name) {
    RCLCPP_INFO(this->get_logger(), "节点已启动：%s.", name.c_str());
    // 创建客户端
    client_ = this->create_client<example_interfaces::srv::AddTwoInts>(
      "add_two_ints_srv");
  }

  void send_request(int a, int b) {
    RCLCPP_INFO(this->get_logger(), "计算%d+%d", a, b);

    // 1.等待服务端上线
    while (!client_->wait_for_service(std::chrono::seconds(1))) {
      //等待时检测rclcpp的状态
      if (!rclcpp::ok()) {
        RCLCPP_ERROR(this->get_logger(), "等待服务的过程中被打断...");
        return;
      }
      RCLCPP_INFO(this->get_logger(), "等待服务端上线中");
    }

    // 2.构造请求的
    auto request =
      std::make_shared<example_interfaces::srv::AddTwoInts_Request>();
    request->a = a;
    request->b = b;

    // 3.发送异步请求，然后等待返回，返回时调用回调函数
    client_->async_send_request(
      request, std::bind(&ServiceClient01::result_callback_, this,
                         std::placeholders::_1));
  };

private:
  // 声明客户端
  rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;

  void result_callback_(
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture
      result_future) {
    auto response = result_future.get();
    RCLCPP_INFO(this->get_logger(), "计算结果：%ld", response->sum);
  }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  /*产生一个的节点*/
  auto node = std::make_shared<ServiceClient01>("service_client_01");
  /* 运行节点，并检测退出信号*/
  node->send_request(5, 6);
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
```

### 6.3 配置与构建

#### package.xml && CMakeLists.txt

按照话题包的方式配置，添加 `example_interfaces` 依赖。

#### 构建运行

```bash
cd ~/ros2_ws
colcon build --packages-select example_service_rclcpp
source install/setup.bash

# 运行服务端（终端A）
ros2 run example_service_rclcpp service_server_01

# 运行客户端（终端B）
ros2 run example_service_rclcpp service_client_01
```

也可以用命令行直接调用服务（无需客户端节点）：

```bash
ros2 service list
ros2 service call /add_two_ints_srv example_interfaces/srv/AddTwoInts "{a: 3, b: 9}"
```

---

## 7. 常见问题排查

- **明明编译过但找不到可执行**：忘了 `source install/setup.bash`；或修改了入口脚本却没重建。
- **话题没数据**：确认 talker 正在运行、话题名一致，`ros2 topic list` 查看是否存在。
- **服务不可用**：客户端启动时会等待服务注册；确认服务端处于运行态，或用 `ros2 service list` 检查。
- **环境冲突**：同机多发行版并存时，务必检查当前 `source` 的是 ROS2 Humble（`/opt/ros/humble/setup.bash`）。

---

## 8. 拓展与思考

- 把 `String` 换成自定义消息（在 `msg/` 里定义，再修改 `package.xml` 与 `CMakeLists.txt`）。
- 给 `listener` 加一点简单"业务逻辑"，例如统计消息速率、写入日志文件。
- 在服务中引入参数服务器（`declare_parameter/get_parameter`），比如设置一个偏置量 `bias`，返回 `a+b+bias`。
- 尝试用 `rqt_graph` / `ros2 doctor` 观察图结构与健康状态。

---

**恭喜完成本教程！你已掌握在 Ubuntu 环境下创建 ROS 2 工作空间、编写节点、发布/订阅话题与提供/调用服务的完整最小闭环。**
