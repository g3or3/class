#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 21

typedef struct customer {
  char * name;
  int tokens;
  int bills;
  long long int units;
} customer;

typedef struct customerList {
  int size, capacity;
  customer ** customers;
} customerList;


customerList * createCustList();
customer * createCustomer();
void addCustomer(customerList *, customer *);
void convertToUnits(customerList *, int, int);
void sortCustomers();
void clearMemory();


int main() {
  int numCustomers, tokens, bills;

  customerList * custList = createCustList();

  /* number of paying customers */
  scanf("%d", &numCustomers);

  while (numCustomers) {
    customer * person = createCustomer();
    addCustomer(custList, person);
    numCustomers--;
  }

  /* conversion rate a tokens == b bills */
  scanf("%d %d", &tokens, &bills);
  convertToUnits(custList, tokens, bills);
  // sortCustomers();
  for (int i = 0; i < custList->size; i++) {
    printf("%lld\n", custList->customers[i]->units);
  }
  return 0;
}

customerList * createCustList() {
  customerList * custList = calloc(1, sizeof(customerList));
  custList->customers = calloc(1, sizeof(customer*));
  custList->size = 0;
  custList->capacity = 1;
  return custList;
}

customer * createCustomer() {
  char handle[MAX_NAME_LEN];
  customer * person = calloc(1, sizeof(customer));
  scanf("%s %d %d", handle, &person->tokens, &person->bills);
  person->name = calloc(strlen(handle) + 1, sizeof(char));
  strcpy(person->name, handle);
  return person;
}

void addCustomer(customerList * custList, customer * person) {
  if (custList->size == custList->capacity) {
    int newCap = custList->capacity * 2;
    custList->customers = realloc(custList->customers, newCap * sizeof(customer *));
    custList->capacity = newCap;
  }
  custList->customers[custList->size] = person;
  custList->size++;
}

void convertToUnits(customerList * custList, int tokens, int bills) {
  long long int tokenToUnits, billtoUnits;
  for (int i = 0; i < custList->size; i++) {
    tokenToUnits = custList->customers[i]->tokens * bills;
    billtoUnits = custList->customers[i]->bills * tokens;
    custList->customers[i]->units = tokenToUnits + billtoUnits;
  }
}

void sortCustomers() {

}
