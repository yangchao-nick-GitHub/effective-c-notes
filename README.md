# effective-c-notes

## 让自己习惯C++
* 条款01: 视C++为一个语言联邦
* 条款02: 尽量以const, enum, inline 替换 #define
* 条款03: 尽可能使用const


### 条款01: 视C++为一个语言联邦

C++作为语言联邦的几个组成部分:
* C++保留了C语言的核心语法和特性，如基本数据类型、指针操作、控制结构等

* 面向对象的C++ (Object-Oriented C++):
引入了类的概念，允许封装数据和方法。
支持继承和多态性，允许创建层次化的类结构，并通过虚函数实现运行时多态。

* 模板C++ (Template C++):**
提供了模板机制，使得可以编写泛型代码。

* 标准模板库 (Standard Template Library, STL):
是一组模板类和函数，提供了容器、算法和迭代器等工具。

### 条款02: 尽量以const, enum, inline 替换 #define
* 常量替换#define 有两种用法:
a.常量指针通常这样定义 const char * const hello = "hello world";  两个const
b.class 定义常量， 通常 定义成static const, 如果想在声明时初始化static const 变量， 可以使用
constexpr， static constexpr float pi = 3.14;

### 条款03: 尽可能使用const
* const优势：
使用const明确告知编译器和程序员该值保持不变
const 修饰函数返回值 参数 和函数自身, 返回值时引用或者指针时使用const修饰返回值才有意义
const 修饰成员函数， 有几点优势和必要性
a.保护对象内容
b.一些重载operator[]的类，一般有两个版本，如
    const char& operator[](size_t ops) const // 供const对象调用
    char& operator[](size_t ops)    // 供non-const对象调用
    
* const 对象应该调用 const版本的operator[]函数 保护对象内容，这时候必须要有 const 版本的成员函数
这是因为const对象只能调用const成员函数

### 条款04: 确定对象在使用前已被初始化
* 尽量使用初始化列表，使用了初始化列表，非内置类型直接调用拷贝构造初始化，如果不使用就会调用默认构造+赋值函数，所以使用初始化列表可以提高效率
* const 引用成员必须使用初始化列表初始化
* 初始化列表初始化的顺序和声明的顺序一致

  ## 构造、析构和赋值运算

### 条款05：了解C++默默编写并调用了哪些函数
* 编译器会主动为你编写的任何类声明一个拷贝构造函数、拷贝复制操作符和一个析构函数,注意上边说的是声明，只有当这些函数有调用需求的时候，编译器才会帮你去实现它们，但有些情况可能需要你自己去实现这些函数
对于拷贝构造函数，需要考虑有没有深拷贝的需求，对于有const 引用成员变量，编译器不会帮你默认生成拷贝构造和赋值操作符，因为const 引用成员一旦初始化都是不能被改变的，需要程序员手动实现,对于析构函数，如果该类有多态需求，请主动将析构函数声明为virtual

### 条款06：若不想使用编译器自动生成的函数，就该明确拒绝
* 接上一条，如果你的类型在语义或功能上需要明确禁止某些函数的调用行为，比如禁止拷贝行为，那么你就应该禁止编译器去自动生成它，在C++11，我们可以直接使用= delete来声明拷贝构造函数，显示禁止编译器生成该函数

### 条款07：为多态基类声明virtual
* 如果有多态的需求，需要为多态基类声明virtual，这样才能保证父类子类的析构函数都被调用，如果该函数明确不想被重写，可以使用final关键字声明

### 条款08：别让异常逃离析构函数
* 析构函数一般情况下不应抛出异常，防止资源归还失败，所以尽量让一些容易出现异常的代码不要出现在析构函数中，使用单独的函数封装

### 条款09：绝不在构造和析构过程中调用virtual函数
* 请不要在构造函数和析构函数中调用virtual函数，在构造函数的调用链中也不能调用virtual函数,夫类构造函数调virtual函数，此时子类还没有构造完全，此时的virtual函数只能调用夫类的virtual函数，同样在夫类析构函数中
  调用virtual函数，此时子类对象已经不复存在，再去调用可能导致未定义行为
  
### 条款10：令operator =返回一个reference to *this
* 在设计接口时一个重要的原则是，让自己的接口和内置类型相同功能的接口尽可能相似,这样做可以让你的赋值操作符实现“连等”的效果

### 条款11：在operator=中处理“自我赋值”
* operator=防止自我赋值避免先把自己的资源给释放掉了，然后又把以释放掉的资源赋给了自己的出错行为。这里推荐使用copy and swap技术方案，这是一种异常安全的赋值技术
```c
friend void swap(MyString& first, MyString& second) noexcept {
		using std::swap;
		swap(first.data, second.data);
	}
 
// Assignment Operator using Copy and Swap
MyString& operator=(const MyString& other) {
    MyString temp(other); //RAII
    swap(*this, temp);  // Swap with a copy of the other object
    return *this;
}
```

### 条款12：复制对象时勿忘其每一个成分
* 当你给类多加了成员变量时，请不要忘记在拷贝构造函数和赋值操作符中对新加的成员变量进行处理。如果你忘记处理，编译器也不会报错



