
// Program to add structures (students to an array list)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Typedefs for the structs
typedef struct student student;
typedef struct AL AL;

// Our student structure which contains a name and grade
struct student {
    char * name;
    int grade;
};

// A basic Array List structure
struct AL {
    student ** arr;
    int size, cap;
};

// The default capacity of the array list (small to prove concept)
#define DEFAULT_CAP 1

// Function prototypes
student * newStudent(char *, int);
void      destroyStudent(student *);
AL *      newAL();
void      destroyAL(AL *);
void      addToAL(AL *, student *);
void      expandAL(AL *);


// The main function
int main()
{
    // Create the array list
    AL * list = newAL();

    // Create a string for making the students
    char str[100 + 1];

    // Add Alice to the array list
    strcpy(str, "Alice");
    addToAL(list, newStudent(str, 95));

    // Add Bob to the array list
    strcpy(str, "Bob");
    addToAL(list, newStudent(str, 94));

    // Add Carol to the array list
    strcpy(str, "Carol");
    addToAL(list, newStudent(str, 93));

    // Add David to the array list
    strcpy(str, "David");
    addToAL(list, newStudent(str, 96));

    // Add Eric to the array list
    strcpy(str, "Eric");
    addToAL(list, newStudent(str, 100));

    // Print all the students
    for (int i = 0; i < list->size; i++)
    {
        printf("%s %d\n", list->arr[i]->name, list->arr[i]->grade);
    }

    // Clean up our dynamic memory
    destroyAL(list);
    return 0;
}

// Function to create a new student
// Input: name and grade
//        name is not guarenteed to remain the same
// Output: Pointer to a student memory section with the
//         appropriate values
student * newStudent(char * name, int grade)
{
    // Create the student segment of memory
    student * ret = calloc(1, sizeof(student));

    // Set up the grade
    ret->grade = grade;

    // Create the name by allocating and copying it
    ret->name = calloc(1 + strlen(name), sizeof(char));
    strcpy(ret->name, name); // ret->name = name;
//    ret->name = name; // this does not work

    // Return the created student
    return ret;
}

// Function to clean up the memory created for the student
// Input: pointer to the student allocation
void      destroyStudent(student * person)
{
    // Free their name
    free(person->name);

    // Free their pointer
    free(person);
}

// Function to create a new array list
// Output: pointer to an allocation for the array list
AL *      newAL()
{
    // Create the overall place for the array list
    AL * ret = calloc(1, sizeof(AL));

    // Create the array of student pointers
    ret->arr = calloc(DEFAULT_CAP, sizeof(student *));

    // Set up the default capacity
    ret->cap = DEFAULT_CAP;

    // Set the size to 0, b/c no student are contained
    ret->size = 0;
    return ret;
}

// Function to destroy the array list
// Input: the pointer to the section of memory containing the
//        array list
void      destroyAL(AL * list) {
    // Loop through and destroy each student
    for (int i = 0; i < list->size; i++)
        destroyStudent(list->arr[i]);

    // Free the array of student pointers
    free(list->arr);

    // Free the actual array list
    free(list);
}

// Function to add a student (already created) to the array list
// Input: the pointer to the array list AND
//        already allocated and initialized person
void      addToAL(AL * list, student * person)
{
    // If the array list is full expand the array list
    if (list->cap == list->size) expandAL(list);

    // Add the person to the end of the array
    list->arr[list->size] = person;

    // Update the number of students in the array list
    list->size++;
}

// Function to expand the array list
// Input: the pointer to the array list to be expanded
void      expandAL(AL * list)
{
    // Make a new capacity equal to double the old capacity
    // The doubling makes it so that the array list will not need
    // to expand EVERY insertion
    int newCap = list->cap * 2;

    // Move the pointers of students into a new array of pointers
    list->arr = realloc(list->arr, newCap * sizeof(student *));
    // TODO CHECK FOR NULL HERE!!!

    // Update the capacity
    list->cap = newCap;
}
