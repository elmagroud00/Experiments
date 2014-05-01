#include <stdio.h>
#include <stdlib.h>

#define CL_OPEN "open"
int main(void)
{
   printf("%s\n", CL_OPEN);
   printf("%s\n", CL_OPEN"xx");
   return(0);
}
