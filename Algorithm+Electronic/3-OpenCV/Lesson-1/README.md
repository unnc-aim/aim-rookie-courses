# OpenCV Lesson-1：虚拟机环境下的人脸识别实战

## 1. 远程连接虚拟机

1. 获取虚拟机 IP 地址（在虚拟机终端执行）：

   ```bash
   ip addr show
   # 或
   ifconfig
   ```

2. 在本地终端通过 SSH 连接虚拟机：

   ```bash
   ssh your_username@虚拟机IP
   # 首次连接输入 yes，输入密码
   ```

## 2. 创建工作目录

```bash
mkdir -p ~/opencv-face-demo
cd ~/opencv-face-demo
```

## 3. Git 克隆代码仓库

（如有团队仓库可直接克隆，否则可用 OpenCV 官方示例仓库）

```bash
git clone https://github.com/opencv/opencv.git
# 或克隆你的项目仓库
git clone <your_repo_url>
```

## 4. 安装 CMake 与 OpenCV

```bash
sudo apt update
sudo apt install -y cmake g++ git
sudo apt install -y libopencv-dev python3-opencv
# 检查 OpenCV 版本
pkg-config --modversion opencv4
```

如需源码编译 OpenCV，可参考 [官方文档](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)。

## 5. 使用 AI 生成 C++ 人脸识别代码

### 示例：AI 生成的人脸识别 C++ 代码

```cpp
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "用法: ./face_detect <图片路径>" << std::endl;
        return -1;
    }
    cv::Mat img = cv::imread(argv[1]);
    if (img.empty()) {
        std::cout << "无法读取图片" << std::endl;
        return -1;
    }
    cv::CascadeClassifier face_cascade;
    face_cascade.load("/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml");
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(img, faces, 1.1, 3, 0, cv::Size(30, 30));
    for (auto& face : faces) {
        cv::rectangle(img, face, cv::Scalar(0, 255, 0), 2);
    }
    std::cout << "检测到 " << faces.size() << " 张人脸" << std::endl;
    cv::imwrite("result.jpg", img);
    return 0;
}
```

## 6. 编写 CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(face_detect)
find_package(OpenCV REQUIRED)
add_executable(face_detect main.cpp)
target_link_libraries(face_detect ${OpenCV_LIBS})
```

## 7. 编译与运行

```bash
# 假设 main.cpp 和 CMakeLists.txt 在 ~/opencv-face-demo
cd ~/opencv-face-demo
cmake .
make
# 运行（假设有 test.jpg）
./face_detect test.jpg
# 检查输出 result.jpg
```

## 8. 拓展与思考

- 尝试用不同图片测试
- 修改参数提升识别效果
- 尝试用 AI 生成更复杂的人脸识别功能（如摄像头实时检测）

---

**恭喜完成本节课！你已掌握 OpenCV 环境部署、C++项目构建与 AI 辅助开发的完整流程。**
