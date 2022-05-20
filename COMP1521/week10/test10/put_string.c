#include <stdio.h>

#include "put_string.h"

// print s to stdout with a new line appended using fputc (only)

void put_string(char *s) {

   // PUT YOUR CODE HERE
   int x = 0;
   int c = 0;
   while (s[x] != '\0') {
      c = s[x];
      fputc(c, stdout);
      x++;
   }
   c = 10;
   fputc(c, stdout);
   return;
}
