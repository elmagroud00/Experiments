#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdio.h>
using namespace std;

int main() {
    int nUnits,  nSize;
    glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &nUnits);
    glGetIntegerv(GL_MAX_RECTANGLE_TEXTURE_SIZE_NV, &nSize);
    fprintf(stderr, "nUnits = %d\n", nUnits);
    fprintf(stderr, "nSize = %d\n", nSize);
    return 0;
}
