/* ************************************************************************
  > File Name: testConstCast.cpp
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Thu May 15 01:01:13 2014
 *********************************************************************** */
#include <iostream>

using namespace std;

int main() {
    char c[] = {'h', 'e', '\0'}; 
    cout << "c = " << c << endl;
    const char* a = c;
    cout << "a = " << a << endl;
    char* b = const_cast<char*>(a);
    b[0] = 'x';
    cout << "b = " << b << endl;

    

    return 0;
}
