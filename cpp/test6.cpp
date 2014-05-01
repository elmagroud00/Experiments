#include <iostream>
using namespace std;


int main() {
   char str[11] = "0234698";
   char *p = str;
     
   //cout << "*p++ = " << *p++ << endl;
   //cout << *p << endl;
   cout << "++*p = " << ++*p << endl;
//   cout << *p << endl;

   return 0;
}
