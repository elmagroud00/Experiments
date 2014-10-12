/*************************************************************************
	> File Name: test64pointer.c
	> Author: 
	> Mail: 
	> Created Time: Tue 23 Sep 2014 01:35:46 PM CST
 ************************************************************************/

#include <stdio.h>

int main(int argc, char **argv) {

    char *a = "12345";
    printf("a: %ld: %p\n", sizeof(a), a);
    char *b = a;
    printf("b: %ld: %p\n", sizeof(b), b);
    char c = 'a';
    printf("c: %ld\n", sizeof(c));
    return 0;
}
