#include <iostream>

using namespace std;

int main(int argc, char *argv)
{
    const int i = 2;
    cout << "i = " << i << endl;
    cout << "address of i : " << &i << endl;
    int *intp = (int*)&i;
    *intp = 3;
    cout << "intp point to : " << intp << endl;
    cout << "*inpt = " << *intp << endl;
    cout << "i = " << i << endl;
    return 0;
}
