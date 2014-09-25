/*************************************************************************
	> File Name: testbuf.c
	> Author: 
	> Mail: 
	> Created Time: Tue 23 Sep 2014 07:21:41 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>

void fun(char *ch) {
    memset(ch, 'a', 10);
}

int main() {
    char a[10];
    fun(a);
    printf("%s\n", a);
    return 0;
}
