#include <iostream>
using namespace std;

template<class T> class Singleton {
    Singleton(const Singleton&);
    Singleton &operator=(const Singleton&);
    protected:
    Singleton() {}
    virtual ~Singleton() {}
    public:
    static T &instance() {
        static T theInstance;
        return theInstance;
    }
};

class MyClass : public Singleton<MyClass> {
    int x;
    protected:
    friend class Singleton<MyClass>;
    MyClass() { cout << "MyClass::MyClass()" << endl ; x = 0; }
    ~MyClass() { cout << "MyClass::~MyClass" << endl; }
    public:
    void setValue(int n) { x = n; }
    int getValue() const { return x; }
};

int main() {
    MyClass &m = MyClass::instance();
    cout << m.getValue() << endl;
    m.setValue(1);
    cout << m.getValue() << endl;
}
