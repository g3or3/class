#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 21

typedef struct customer {
  char *name;
  int tokens;
  int bills;
  long long int units;
} customer;

typedef struct customerList {
  int size, capacity;
  customer **customers;
} customerList;


customerList * createCustomerList();
customer * createCustomer();
void addCustomer(customerList *, customer *);
void convertToUnits(customerList *, int, int);
void sortCustomers(customer **, int);
void freeMemory(customerList *);


int main() {
  int numCustomers, tokens, bills;

  customer *newCustomer;

  customerList *custList = createCustomerList();

  /* number of paying customers */
  scanf("%d", &numCustomers);

  while (numCustomers) {
    newCustomer = createCustomer();
    addCustomer(custList, newCustomer);
    numCustomers--;
  }

  /* conversion rate a tokens == b bills */
  scanf("%d %d", &tokens, &bills);
  convertToUnits(custList, tokens, bills);

  /* quicksort */
  sortCustomers(custList->customers, custList->size);

  /* print the sorted customer array */
  for (int i = 0; i < custList->size; i++) {
    printf("%s\n", custList->customers[i]->name);
  }

  freeMemory(custList);

  return 0;
}

/* Set up an array of customer structs to store every paying customer */
customerList * createCustomerList() {
  customerList *custList = calloc(1, sizeof(customerList));
  custList->customers = calloc(1, sizeof(customer*));
  custList->size = 0;
  custList->capacity = 1;
  return custList;
}

/* Create a customer struct to store the name, tokens, bills and converted units */
customer * createCustomer() {
  char handle[MAX_NAME_LEN];
  customer *newCustomer = calloc(1, sizeof(customer));

  scanf("%s %d %d", handle, &newCustomer->tokens, &newCustomer->bills);
  newCustomer->name = calloc(strlen(handle) + 1, sizeof(char));
  strcpy(newCustomer->name, handle);
  return newCustomer;
}

/* Add the customer to the array of customers */
void addCustomer(customerList *custList, customer *newCustomer) {
  if (custList->size == custList->capacity) {
    int newCap = custList->capacity * 2;
    custList->customers = realloc(custList->customers, newCap * sizeof(customer *));
    custList->capacity = newCap;
  }
  custList->customers[custList->size] = newCustomer;
  custList->size++;
}

/* Use the conversion rate to assign a 'units' value to every customer */
void convertToUnits(customerList *custList, int tokens, int bills) {
  long long int tokenToUnits, billtoUnits;

  for (int i = 0; i < custList->size; i++) {
    tokenToUnits = custList->customers[i]->tokens * bills;
    billtoUnits = custList->customers[i]->bills * tokens;
    custList->customers[i]->units = tokenToUnits + billtoUnits;
  }
}

/* Sort the list of customers from greatest to least in terms of paid value */
void sortCustomers(customer **customers, int len) {
  if (len <= 1) {
    return;
  }
  customer *pivot = customers[0];
  int frontSize = 0;
  int backSize = 0;
  for (int i = 1; i < len; i++) {
    if (customers[frontSize + 1]->units > pivot->units) {
      frontSize++;
    } else {
      backSize++;
      customer *temp = customers[frontSize + 1];
      customers[frontSize + 1] = customers[len - backSize];
      customers[len - backSize] = temp;
    }
  }
  customers[0] = customers[frontSize];
  customers[frontSize] = pivot;
  sortCustomers(customers, frontSize);
  sortCustomers(customers + frontSize + 1, backSize);
}

/* Frees any memory used */
void freeMemory(customerList *custList) {
  for (int i = 0; i < custList->size; i++) {
    free(custList->customers[i]->name);
    free(custList->customers[i]);
  }
  free(custList->customers);
  free(custList);
}
