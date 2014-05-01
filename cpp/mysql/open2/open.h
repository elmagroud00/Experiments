#ifndef _OPEN_H_
#define _OPEN_H_

#include <apue.h>
#include <errno.h>

#define CL_OPEN "open"
#define CS_OPEN "/tmp/opend"

int csopen(char*, int);

#endif
