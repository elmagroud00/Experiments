/*************************************************************************
	> File Name: testsizeof.c
	> Author: 
	> Mail: 
	> Created Time: Mon 29 Sep 2014 03:34:54 PM CST
 ************************************************************************/

#include <stdio.h>

struct A {
    int a;
    char b[10];
};

void func(struct A *a) {
    printf("func: %d\n", sizeof(struct A));
}

int main() {
    struct A a;
    func(&a);
    printf("sizeof(a): %d\n", sizeof(a));
    printf("sizeof(A): %d\n", sizeof(struct A));

    return 0;
}
