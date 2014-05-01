#include "open.h"
#include <fcntl.h>

#define BUFFSIZE 8192

int main(int argc, char *argv[])
{
    int n, fd;
    char buf[BUFSIZ], line[MAXLINE];

    /*read filename to cat from stdin*/
    while(fgets(line, MAXLINE, stdin) != NULL){
        printf("line = %s\n", line);
        if(line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = 0;
        printf("line = %s\n", line);
        /*open the file*/
        if((fd = csopen(line, O_RDONLY)) < 0)
            continue; /*csopen() prints error from server*/
        printf("csopen = %d\n", fd);
        /*add cat to stdout*/
        while((n = read(fd, buf, BUFFSIZE)) > 0)
            if(write(STDOUT_FILENO, buf, n) != n)
                err_sys("write error");
        if(n < 0)
            err_sys("read error");
        close(fd);
    }
    printf("good bye");
    exit(0);
}
