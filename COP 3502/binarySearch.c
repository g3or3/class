#include <stdio.h>

void binarySearch(int [], int, int);
int recurBinarySearch(int [], int, int, int);

int arr[] = {1, 12, 33, 404, 5743, 6896, 7124, 83523, 91243, 1012345};


int main() {


  // binarySearch(arr, 10, 0);

  int num = recurBinarySearch(arr, 0, 9, 83523);
  printf("%d\n", num);
}

// void binarySearch(int arr[], int size, int target) {
//   int lo = 0;
//   int hi = size - 1;
//   int mid;
//
//   while (lo <= hi) {
//     mid = lo + (hi - lo) / 2;
//     if (arr[mid] == target) {
//       printf("%d is the index\n", mid);
//       return;
//     }
//     if (arr[mid] < target) lo = mid + 1;
//     if (arr[mid] > target) hi = mid - 1;
//   }
//   printf("%d not in the array\n", target);
// }



int recurBinarySearch(int arr[], int start, int end, int target) {
  int mid = start + (end - start) / 2;
  // base case
  if (arr[mid] == target) return mid;
  if (start >= end) return -1;

  // recursive step
  if (arr[mid] < target) {
    mid = recurBinarySearch(arr, mid + 1, end, target);
  }

  if (arr[mid] > target) {
    mid = recurBinarySearch(arr, start, mid - 1, target);
  }

  return mid;
}






// int recurBinarySearch(int arr[], int start, int end, int mid, int target) {
//   int retval;
//   // base case
//   if (arr[mid] == target) return mid;
//   if (start >= end) return -1;
//
//   // recursive step
//   if (arr[mid] < target) {
//     retval = recurBinarySearch(arr, mid + 1, end, (mid + 1 + (end - mid - 1) / 2), target);
//   }
//
//   if (arr[mid] > target) {
//     retval = recurBinarySearch(arr, start, mid - 1, (start + (mid - 1 - start) / 2), target);
//   }
//
//   return retval;
// }
