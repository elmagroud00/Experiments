/*************************************************************************
	> File Name: testCharCopy.c
	> Author: 
	> Mail: 
	> Created Time: Fri 26 Sep 2014 11:23:19 AM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>

int main() {
    char* a = "abcd";    
    char b[32] = {0};
    
    memcpy(b, a, sizeof(b) - 1); 
    printf("%s\n", b);

    return 0;
}
