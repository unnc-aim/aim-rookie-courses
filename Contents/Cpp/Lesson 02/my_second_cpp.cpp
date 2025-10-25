//
// Created by Anon on 2025/10/25.
//

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;


/*
函数的基本语法：
返回值类型 函数名 （参数列表）
{
       函数体语句
       return表达式
}
 */

int test_add(int a, int b)
{
    // 有输入参数，有返回值的函数
    cout << "[函数传入和返回值-求和演示：]" << endl;
    int sum = a + b;
    return sum;
}

void cite_pointer() {
    // 引用和指针（pointer，简写为ptr)
    cout << "[引用和指针演示：]" << endl;
    string band1 = "poppin party";
    string &live1 = band1; // 引用
    cout << "band1: " << live1 << endl;
    cout << "band1的内存地址为：" << &band1 << endl;
    cout << "live1的内存地址为：" << &live1 << endl;
    cout << string(20, '*') << endl;

    // 指针anime1，存储变量band1的内存地址，使用*创建
    string* anime1 = nullptr; // 指针初始化为空指针

    anime1 = &band1;
    cout << "anime1指针存储的内存地址为：" << anime1 << endl;
    // 下面输出流当中，使用*解引用运算符，访问anime1指针所指向的内存地址的值
    cout << "通过指针anime1访问band1的值为：" << *anime1 << endl;
    cout << string(20, '*') << endl;

    // 通过指针修改原始变量的值
    *anime1 = "afterglow";
    cout << "通过指针修改后，band1的值为：" << band1 << endl;

}

// 指针作为函数参数，可以修改实参的值
// 值传递，输入函数的是值
void swap1(int a ,int b)
{
    int temp = a;
    a = b;
    b = temp;
}

// 地址传递，输入函数的是指针，实际是指针指向的地址包含的值，可以修改实参（即操作内存空间）
void swap2(int* p1, int* p2)
{
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// 1. 将 struct 关键字改为 class
// 按照惯例，class 的名称通常以大写字母开头
class Band {
    // 1. 将数据成员设为 private
    // 这是封装的核心：将内部数据保护起来，防止外部直接、随意地修改
    // 乐队成员不能随意换来换去！
private:
    string guitar;
    string vocal;
    string drum;
    string bass;
    string keyboard;

    // 2. 添加 public 访问修饰符
    // class 的成员默认是 private，必须明确指定哪些部分是外界可以访问的
public:
    // 构造函数：用于创建对象的接口，必须是 public
    Band(string gt, string vo, string dr, string ba, string key) {
        guitar = std::move(gt);
        vocal = std::move(vo);
        drum = std::move(dr);
        bass = std::move(ba);
        keyboard = std::move(key);
        cout << "组建了一支新乐队！";
    }

    // 成员函数：对象的功能接口，也必须是 public
    void print_info() {
        std::cout << "吉他手：" << guitar
                  << "，主唱：" << vocal
                  << "，鼓手：" << drum
                  << "，贝斯手：" << bass
                  << "，键盘手：" << keyboard << std::endl;
    }

    void live() {
        cout << "成员们正在开live。" << endl;
    }

    void get_guitar() {
        cout << "当前乐队的吉他手：" << guitar << endl;
    }

    void set_keyboard_anon() {
        keyboard = "anon";
    }
};

// 继承：派生类 roselia 继承自基类 Band

class MofoBand : public Band {
public:
    // 子类必须定义自己的构造函数
    // 它的参数列表需要包含初始化“父类部分”和“子类部分”所需的所有信息
    MofoBand(string gt, string vo, string dr, string ba, string key, string actor)
        // 使用成员初始化列表语法，调用父类的构造函数
        // : Band(...) 的意思就是：“请用后面括号里的这些参数，去调用父类 Band 的构造函数”
        // 这样就把父类部分的初始化工作委托给了父类自己
        : Band(std::move(gt), std::move(vo), std::move(dr), std::move(ba), std::move(key))
    {
        // 4. 在子类构造函数的函数体内，只处理子类自己新增的成员
        vocal_actor = std::move(actor);
        cout << "[MofoBand Constructor Called]\n"; // 加个打印
    }

    // 子类可以有自己的新方法
    void print_mofo_info() {
        // 子类可以调用父类的 public 方法
        print_info();
        cout << "主唱的声优：" << vocal_actor << endl;
    }

protected:
    // 当前类不能访问，继承类可以访问、操作
    // 子类新增的成员
    string vocal_actor;
};

class MofoBand_New : public MofoBand {
public:
    MofoBand_New(string gt, string vo, string dr, string ba, string key, string actor)
        : MofoBand(std::move(gt), std::move(vo), std::move(dr), std::move(ba), std::move(key), std::move(actor)){
    }

    // 演示：在子类的成员函数内部，可以自由访问 protected 成员
    // this->vocal_actor 的意思就是：“当前这个对象的 vocal_actor 成员”
    void change_actor(const string& new_actor) {
        cout << "[内部] 正在将声优从 '" << this->vocal_actor << "' 修改为 '" << new_actor << "'" << endl;
        this->vocal_actor = new_actor; // 正确！因为这里是 MofoBand_New 类的内部
    }
};

void class_band() {
    // 创建类的实例（也叫“对象”）的方式和 struct 完全一样
    Band ave_mujica("睦", "初音", "喵梦", "海铃", "祥");
    ave_mujica.print_info();
    ave_mujica.live();
    cout << string(20, '*') << endl;

    // vector 的用法也完全一样，只是存储的类型从 band 变成了 Band
    std::vector<Band> live_bands;
    live_bands.emplace_back("日菜", "彩", "麻弥", "千圣", "伊芙");
    live_bands.emplace_back("纱夜", "友希那", "亚子", "莉莎", "燐子");

    cout << "\n--- Live Bands Lineup ---\n";
    // 基于范围的 for 循环，用法也完全一样
    // 对于live_bands这个vector中的每一个Band类型的元素，依次将它的引用赋值给变量p，然后执行循环体内的代码
    // &p表示p是容器中原始对象的引用，而不是一个副本，是为了避免拷贝整个Band对象，提高效率
    for (Band& p : live_bands) {
        p.print_info();
    }
    cout << string(20, '*') << endl;

    // 调用访问类的成员（私有）的函数（公开）
    ave_mujica.get_guitar();
    // 通过公开的类的成员函数，修改私有成员
    ave_mujica.set_keyboard_anon();
    ave_mujica.print_info();
    cout << string(20, '*') << endl;

    MofoBand morfonica("透子", "真白", "筑紫", "七深", "瑠唯", "进藤天音");
    // 调用子类自己的方法
    morfonica.print_mofo_info();
    cout << string(20, '*') << endl;

    // 操作protected属性
    MofoBand_New lovelive("透子", "真白", "筑紫", "七深", "瑠唯", "进藤天音");
    lovelive.change_actor("佐仓绫音"); // 调用我们新增的 public 函数
    lovelive.print_mofo_info();
}


int main() {
    #ifdef _WIN32
        system("chcp 65001");       // windows下，把系统的字符集切换为 65001 (UTF-8)，避免运行时中文乱码
    #endif

    // int sum1 = test_add(1, 2);
    // cout << "test_add函数返回的和为：" << sum1 << endl;
    //
    // cout << string(50, '-') << endl;    // 输出50个'-'作为分隔线
    // cite_pointer();

    // cout << string(50, '-') << endl;    // 输出50个'-'作为分隔线
    // int a = 10;
    // int b = 20;
    // swap1(a, b); // 值传递不会改变实参
    // cout << "a = " << a << endl;
    // cout << "b = " << b << endl;
    // swap2(&a, &b); //地址传递会改变实参
    // cout << "a = " << a << endl;
    // cout << "b = " << b << endl;

    cout << string(50, '-') << endl;    // 输出50个'-'作为分隔线
    class_band();


    // system("pause");
    return 0;
}

