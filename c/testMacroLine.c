/*************************************************************************
	> File Name: testMacroLine.c
	> Author: 
	> Mail: 
	> Created Time: Tue 23 Sep 2014 02:27:09 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define LOG("%s:%d", __FUNCTION__, __LINE__) \
        printf()

int main() {
    int a = 10;
    LOG();
    return 0;
}

