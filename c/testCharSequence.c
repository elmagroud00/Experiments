/*************************************************************************
	> File Name: testCharSequence.c
	> Author: 
	> Mail: 
	> Created Time: Thu 25 Sep 2014 10:19:08 AM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>

#define HELLO "hello"

void func(char** str) {
    *str = HELLO; 
}

int main() { 
    char *str = NULL;
    func(&str);
    printf("%s\n", str);

    return 0;
}

