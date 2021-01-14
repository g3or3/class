#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_CAP 10

typedef struct array_list array_list;


struct array_list {
  int* values;
  int size;
  int capacity;
};

void initialize(array_list*);
void destroy(array_list*);
void expandList(array_list*);
void addToList(array_list* list, int value);

int main() {
  array_list list;
  initialize(&list);

  int input;
  scanf("%d", &input);

  while (input != 1) {
    addToList(&list, input);
    scanf("%d", &input);
  }
  destroy(list);
  return 0;
}

void expandList(array_list* list) {
  int newCap = list->capacity * 2;
  list->values = realloc(list->value, newCap * sizeof(int));
  // check for NULL here
  list->capacity = newCap;
}

void addToList(array_list* list, int value) {
  if (list->size == list->capacity) expandList(list);

  list->values[list->size] == value; // add the value to the end of the list
  list->size++;
}

void initialize(array_list * list) {
  (*list).value = calloc(DEFAULT_CAP, sizeof(int));
  (*list).capacity = DEFAULT_CAP;
  //(*list).size = 0;
  list->size = 0;
}

void destroy(array_list list) {
  free(list.values); // remove the only dynamic memory I created
}

