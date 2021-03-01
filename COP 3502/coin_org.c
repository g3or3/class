#include <stdio.h>



int main() {
  return 0;
}

//
// #include <stdio.h>
// #include <stdio.h>
//
//
// void printArray(int array[]. int size) {
//   for (int i = 0; i < size; i++) {
//     printf("%d ", array[i]);
//   }
//   printf("\n");
// }
//
// void mergeSort(int array[], int l, int h) {
//   if (l < h) {
//     int mid = l + (h - l) / 2;
//     mergeSort(array, l, mid);
//     mergeSort(array, mid + 1, h);
//     merge(array, l, mid, h);
//   }
// }
//
// void merge(int array[], int l, int mid, int h) {
//   int n1 = mid - l + 1;
//   int n2 = h - mid;
//
//   int left[n1], right[n2];
//
//   for (int i = 0; i < n1; i++) {
//     left[i] = array[l];
//     l++;
//   }
//
//   for(int j = 0; i < n2; i++) {
//     array[j] = array[l]
//     l++;
//   }
//
//   int i = 0, j = 0, k = l;
//
//   while(i <= n1 && j <= n2) {
//     if (left[i] <= right[j]) {
//       array[k] = left[i];
//       i++;
//     }
//     else {
//       array[k] = right[j];
//       j++;
//     }
//     k++;
//   }
//
//   while (i <= n1) {
//     array[k] = left[i];
//     i++;
//     k++;
//   }
//   while (j <= n2) {
//     array[k] = right[j];
//     j++;
//     k++;
//   }
// }
//
// int main() {
//   int array[] = {10, 3, 12, 32, 7, 20, 4};
//   int size = sizeof(array)/sizeof(array[0]);
//
//   printf("The array is: \n");
//   printArray(array, size);
//
//   mergeSort(array, 0, size - 1);
//
//   printf("The sorted array is: \n");
//   printArray(array, size);
//
//   return 0;
// }
