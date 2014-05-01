#include <cstdio>
#include <iostream>

using namespace std;

int main(int argc, char *argv)
{
    for(int i = 0; i < 10; i++)
        cout << i << endl;

    while((char c = cin.get()) != 'q')
    {
        cout << "not equ q" << endl;
    }
    return 0;
}
