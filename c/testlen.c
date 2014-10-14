/*************************************************************************
	> File Name: testlen.c
	> Author: 
	> Mail: 
	> Created Time: Sat 11 Oct 2014 01:47:52 PM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    char a[10] = {0};
    char b[20] = {'a'};

    if(0 == strlen(a)) {
        strncpy(a, "unknown", sizeof("unknown"));
    }

    printf("%s\n", a);


    return 0;
}
