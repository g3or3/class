#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 15

void guessNum(int);
void search(int, int, int, int, char [], _Bool, int);
void printVal(int);
int getInput(char [], int);


/* Take a number N from the user and start the guessing game */
int main() {
  int maxGuess;

  scanf("%d", &maxGuess);
  guessNum(maxGuess);

  return 0;
}


/* Prints the first two guess values which are always 1 and N
  then starts the binary search based on user input */
void guessNum(int max) {
  int start = 1, mid, end = max, guessVal, warmer;
  char *correct = "Yes!!!", *firstNo = "No.";
  char input[MAX_LEN];

  /* first guess 1 */
  printVal(start);
  scanf("%s", input);
  getchar();
  /* second guess N */
  if (strcmp(input, firstNo) ==  0) printVal(end);
  else if (strcmp(input, correct) == 0) exit(1);

  /* Arbitrary value for second argument because the first time
    getInput is called there is no relevant mid value */
  warmer = getInput(input, -1);

  /* check right side of N */
  if (warmer == 1) {
    start = max / 2 + 1;
    mid = start + (end - start) / 2;
    guessVal = mid - (max - mid);
    search(start, mid, end, guessVal, input, warmer, max);
  }

  /* check left side of N */
  if (warmer == 0) {
    end = max / 2;
    mid = start + (end - start) / 2;
    guessVal = mid - (max - mid);
    search(start, mid, end, guessVal, input, warmer, max);
  }
}


/* Search for the guess value recursively */
void search(int start, int mid, int end, int guessVal, char input[], _Bool warmer, int max) {
  /* if the target value is N / 2 */
  if (start == mid && end == max / 2) {
    printVal(end);
    getInput(input, end);
  }

  /* checks the guess value passed from previous search call */
  printVal(guessVal);
  warmer = getInput(input, mid);

  /* if guess value is "warmer" than the previous guess */
  if (warmer == 1) {
    /* end becomes mid with new mid and guess values */
    if (guessVal < mid) {
      end = mid;
      mid = start + (end - start) / 2;
      guessVal = mid + (mid - guessVal);
      search(start, mid, end, guessVal, input, warmer, max);
    }
    /* start becomes mid with new mid and guess values */
    if (guessVal > mid) {
      start = mid;
      mid = start + (end - start) / 2;
      guessVal = mid - (guessVal - mid);
      search(start, mid, end, (mid + (end - mid) / 2) * -2, input, warmer, max);
    }
  }

  /* if guess value is "colder" than the previous guess */
  if (warmer == 0) {
    /* start becomes mid with new mid and guess values */
    if (guessVal < mid) {
      start = mid;
      mid = start + (end - start) / 2;
      guessVal = mid + (mid - guessVal);
      search(start, mid, end, guessVal, input, warmer, max);
    }
    /* end becomes mid with new mid and guess values */
    if (guessVal > mid) {
      end = mid;
      mid = start + (end - start) / 2;
      guessVal = mid - (guessVal - mid);
      search(start, mid, end, guessVal, input, warmer, max);
    }
  }
}


/* Prints the guess value and clears the buffer */
void printVal(int num) {
  printf("%d\n", num);
  fflush(stdout);
}


/* Checks to see if the printed guess value is closer (warmer) or
  further (colder) from the target value but also checks
  if the guess is correct or if there is no change from
  the last guess value */
int getInput(char input[], int mid) {
  char *correct = "Yes!!!", *noWarmer = "No. Warmer.", *noColder = "No. Colder.", *noChange = "No. No change.";
  fgets(input, MAX_LEN, stdin);

  /* need to deal with the extra \n passed in fgets by trimming the string */
  if (strlen(input) == 7) input[6] = '\0';
  if (strlen(input) == 12) input[11] = '\0';
  if (strcmp(input, correct) == 0) exit(1);
  if (strcmp(input, noWarmer) == 0) return 1;
  if (strcmp(input, noColder) == 0) return 0;

  /* no change means mid is the target value */
  if (strcmp(input, noChange) == 0) {
    printVal(mid);
    scanf("%s", input);
    if (strcmp(input, correct) == 0) exit(1);
  }

  return -100;
}
