#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 241
#define IS_PRETTY 1
#define INDEX 0

int   splitString(char **, char *, char *);
void  permuteStrings(char **, int, int, int);
void  swapStrings(char **, int, int);
_Bool prettyPhrase(char **, int, int, _Bool);
void  joinStrings(char **, int, char *, char *, int);
void  freeStringArr(char **, int);

char * space = " ";
char inputStr[MAX_INPUT_LEN];
char answerString[MAX_INPUT_LEN];

int main() {
  int n;
  scanf("%d ", &n);
  char * arrofStrings[n];
  scanf("%[^\n]%*c", inputStr);
  int wordCount = splitString(arrofStrings, inputStr, space);
  permuteStrings(arrofStrings, INDEX, wordCount - 1, wordCount);
  return 0;
}

/* Splits the input string into individual handles for analysis */
int splitString(char ** emptyStrArr, char inputStr[], char * space) {
  int wordCount = 0, i = 0;
  char * token = strtok(inputStr, space);
  while (token != NULL) {
    emptyStrArr[i] = malloc(strlen(token) + 1);
    strcpy(emptyStrArr[i], token);
    token = strtok(NULL, space);
    i++; wordCount++;
  }
  return wordCount;
}

/* Find all the permutations of the handles */
void permuteStrings(char ** arrofStrings, int start, int end, int wordCount) {
  if (prettyPhrase(arrofStrings, INDEX, wordCount, IS_PRETTY) == 1) {
    joinStrings(arrofStrings, INDEX, answerString, space, wordCount);
    printf("%s\n", answerString);
    freeStringArr(arrofStrings, wordCount); exit(0);
  }
  else {
    for (int i = start; i <= end; i++) {
      swapStrings(arrofStrings, start, i);
      permuteStrings(arrofStrings, start + 1, end, wordCount);
      swapStrings(arrofStrings, start, i);
    }
  }
}

/* Swaps two handles in the handles array */
void swapStrings(char ** arrofStrings, int x, int y) {
  char * temp = arrofStrings[x];
  arrofStrings[x] = arrofStrings[y];
  arrofStrings[y] = temp;
}

/* Checks to see if the arrangement of handles is "pretty" */
_Bool prettyPhrase(char ** arrofStrings, int pos, int wordCount, _Bool isPretty) {
  if (isPretty == 0) return isPretty;
  if (pos == wordCount - 1) return isPretty;
  int length = strlen(arrofStrings[pos]) - 1;
  if (!(arrofStrings[pos][length] == arrofStrings[pos + 1][INDEX])) {
    isPretty = 0; return isPretty;
  }
  isPretty = prettyPhrase(arrofStrings, pos + 1, wordCount, isPretty);
  return isPretty;
}

/* Concatenates the organized handles that form a "pretty" phrase */
void joinStrings(char ** arrofStrings, int pos, char * answerString, char * space, int wordCount) {
  if (pos == wordCount) return;
  strcat(answerString, arrofStrings[pos]);
  strcat(answerString, space);
  joinStrings(arrofStrings, pos + 1, answerString, space, wordCount);
}

/* Frees the array that contains the handles */
void freeStringArr(char ** arrofStrings, int wordCount) {
  for (int i = 0; i < wordCount; i++)
    free(arrofStrings[i]);
}
