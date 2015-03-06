/*************************************************************************
	> File Name: testConst.c
	> Author: 
	> Mail: 
	> Created Time: Tue 27 Jan 2015 01:35:45 PM CST
 ************************************************************************/

#include <stdio.h>

int main() {

    const char* const a[] = {
        "abc",
        "def",
        "ghj",
    };

    a[0] = "ooo";

    printf("%s\n", a[0]);

    return 0;
}
