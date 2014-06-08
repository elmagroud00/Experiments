/*
 * util.h
 *
 *  Created on: Jan 30, 2013
 *      Author: sijiewang
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <sys/time.h>
#include <iostream>

typedef long long TIME;

TIME Dayus();

TIME Dayus(const timeval *t);

TIME Dayus(int h24, int min, int sec, int us);

#endif /* UTIL_H_ */
