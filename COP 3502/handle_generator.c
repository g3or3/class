#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LENGTH 100001

void handleGenerator();
void modName(char []);

int main() {
  handleGenerator();
  return 0;
}

/* records what n will be and creates an array of chars to store the names
   while user inputs into console n times */
void handleGenerator() {
  int total;
  char names[MAX_LENGTH]; // max chars in name 100,000 + \0
  scanf("%d ", &total);
  if (total > 100000) exit(0); // if n exceeds spec limit
  while (total) {
    modName(names);
    total--;
  }
}

/* takes user input and prints out the user handle */
void modName(char str[]) {
  int length;
  fgets(str, MAX_LENGTH, stdin);
  length = strlen(str) - 1;
  for (int i = 0; i < length; i++) {
    if (i == 0) {                      // will always print the first char unless
      if (isspace(str[i]) == 0) {      // it's a space
        printf("%c", str[i]);
        if (length == 1) printf("\n"); // if there is only one char inputted
        continue;                      // will add new line and end loop
      }
    }
    if (isspace(str[i]) != 0 && isspace(str[i + 1]) == 0) {
      if (isspace(str[i + 2]) != 0) {
        printf("%c", str[i + 1]); i++;      // this is for when there is a single
        if (i == length - 1) printf("\n");  // letter in between two spaces so it
        continue;                           // will just print the letter once
      }
      printf("%c", str[i + 1]);
    }
    if (isspace(str[i]) == 0 && isspace(str[i + 1]) != 0) {
      printf("%c", str[i]);
    }
    if (i == length - 1) printf("\n");
  }
}
