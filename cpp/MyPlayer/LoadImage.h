/*
 * LoadImage.h
 *
 *  Created on: Dec 26, 2012
 *      Author: sijiewang
 */

#ifndef LOADIMAGE_H_
#define LOADIMAGE_H_

bool loadPngImage(const char *name, int *outWidth, int *outHeight, bool *outHasAlpha, GLubyte **outData);


#endif /* LOADIMAGE_H_ */
