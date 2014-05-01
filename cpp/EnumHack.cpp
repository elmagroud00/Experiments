#include <iostream>

using namespace std;

class Bunch{
    enum { size = 100 };
    int i[size];
};

int main(){
    cout << "sizeof(Bunch) = " << sizeof(Bunch)
         << ", sizeof(i[100]) = " << sizeof(int[100]) << endl; 
}///:~
