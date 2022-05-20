#include <stdio.h>

#include "get_string.h"

// print a line from stream using fgetc (only)
// reads  in at  most one less than size characters from stream and stores them into the
// buffer pointed to by s.  Reading stops after an EOF or a newline.  If a newline is read, it  is
// stored  into  the buffer.  A terminating null byte ('\0') is stored after the last character in the buffer.
void get_string(char *s, int size, FILE *stream) {

    // PUT YOUR CODE HERE
    int c;
    int n = 0;
    int count = 0;
    if (stream == NULL) {
        perror("Error opening file");
    } 
    c = fgetc(stream);  
    while (c != EOF && c != '\n') {
        if (n < size - 1) {
            s[n] = c;
            count++;
        }
        c = fgetc(stream);
        n++;
    }
    if (c == '\n' && n < size) {
        s[count] = '\n';
        count++;
    }
    s[count] = '\0';
    return;
}
