#include <stdio.h>


// recursive sum of odd numbers in array
int oddSum (int * arr, int size) {
  int sum = 0;
  if (size == 0) return sum;
  if (arr[size - 1] % 2 != 0) sum = arr[size - 1];
  return sum + oddSum(arr, size - 1);
}


int arr[] = {1, 2, 4, 6, 7, 8, 10};
int size = 7;


int main() {
  printf("%d\n", oddSum(arr, size));
}


// insertion sort passes
/*
()7 9 3 8 5 11 1

(7) 9 3 8 5 11 1

(7 9) 3 8 5 11 1

(3 7 9) 8 5 11 1

(3 7 8 9) 5 11 1

(3 5 7 8 9) 11 1

(3 5 7 8 9 11) 1

(1 3 5 7 8 9 11)
*/

// merge sort big Oh O(nlog(n)) T(n) = 2T(n/2) + n

/*
  worst case big Oh runtime for following operations:

  add an item to the front of an array list: O(n)
  using quicksort on an array of numbers: O(n^2)
  using a binary search to find a certain number in an array: O(log(n))
*/

// best case runtime for selection sort O(n^2) *find the smallest number in the array every pass*

// arraylist is resizable so we can use dynamic memory and that means we can change the size after runtime
