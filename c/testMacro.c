#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define INFO(x...) log_out(6, "<6>init: ", x)

void log_out(int level, ...) {
    va_list argptr;
    va_start(argptr, level);

    while(1) {
        char *ret = va_arg(argptr, char*); 
        if(strcmp(ret, "end")) {
            printf("%s ", ret);
        } else {
            break;
        }
    }
    va_end(argptr);
    printf("\n");
}

int main() {
    INFO("hello world", "lnmcc", "end");
}
