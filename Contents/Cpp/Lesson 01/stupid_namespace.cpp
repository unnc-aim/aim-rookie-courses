//
// Created by Anon on 2025/10/25.
//

#include <iostream>

// 打开C++的标准库命名空间（std），能直接使用cout、vector等标准库里的名字，而无需每次都写std::前缀。
// 但这样做的代价是，如果自己的代码里定义了与标准库中同名的函数或变量，
// 就可能引发命名冲突，导致编译器不知道该使用哪一个。
using namespace std;                                 // 懒，按规范不能这么写

namespace mygo {
    struct std {
        int anon = 42;
    };
    int cin = 947;
    int cout = 310;
}

using namespace mygo;

void namespace_test(){
    // cout << "Hello, C++! 1\n";                     // 错误，命名冲突
    // std::cout << "Hello, C++! 2" << ::std::endl;   // 错误，命名空间冲突
    ::std::cout << "Hello, C++! 3" << ::std::endl;    // 正确，使用全局命名空间的std

    mygo::std saki;
    ::std::cout << saki.anon << ::std::endl;          // 正确

    ::std::cout << mygo::cin << ::std::endl;          // 正确
}


