/*************************************************************************
	> File Name: testString.c
	> Author: 
	> Mail: 
	> Created Time: Mon 22 Sep 2014 05:12:58 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>

void test(const char *str) {

    printf("strlen---%d\n:", strlen(str));
    printf("sizeof---%d\n:", sizeof(str));
    char local[128];
    memset(local, 0, sizeof(local));
    strncpy(local, str, sizeof(local));

    printf("result: %s\n", local);
    printf("sizeof: %d\n", sizeof(local) - 1);
    printf("strlen: %d\n", strlen(local));
}

int main(int argc, char** argv) {
    char* str = "abjhjcdefef";
    test(str);

    char test[3];
    test[0] = 'a';
    test[1] = 'b';
    test[2] = 0;
    return 0;
}
