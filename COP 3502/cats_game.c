#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 12

void guessNum(int num);
void search(int [], int, int, int, int, char [], _Bool);
void printVal(int val);
_Bool getInput(char []);

int main() {
  int maxGuess;

  scanf("%d", &maxGuess);
  guessNum(maxGuess);

  return 0;
}

void guessNum(int max) {
  int size = max * 3 + 1;
  int arr[size], start = 1, mid, end = max, guessVal;
  char *correct = "Yes!!!", *firstNo = "No.", *noWarmer = "No. Warmer.", *noColder = "No. Colder.";
  char input[MAX_LEN];

  // get the array set up from -N to 2N
  for (int i = 0, j = max * -1; i <= size; i++, j++) {
    arr[i] = j;
  }

  // first guess 1
  printf("%d\n", start);
  fflush(stdout);
  scanf("%s", input);
  if (strcmp(input, firstNo) ==  0) {
    // second guess N
    printVal(end);
  }
  _Bool warmer = getInput(input);
  if (warmer == 1) {
    // check right
    start = max / 2 + 1;
    mid = start + (end - start) / 2;
    guessVal = mid * 2 - 1;
    search(arr, start, mid, end, guessVal, input, warmer);
  }
  if (warmer == 0) {
    // check left
    end = max / 2;
    mid = start + (end - start) / 2;
    guessVal = 1 - mid * 2;
    search(arr, start, mid, end, guessVal, input, warmer);
  }
}




void search(int arr[], int start, int mid, int end, int guessVal, char input[], _Bool warmer) {
  printVal(guessVal);
  warmer = getInput(input);

  // base case
  if (start >= end) return;

  // recursive step
  if (warmer == 1) {
    if (guessVal < mid) {
      end = mid;
      mid = start + (end - start) / 2;
      guessVal = mid * 2 + abs(guessVal);
      search(arr, start, mid, end, guessVal, input, warmer);
    }
    if (guessVal > mid) {
      start = mid;
      mid = start + (end - start) / 2;
      guessVal = mid * 2 - abs(guessVal);
      search(arr, start, mid, end, guessVal, input, warmer);
    }
  }
  if (warmer == 0) {
    if (guessVal > mid) {
      end = mid;
      mid =  start + (end - start) / 2;
      guessVal = mid * 2 - guessVal;
      search(arr, start, mid, end, guessVal, input, warmer);
    }
    if (guessVal < mid) {
      start = mid;
      mid = start + (end - start) / 2;
      guessVal = abs(guessVal) + mid * 2;
      search(arr, start, mid, end, guessVal, input, warmer);
    }
  }
}



void printVal(int guessVal) {
  printf("%d\n", guessVal);
  fflush(stdout);
  fflush(stdin);
}




_Bool getInput(char input[]) {
  char *correct = "Yes!!!", *noWarmer = "No. Warmer.", *noColder = "No. Colder.", *noChange = "No. No change.";
  fgets(input, MAX_LEN, stdin);
  if (strlen(input) == 7) input[6] = '\0';
  if (strcmp(input, correct) == 0) exit(1);
  if (strcmp(input, noWarmer) == 0) return 1;
  if (strcmp(input, noColder) == 0) return 0;
  return -1;
}
