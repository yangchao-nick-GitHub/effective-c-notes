#include <iostream>
#include <vector>

using namespace std;

const char * const hello = "hello world";

class Test {
public:
    static constexpr float pi = 3.14;
};

class MyClass {
public:
    const int* getConstMemberAddr() {
        // return someValue;
        p = &someValue;
        return p;
    }

    const int getConstMember() const {
        cout << "const getConstMember" << endl;
        return someValue;
    }

    int getConstMember() {
        cout << "getConstMember" << endl;
        return someValue;
    }
    
    int getMember() {
        cout << "getMember" << endl;
        return someValue;
    }

private:
    int someValue = 10;
    int *p {nullptr};
};

int test(const MyClass& obj)
{
    return obj.getMember();
}


int main()
{
    cout << Test::pi << endl;
    cout << hello << endl;

    MyClass obj;
    test(obj);
    
    return 0;
}