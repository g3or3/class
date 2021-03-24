#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50

typedef struct Node Node;
typedef struct Stack Stack;

struct Node {
  char *name;
  long long int tokens;
  Node * next;
};

struct Stack {
  Node *head;
};


Node * getCustInfo(char *line);
Node * createCustomer(char *name, long long int tokens);
void findMVP(Stack *stack);

Stack * createCustStack();
void addCustomer(Stack *stack, Node *customer);
void removeCustomer(Stack *stack);
void destroyStack(Stack *stack);

int main() {
  char line[MAX_LEN];
  Stack *custStack = createCustStack();

  scanf("%[^\n]%*c", line);

  while (line[0] != '0') {
    if (line[0] == '1') {
      Node *newCust = getCustInfo(line);
      addCustomer(custStack, newCust);
    }
    if (line[0] == '2') {
      removeCustomer(custStack);
    }
    if (line[0] == '3') {
      findMVP(custStack);
    }
    scanf("%[^\n]%*c", line);
  }

  destroyStack(custStack);

  return 0;
}

/* Split up the line to be able to store the integer representing the
  number of tokens and the string representing the name of the customer */
Node * getCustInfo(char *line) {
  char tokenStr[MAX_LEN] = "";
  char name[MAX_LEN];
  long long int tokens;

  // starting at pos 2 in the line because that's where token values start
  // using numDigits to keep track of # of digits in the token int
  int numDigits = 0, pos = 2;

  while (isalpha(line[pos]) == 0) {
    numDigits++;
    pos++;
  }

  // numDigits is how many digits to copy minus 1 for whitespace char
  // pos is the index where the name of the customer starts
  strncpy(tokenStr, line + 2, numDigits - 1);
  tokens = atoi(tokenStr);
  strncpy(name, line + pos, MAX_LEN);

  Node *newCust = createCustomer(name, tokens);

  return newCust;
}

/* Create a new customer node with the number of tokens and the name */
Node * createCustomer(char *name, long long int tokens) {
  Node *newCust = calloc(1, sizeof(Node));
  newCust->name = calloc(strlen(name) + 1, sizeof(char));

  strcpy(newCust->name, name);
  newCust->tokens = tokens;
  newCust->next = NULL;

  return newCust;
}

/* Create a stack to store all the customer nodes */
Stack * createCustStack() {
  Stack *newStack = calloc(1, sizeof(Stack));
  newStack->head = NULL;

  return newStack;
}

/* Push the new customer to the customer stack */
void addCustomer(Stack *stack, Node *customer) {
  customer->next = stack->head;
  stack->head = customer;
}

/* Pop the last customer that was added */
void removeCustomer(Stack *stack) {
  if (stack->head == NULL) return;

  Node * temp = stack->head->next;

  free(stack->head->name);
  free(stack->head);
  stack->head = temp;
}

/* Finds the MVP customer based on highest tokens balance */
void findMVP(Stack *stack) {
  if (stack->head == NULL) return;

  Node *current = stack->head;
  Node *mvp = NULL;

  while (current != NULL) {
    if (mvp == NULL || mvp->tokens < current->tokens) mvp = current;
    current = current->next;
  }

  printf("%s\n", mvp->name);
}

/* Free any memory being used */
void destroyStack(Stack *stack) {
  while (stack->head != NULL) removeCustomer(stack);
  free(stack);
}
