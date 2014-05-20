/*
 * util.cpp
 *
 *  Created on: Jan 30, 2013
 *      Author: sijiewang
 */

#include "util.h"

TIME Dayus() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return Dayus(&t);
}

TIME Dayus(const timeval *t) {
	struct tm *ti = localtime(&t->tv_sec);
	return Dayus(ti->tm_hour, ti->tm_min, ti->tm_sec, t->tv_usec);
}

TIME Dayus(int h24, int min, int sec, int us) {
	TIME re = (long long)h24 * 3600000000LL;
	re += (long long)min * 60000000LL;
	re += (long long)sec * 1000000LL;
	re += (long long)us;
	return re;
}
