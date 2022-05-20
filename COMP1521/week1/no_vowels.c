#include <stdio.h>

int main () {
    char character;
   //int check;
    //scanf("%c", &character);
    while (scanf("%c", &character) != EOF) {   //scan the char while checking 
    //for EOF 
        if (character != 'a' && character != 'e' && character != 'i' && 
        character != 'o' && character != 'u' && character != 'A' && 
        character != 'E' && character != 'I' && character != 'O' && 
        character != 'U') {
            // if it not vowel, print it 
            printf("%c", character);            
        }                 
    }
    
    return 0;
} 