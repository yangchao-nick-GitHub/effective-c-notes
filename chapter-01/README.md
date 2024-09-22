# 条款01: 视C++为一个语言联邦

C++作为语言联邦的几个组成部分:
**a.c:**
C++保留了C语言的核心语法和特性，如基本数据类型、指针操作、控制结构等

**b.面向对象的C++ (Object-Oriented C++):**
引入了类的概念，允许封装数据和方法。
支持继承和多态性，允许创建层次化的类结构，并通过虚函数实现运行时多态。

**c.模板C++ (Template C++):**
提供了模板机制，使得可以编写泛型代码。

**d.标准模板库 (Standard Template Library, STL):**
是一组模板类和函数，提供了容器、算法和迭代器等工具。

# 条款02: 尽量以const, enum, inline 替换 #define
**常量替换#define 有两种用法:**
a.常量指针通常这样定义 const char * const hello = "hello world";  两个const
b.class 定义常量， 通常 定义成static const, 如果想在声明时初始化static const 变量， 可以使用
constexpr， static constexpr float pi = 3.14;

# 条款03: 尽可能使用const
const优势：
使用const明确告知编译器和程序员该值保持不变
const 修饰函数返回值 参数 和函数自身, 返回值时引用或者指针时使用const修饰返回值才有意义
const 修饰成员函数， 有几点优势和必要性
a.保护对象内容
b.一些重载operator[]的类，一般有两个版本，如
    const char& operator[](size_t ops) const // 供const对象调用
    char& operator[](size_t ops)    // 供non-const对象调用
const 对象应该调用 const版本的operator[]函数 保护对象内容，这时候必须要有 const 版本的成员函数
这是因为const对象只能调用const成员函数