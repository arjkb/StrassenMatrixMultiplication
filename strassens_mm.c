/* Program to implement strassen's matrix multiplication
  Arjun Krishna Babu
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int str_to_int(const char *numstring);

int main()  {
  printf(" Hello, world!\n");
  
  return 0;
}


int str_to_int(const char *numstring) {
  int number = 0;
  int i;
  int digit = 0;

  for(i = 0; numstring[i] != '\0'; i++) {
    if( isdigit(numstring[i]) ) {
      digit = numstring[i] - '0';
      number = (number * 10) + digit;
      // printf(" DEBUG: Number: %d, %d %d\n", i, number, digit);
    }
    else  {
      printf(" Error: str_to_int(%s): not a digit\n", numstring);
      return 0;
    }
  }
  return number;
}
