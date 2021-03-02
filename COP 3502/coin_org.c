#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 21

void addCustomer();
void sortCustomers();

typedef struct customer {
  char * name;
  int tokens;
  int bills;
} customer;

int main() {
  int numCustomers, tokens, bills;

  /* number of paying customers */
  scanf("%d", &numCustomers);

  while (numCustomers) {
    addCustomer();
    numCustomers--;
    break;
  }

  /* conversion rate a tokens == b bills */
  scanf("%d %d", &tokens, &bills);

  // sortCustomers();

  return 0;
}


void addCustomer() {
  char handle[MAX_NAME_LEN];
  customer * person = calloc(1, sizeof(customer));
  scanf("%s %d %d", handle, &person->tokens, &person->bills);
  person->name = calloc(strlen(handle) + 1, sizeof(char));
  strcpy(person->name, handle);
  printf("%s %d %d\n", person->name, person->tokens, person->bills);
}

void sortCustomers() {

}
