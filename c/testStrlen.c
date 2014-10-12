/* ************************************************************************
  > File Name: testStrlen.c
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Mon Sep 22 23:55:13 2014
 *********************************************************************** */
#include <stdio.h>
#include <string.h>

void func(char *str) {
    printf("%s\n", str);
    printf("%ld\n", strlen(str));
}

int main(void) {
    char *s = "1234567";
    char ss[10];
    ss[0] = 'a';
    ss[1] = 'b';
    func(ss);
    return 0;
}
