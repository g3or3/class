#include <stdio.h>

void binarySearch(int arr[], int, int);

int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int main() {
  binarySearch(arr, 10, 0);
}

void binarySearch(int arr[], int size, int target) {
  int lo = 0;
  int hi = size - 1;
  int mid;

  while (lo <= hi) {
    mid = lo + (hi - lo) / 2;
    if (arr[mid] == target) {
      printf("%d is the index\n", mid);
      return;
    }
    if (arr[mid] < target) lo = mid + 1;
    if (arr[mid] > target) hi = mid - 1;
  }
  printf("%d not in the array\n", target);
}
