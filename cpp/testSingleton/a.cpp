#include <iostream>

using namespace std;

class Singleton {
    private:
        Singleton() { cout << "Singleton::constructor" << endl; }
        ~Singleton() { cout << "Singleton::destructor" << endl; }

    public:
        static Singleton* getInstance() {
            if(m_aInstance == NULL) {
                m_aInstance = new Singleton();
            }
            return m_aInstance;
        }
        void show() {
            cout << "Singleton::show" << endl;
        }

    private:
        class Garbage{
            public:
                ~Garbage() {
                    if(m_aInstance != NULL) {
                        delete m_aInstance;
                    }
                }
        };
    
    private:
        static Singleton* m_aInstance;
        static Garbage m_garbage;
};

Singleton* Singleton::m_aInstance = NULL;
Singleton::Garbage Singleton::m_garbage;

int main(int argc, char **argv) {
    Singleton* aSingleton = Singleton::getInstance();
    aSingleton->show(); 
    return 0;
}
