#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPETITIONS 10

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
    if (i >= j)
      break;

    swap(arr + i, arr + j);
  }

  hoareQuicksort(arr, low, j);
  hoareQuicksort(arr, j + 1, high);
}

size_t lomutoPartitionBranchFree(int* a, size_t first, size_t last) {
  if (last - first < 2)
    return first;
  last--;
  if (a[first] > a[last])
    swap(a + first, a + last);
  size_t pivot_pos = first;
  int pivot = a[first];

  while (a[++first] < pivot);
  for (size_t read = first + 1; read < last; read++) {
    int x = a[read];
    int smaller = -(int)(x < pivot);
    int delta = smaller & (read - first);
    a[first + delta] = a[first];
    a[read - delta] = x;
    first -= smaller;
  }
  first--;
  a[pivot_pos] = a[first];
  a[first] = pivot;
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
  double m[3];
  for (size_t size = 1024; size <= 1000000000; size *= 2) {
    timeMeasurement(size, lomuto, m);
    printf("%zu: %f %f %f -- ", size, m[0], m[1], m[2]);
    timeMeasurement(size, hoare, m);
    printf("%f %f %f -- ", m[0], m[1], m[2]);
    timeMeasurement(size, lomutoBF, m);
    printf("%f %f %f\n", m[0], m[1], m[2]);
  }
}
