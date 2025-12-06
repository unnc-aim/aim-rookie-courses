# OpenCV C++ 教程

本教程涵盖了 OpenCV C++ 的一些基本操作。

## 1. `cv::Mat` 基础

`cv::Mat` 是 OpenCV 中用于存储图像和矩阵数据的核心数据结构。

- **创建 `cv::Mat` 对象**

  ```cpp
  // 创建一个 3x3 的 8 位单通道矩阵
  cv::Mat M(3, 3, CV_8UC1);

  // 创建一个 2 通道（复数）矩阵
  cv::Mat C = cv::Mat(3, 3, CV_32FC2, cv::Scalar(1, 3));

  // 从现有数据创建
  double data[] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7};
  cv::Mat D(2, 3, CV_64F, data);
  ```

- **加载和显示图像**

  ```cpp
  #include <opencv2/opencv.hpp>

  int main() {
      // 从文件加载图像
      cv::Mat image = cv::imread("path/to/your/image.jpg");

      if (image.empty()) {
          std::cout << "无法加载图像" << std::endl;
          return -1;
      }

      // 创建一个窗口来显示图像
      cv::namedWindow("图像", cv::WINDOW_AUTOSIZE);
      // 在窗口中显示图像
      cv::imshow("图像", image);

      // 等待按键
      cv::waitKey(0);

      return 0;
  }
  ```

## 2. 基本平移

平移是将图像沿 x 和 y 方向移动。

```cpp
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat src = cv::imread("path/to/your/image.jpg");
    if (src.empty()) { return -1; }

    int tx = 50;  // x 方向平移量
    int ty = 100; // y 方向平移量

    // 定义平移矩阵
    cv::Mat trans_mat = (cv::Mat_<double>(2, 3) << 1, 0, tx, 0, 1, ty);

    cv::Mat dst;
    // 应用仿射变换
    cv::warpAffine(src, dst, trans_mat, src.size());

    cv::imshow("原始图像", src);
    cv::imshow("平移后的图像", dst);
    cv::waitKey(0);

    return 0;
}
```

## 3. 颜色过滤

颜色过滤用于在图像中隔离特定颜色。通常在 HSV 颜色空间中进行操作。

```cpp
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat bgr_image = cv::imread("path/to/your/image.jpg");
    if (bgr_image.empty()) { return -1; }

    cv::Mat hsv_image;
    // 将 BGR 图像转换为 HSV 图像
    cv::cvtColor(bgr_image, hsv_image, cv::COLOR_BGR2HSV);

    // 定义要过滤的颜色范围 (例如：蓝色)
    cv::Scalar lower_blue(110, 50, 50);
    cv::Scalar upper_blue(130, 255, 255);

    cv::Mat mask;
    // 根据颜色范围创建掩码
    cv::inRange(hsv_image, lower_blue, upper_blue, mask);

    cv::Mat result;
    // 将掩码应用于原始图像
    cv::bitwise_and(bgr_image, bgr_image, result, mask);

    cv::imshow("原始图像", bgr_image);
    cv::imshow("颜色过滤结果", result);
    cv::waitKey(0);

    return 0;
}
```

## 4. 边缘检测

Canny 边缘检测是一种流行的边缘检测算法。

```cpp
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat src = cv::imread("path/to/your/image.jpg", cv::IMREAD_GRAYSCALE);
    if (src.empty()) { return -1; }

    cv::Mat edges;
    // 应用 Canny 边缘检测
    cv::Canny(src, edges, 100, 200); // minVal 和 maxVal

    cv::imshow("原始图像", src);
    cv::imshow("边缘", edges);
    cv::waitKey(0);

    return 0;
}
```

## 5. 二值化阈值

二值化阈值是一种将灰度图像转换为黑白图像的简单方法。

```cpp
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat src = cv::imread("path/to/your/image.jpg", cv::IMREAD_GRAYSCALE);
    if (src.empty()) { return -1; }

    cv::Mat binary_image;
    // 应用二值化阈值
    // 像素值 > 128 的设为 255 (maxVal)，否则设为 0
    cv::threshold(src, binary_image, 128, 255, cv::THRESH_BINARY);

    cv::imshow("原始图像", src);
    cv::imshow("二值化图像", binary_image);
    cv::waitKey(0);

    return 0;
}
```

## 6. 关键点检测

使用 ORB (Oriented FAST and Rotated BRIEF) 算法检测关键点。

```cpp
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

int main() {
    cv::Mat src = cv::imread("path/to/your/image.jpg", cv::IMREAD_GRAYSCALE);
    if (src.empty()) { return -1; }

    // 创建 ORB 检测器
    cv::Ptr<cv::ORB> orb = cv::ORB::create();

    std::vector<cv::KeyPoint> keypoints;
    // 检测关键点
    orb->detect(src, keypoints);

    cv::Mat img_keypoints;
    // 在图像上绘制关键点
    cv::drawKeypoints(src, keypoints, img_keypoints, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);

    cv::imshow("关键点", img_keypoints);
    cv::waitKey(0);

    return 0;
}
```
