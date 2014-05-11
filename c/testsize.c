/* ************************************************************************
  > File Name: testsize.c
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Wed May  7 14:35:28 2014
 *********************************************************************** */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *p = (char*) malloc(100);
    char ch[100] = {0};
    printf("%lu\n", sizeof(ch));
}
