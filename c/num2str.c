/* ************************************************************************
  > File Name: num2str.c
  > Author: lnmcc
  > Mail: lnmcc@hotmail.com 
  > Blog: lnmcc.net 
  > Created Time: Sun May 11 15:37:48 2014
 *********************************************************************** */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void int2str(int num, char* str) {
    sprintf(str, "%d", num);
}

int main(int argc, char **argv) {
    char* str = (char*)malloc(100);
    
    printf("sizeof = %ld\n", sizeof(str));
    printf("strlen = %ld\n", strlen(str));

    memset(str, 0x0, 100);
    int2str(atoi(argv[1]), str);

    printf("str = %s\n", str);

    free(str);
}
