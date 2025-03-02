#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define REPETITIONS 20

typedef enum {
  lomuto,
  lomutoBF,
  hoare,
} Mode;

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
    if (arr[c] == pivot) {
      swap(arr + h, arr + c);
      h++;
    } else if (arr[c] < pivot) {
      int tmp = arr[c];
      arr[c] = arr[h];
      arr[h] = arr[l];
      arr[l] = tmp;
      h++;
      l++;
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

  while (true) {
    do {
      i++;
    } while (arr[i] < pivot);

    do {
      j--;
    } while (arr[j] > pivot);

    if (i >= j)
      break;

    swap(arr + i, arr + j);
  }

  hoareQuicksort(arr, low, j);
  hoareQuicksort(arr, j + 1, high);
}

int lomutoPartitionBranchFree(int* arr, int first, int last) {
  if (last - first < 2)
    return first;

  last--;
  if (arr[first] > arr[last]) {
    swap(arr + first, arr + last);
  }

  int pivot_pos = first;
  int pivot = arr[first];

  do {
    first++;
  } while (arr[first] < pivot);
  for (int read = first + 1; read < last; read++) {
    int x = arr[read];
    int less = -(x < pivot);
    int delta = less & (read - first);
    
    arr[first + delta] = arr[first];
    arr[read - delta] = x;
    first -= less;
  }

  first--;
  arr[pivot_pos] = arr[first];
  arr[first] = pivot;

  return first;
}

void lomutoQuicksortBranchFree(int* arr, int low, int high) {
  if (low >= high) {
    return;
  }
  int pivot = lomutoPartitionBranchFree(arr, low, high + 1);

  lomutoQuicksortBranchFree(arr, low, pivot);
  lomutoQuicksortBranchFree(arr, pivot + 1, high);
}

int* sortArray(int* nums, int numsSize, Mode mode) {
  switch (mode) {
  case lomuto:
    lomutoQuicksort(nums, 0, numsSize - 1);
    break;
  case hoare:
    hoareQuicksort(nums, 0, numsSize - 1);
    break;
  case lomutoBF:
    lomutoQuicksortBranchFree(nums, 0, numsSize - 1);
    break;
  }

  return nums;
}

double sampleMean(double measurements[], size_t len) {
  double mean = 0.0;
  for (size_t i = 0; i < len; i++)
    mean += measurements[i];

  mean /= len;
  return mean;
}

double standardDeviation(double measurements[], size_t len) {
  double mean = sampleMean(measurements, len);
  double dev = 0.0;

  for (size_t i = 0; i < len; i++) {
    double v = measurements[i] - mean;
    dev += v * v;
  }

  dev /= len;
  dev = sqrt(dev);
  return dev;
}

double geometricMean(double measurements[], size_t len) {
  double mean = 1.0;

  for (size_t i = 0; i < len; i++) {
    mean *= measurements[i];
  }

  mean = pow(mean, 1.0 / len);
  return mean;
}

void fillRandom(int* arr, size_t len) {
  for (size_t i = 0; i < len; i++) {
    arr[i] = rand();
  }
}

void timeMeasurement(size_t len, Mode mode, double* result) {
  int* arr = (int*)malloc(len * sizeof(int));
  double* m = (double*)malloc(REPETITIONS * sizeof(double));

  for (size_t i = 0; i < REPETITIONS; i++) {
    fillRandom(arr, len);

    clock_t start = clock();
    sortArray(arr, len, mode);
    clock_t end = clock();

    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    m[i] = seconds;
  }

  result[0] = sampleMean(m, REPETITIONS);
  result[1] = standardDeviation(m, REPETITIONS);
  result[2] = geometricMean(m, REPETITIONS);

  free(m);
  free(arr);
}

int main() {
  int arr1[1024];
  int arr2[1024];
  int arr3[1024];
  fillRandom(arr1, 1024);
  memcpy(arr2, arr1, 1024*sizeof(int));
  memcpy(arr3, arr1, 1024*sizeof(int));

  sortArray(arr1, 1024, lomuto);
  sortArray(arr2, 1024, hoare);
  sortArray(arr3, 1024, lomutoBF);

  for (size_t i = 0; i < 1024; i++) {
    if (arr1[i] != arr2[i] || arr2[i] != arr3[i] || arr3[i] != arr1[i]) {
      fputs("Not equal", stderr);
      exit(1);
    }
  }
  

  double m[3];
  for (size_t size = 65536; size <= 4294967296; size *= 2) {
    timeMeasurement(size, lomuto, m);
    printf("%9zu: %f %f %f -- ", size, m[0], m[1], m[2]);
    timeMeasurement(size, hoare, m);
    printf("%f %f %f -- ", m[0], m[1], m[2]);
    timeMeasurement(size, lomutoBF, m);
    printf("%f %f %f\n", m[0], m[1], m[2]);
  }
}
