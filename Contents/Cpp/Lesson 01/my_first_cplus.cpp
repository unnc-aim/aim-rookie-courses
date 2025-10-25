//
// Created by Anon on 2025/10/25.
//

#include <iomanip>                              // 包含输入输出格式库, 支持setprecision等操作
#include <iostream>                             // 包含输入输出流库
#include <cmath>                                // 包含数学库，支持sqrt等数学函数
#include <array>                                // 包含数组库
#include <string>                               // 包含字符串库

#include "stupid_namespace.h"

// 打开C++的标准库命名空间（std），能直接使用cout、vector等标准库里的名字，而无需每次都写std::前缀。
using namespace std;                            // 懒，按规范最好别这么写

void new_new(){
    // 体验最简单的C++输出
    cout << "Hello, C++! 1\n";
}

/*
1. cout << "hello world!" << endl; 不仅输出字符串"hello world!"，
还在末尾添加了一个换行符endl，表示输出结束并换行，并强制刷新 (flush) 输出缓冲区。
可以写cout << "hello world!\n";，换行但不强制刷新缓冲区；
也可以直接写cout << "hello world!";，不换行也不刷新缓冲区。

2. cout中的<<是插入运算符，表示将右侧的内容插入到左侧的输出流中。
例如，cout << "Hello" 表示把右边的字符串"Hello"插入到标准输出流cout中，从而显示在屏幕上。
同理，cin中的>>是提取运算符，表示从左侧的输入流中提取数据到右侧的变量中。
例如，cin >> x 表示从标准输入流cin中提取数据，并存储到变量x中。

3. cin >> x >> y; 可以连续从输入流中提取多个值，依次存储到变量x和y中。
这相当于先执行cin >> x;，然后再执行cin >> y;。
输入时，可以使用空格、敲击回车（换行）、按tab（制表符）等分隔赋给不同变量的值。
*/
void input_int() {
    // 了解整数和基本输入输出
    int x = 0;
    int y = 0;
    cout << "[请输入2个整数：]" << endl;
    cin >> x >> y;
    cout << "[You entered: " << x << "; " << y << "]" << endl;
}

void input_variable() {
    // 了解不同变量类型
    double a = 0.0;
    char b = ' ';
    string c = "mutsumi";

    cout << "[请分别输入一个浮点数a，一个英文单字符b，一个英文字符串c：]" << endl;
    cin >> a >> b >> c;
    cout << fixed << setprecision(2) << "[你输入的内容是：a（保留2位小数）= "
    << a << "; b = " << b << "; c = " << c << "]" << endl;
}

void calculate() {
    // 了解运算符
    // 取模
    cout << "[除法与取模计算演示：]" << endl;
    cout << "3 % 2 = " << (3 % 2) << endl; // 取余数/模，只适用于整数
    cout << "3 / 2 = " << (3 / 2) << endl; // 除法，整数除以整数，损失小数位
    cout << "3.14 / 2 = " << (3.14 / 2) << endl; // 除法，浮点数除以整数，保留小数位


    // 赋值，比较，布尔值
    cout << string(10, '*') << endl;
    int x = 10;
    int y = 1;
    cout << "[赋值，比较，布尔值演示：]" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "y等于x吗？" << (y == x) << endl; // 不等于，输出0（false）
    cout << "y小于x吗？" << (y <= x) << endl; // 不等于，输出0（false）

    cout << string(10, '*') << endl;
    y = x;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "y不等于x吗？" << (y != x) << endl; // 不等于，输出0（false）

    // 逻辑，与或非
    cout << string(10, '*') << endl;
    cout << "[与或非演示：]" << endl;
    cout << "x大于3和x<15都成立吗？" << (x > 3 && x < 15) << endl;
    cout << "x大于3和x<15都不成立吗？" << !(x > 3 && x < 15) << endl;
    cout << "y小于3或y>15有一个成立吗？" << (y < 3 || y < 15) << endl;

    // 简单数学运算
    cout << string(10, '*') << endl;
    cout << "[简单数学运算演示：]" << endl;
    cout << "2的平方根是：" << sqrt(2) << endl;
    cout << "3的立方是：" << pow(3, 3) << endl;
    cout << "2.5向上取整是：" << ceil(2.5) << endl;
    cout << "6.5向下取整是：" << floor(6.5) << endl;

    // 自加自减
    cout << string(10, '*') << endl;
    cout << "[自加自减演示：]" << endl;
    cout << "x = " << x << endl;
    x++;    // x 自加 1
    cout << "x++ 后，x = " << x << endl;
    x += 5; // x 自加 5
    cout << "x += 5 后，x = " << x << endl;
    x--;    // x 自减 1
    cout << "x-- 后，x = " << x << endl;
}

void if_and_for() {
    // 了解条件和循环语句
    // 条件：if (条件) 然后 { 执行代码 }
    int x = 1;
    cout << "[if/条件语句演示：]" << endl;
    cout << "[请输入一个整数值：]" << endl;
    cin >> x;
    if (x > 0) {
        cout << "x是正数" << endl;
    } else if (x < 0) {
        cout << "x是负数" << endl;
    } else {
        cout << "x是零" << endl;
    }

    // 循环：for (循环变量初始值; 继续循环的条件; 迭代操作/更新) { 执行代码 }
    // 10分钟速通c++基础 04:47
    cout << string(20, '*') << endl;
    cout << "[for/循环语句演示：]" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << "这是第 " << i << " 次循环" << endl;
    }
}

/*
定义在函数内部的是局部变量，储存在内存的栈空间里，函数执行结束后，这些变量会被自动销毁，释放内存。
栈空间很小，但一个用于图像处理的数组，例如1920*1080的像素点数组，需要的空间可能是：
1920 * 1080 * 4 字节（整型int，一个是4字节） = 8,294,400 字节 ≈ 8 MB
这可能超过了栈空间的容量，导致程序崩溃。
------------------------------------
放在函数外部，即全局变量，储存在内存的全局数据区，程序运行期间一直存在，直到程序结束才释放内存。
全局变量的内存空间较大，可以存储大型数据结构，如大数组、大对象等。
所以最好把数组的定义放在函数外边。在函数里可以正常对数组进行各种操作。
------------------------------------
{}大括号仅在定义数组的时候使用，是初始化数组，不能用于给数组赋新值。
 */

int score[5] = {94, 87, 50}; // 长度为固定不变的5，包含5个整数的数组

// 现代c++推荐使用std::array，功能更强大，语法更规范
// 当然还有可变长度的std::vector，功能更强大，但语法更复杂.
std::array <int, 5> score_new;

void shuzu() {
    // 了解数组和字符串
    cout << string(20, '*') << endl;
    cout << "[数组演示：]" << endl;
    cout << "数组score的内容是：" << endl;
    for (int i = 0; i < 5; i++) // 下标/索引从0开始，到4结束，共5个元素
    {
        cout << score[i] << " "; // 用循环输出数组中的每个元素
    }
    cout << endl;

    // 数组赋值
    cout << string(20, '*') << endl;
    int new_scores[] = {80, 85, 90, 95, 100}; // 定义并初始化一个新数组
    for (int i = 0; i < 5; i++) {
        score[i] = new_scores[i];
    }
    cout << "数组score的新内容是：" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << score[i] << " "; // 用循环输出数组中的每个元素
    }
    cout << endl;

    // 新数组赋值
    score_new = {1, 2, 3, 4, 5};
    cout << string(20, '*') << endl;
    cout << "现代数组score_new的内容是：" << endl;
    // 基于范围的for循环，对score_new数组中的每一元素，用变量j依次输出
    for (int j: score_new) {
        cout << j << " ";
    }
    cout << endl;
}

// 现代C++字符串操作，支持增删改查，现代数组std::vector支持类似操作
std::string mygo = "soyo,anon,taki,rana,tomori";
void str_modern() {
    // 了解现代字符串
    cout << string(20, '*') << endl;
    cout << "[字符串演示：]" << endl;

    // 查
    std::cout << mygo.at(3) << std::endl;     // 索引为3位置的字符，越界访问时抛出异常
    std::cout << mygo << std::endl;
    cout << string(20, '*') << endl;
    auto pos = mygo.find("anon"); // 查找 "anon"
    if (pos != std::string::npos) {
        std::cout << "'anon' found at position: " << pos << std::endl; // 输出 10
    } else {
        std::cout << "'anon' not found." << std::endl;
    }

    // 改
    cout << string(20, '*') << endl;
    mygo.replace(mygo.find("anon"), 4, "saki");
    std::cout << mygo << std::endl;    // 输出 "11423432"

    // 增
    cout << string(20, '*') << endl;
    mygo += ",下北泽第一突破手波奇酱"; // 末尾拼接
    std::cout << mygo << std::endl;

    cout << string(20, '*') << endl;
    mygo.insert(0, "阿诺,"); // 指定位置插入
    std::cout << mygo << std::endl;

    // 删
    cout << string(20, '*') << endl;
    auto saki_pos = mygo.find("saki"); // 查找saki，查不到返回std::string::npos
    if (saki_pos != std::string::npos) {
        mygo.erase(saki_pos, 5); // 删除 "saki"
    }
    std::cout << mygo << std::endl;

    cout << string(20, '*') << endl;
    mygo.clear();
    std::cout << "Length is now: " << mygo.length() << std::endl; // 输出 0
}


/*
main函数是C++程序执行的唯一入口，操作系统会从这里调用你的代码。
而前面的int则规定了这个函数在执行结束时，必须返回一个整数作为“退出状态码”给操作系统.
通常返回0代表程序已成功运行。
*/
int main() {
    // 主函数

    #ifdef _WIN32
        system("chcp 65001");       // windows下，把系统的字符集切换为 65001 (UTF-8)，避免运行时中文乱码
    #endif

    // namespace_test();
    // cout << string(50, '-') << endl;    // 输出50个'-'作为分隔线

    // new_new();
    // cout << string(50, '-') << endl;    // 输出50个'-'作为分隔线
    //
    // input_int();
    // cout << string(50, '-') << endl;    // 输出50个'-'作为分隔线
    //
    // input_variable();
    // cout << string(50, '-') << endl;    // 输出50个'-'作为分隔线
    //
    // test();
    // cout << string(50, '-') << endl;    // 输出50个'-'作为分隔线

    // calculate();
    // cout << string(50, '-') << endl;    // 输出50个'-'作为分隔线

    // if_and_for();
    // cout << string(50, '-') << endl;    // 输出50个'-'作为分隔线

    // shuzu();
    // cout << string(50, '-') << endl;    // 输出50个'-'作为分隔线

    str_modern();
    cout << string(50, '-') << endl;    // 输出50个'-'作为分隔线
    return 0;
}


