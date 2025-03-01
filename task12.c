#include <assert.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPETITIONS 20
#define MAX_LEN 1048576*2

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
    while (arr[++i] < pivot)
      ;
    while (arr[--j] > pivot)
      ;
    if (i >= j)
      break;

    swap(arr + i, arr + j);
  }

  hoareQuicksort(arr, low, j);
  hoareQuicksort(arr, j + 1, high);
}

int lomutoPartitionBranchFree(int* arr, int first, int last) {
  assert(first <= last);
  if (last - first < 2)
    return first;
  --last;

  if (arr[first] > arr[last])
    swap(arr + first, arr + last);

  int index = first;
  int pivot = arr[first];
  do {
    ++first;
    assert(first <= last);
  } while (arr[first] < pivot);

  for (int i = first + 1; i < last; i++) {
    int smaller = -(arr[i] < pivot);
    int delta = smaller & (i - first);
    arr[first + delta] = arr[first];
    arr[i - delta] = arr[i];
    first -= smaller;
  }
  assert(arr[first] >= pivot);
  --first;
  arr[index] = first;
  arr[first] = pivot;
  return first;
}

void lomutoQuicksortBranchFree(int* arr, int low, int high) {
  if (low >= high) {
    return;
  }
  int pivot = lomutoPartitionBranchFree(arr, low, high);

  lomutoQuicksort(arr, low, pivot - 1);
  lomutoQuicksort(arr, pivot, high);
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
  fillRandom(arr, len);
  
  double* m = (double*)malloc(REPETITIONS * sizeof(double));
  for (size_t i = 0; i < REPETITIONS; i++) {
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
  for (size_t size = 1024; size <= MAX_LEN; size *= 2) {
    timeMeasurement(size, lomuto, m);
    printf("lomuto %zu: %f %f %f\n", size, m[0], m[1], m[2]);
  }
  
  for (size_t size = 1024; size <= MAX_LEN; size *= 2) {
    timeMeasurement(size, hoare, m);
    printf("hoare %zu: %f %f %f\n", size, m[0], m[1], m[2]);
  }
  
  for (size_t size = 1024; size <= MAX_LEN; size *= 2) {
    timeMeasurement(size, lomutoBF, m);
    printf("lomutoBF %zu: %f %f %f\n", size, m[0], m[1], m[2]);
  }
}
