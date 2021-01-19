#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CAP 10

typedef struct list{
  int * values;
  int size;
  int capacity;
} list;

void initializeList(list *);
void addToList(list *, int);
void doubleList(list *);
void deleteList(list);

int main() {
  int input;
  list *myList;

  initializeList(myList);

  scanf("%d", &input);
  while (input != -1) {
    addToList(myList, input);
    scanf("%d", &input);
  }

  for (int i = 0; i < myList->size; i++) {
    printf("%d\n", myList->values[i]);
  }

  //deleteList(*myList);
  //atexit(report_mem_leak);
  return 0;
}

void initializeList(list *arrList) {
  arrList->values = calloc(DEFAULT_CAP, sizeof(int));
  arrList->capacity = DEFAULT_CAP;
  arrList->size = 0;
}

void addToList(list *arrList, int n) {
  if (arrList->size == arrList->capacity) doubleList(arrList);
  arrList->values[arrList->size] = n;
  arrList->size++;
}

void doubleList(list *arrList) {
  printf("%s", "List expanding...");
  int newCap = arrList->capacity * 2;
  arrList->values = realloc(arrList->values, newCap * sizeof(int));
  if (arrList->values == NULL) exit(0);
  arrList->capacity = newCap;
  printf("%s %d\n", " new capacity", newCap);
}

void deleteList(list arrList) {
  free(arrList.values);
}
