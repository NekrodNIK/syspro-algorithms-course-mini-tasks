#include <stdbool.h>
#include <stdlib.h>
// #define HOARE_MODE

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void lomutoQuicksort(int* arr, int low, int high) {
  if (low >= high)
    return;

  int pivot = arr[(low + rand() % (high - low + 1))];
  int l = low, h = low;

  for (int c = low; c <= high; c++) {
    if (arr[c] == pivot)
      swap(arr + h++, arr + c);
    else if (arr[c] < pivot) {
      int tmp = arr[c];
      arr[c] = arr[h];
      arr[h++] = arr[l];
      arr[l++] = tmp;
    }
  }

  lomutoQuicksort(arr, low, l - 1);
  lomutoQuicksort(arr, h, high);
}

void hoareQuicksort(int* arr, int low, int high) {
  if (low >= high)
    return;

  int pivot = arr[(low + rand() % (high - low + 1))];
  int i = low - 1, j = high + 1;
  
  for (;;) {
    while (arr[++i] < pivot);
    while (arr[--j] > pivot);
    if (i >= j) break;

    swap(arr + i, arr + j);
  }

  hoareQuicksort(arr, low, j);
  hoareQuicksort(arr, j + 1, high);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
#ifdef HOARE_MODE
  hoareQuicksort(nums, 0, numsSize - 1);
#else
  lomutoQuicksort(nums, 0, numsSize - 1);
#endif
  *returnSize = numsSize;
  return nums;
}
