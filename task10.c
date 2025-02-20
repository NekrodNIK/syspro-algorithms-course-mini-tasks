#include <stddef.h>

void sortColors(int* nums, int numsSize) {
  size_t C[3] = {0};
  for (size_t i = 0; i < numsSize; i++)
    C[nums[i]]++;

  size_t k = 0;
  for (int i = 0; i < 3; i++) {
    while (C[i] > 0) {
      nums[k++] = i;
      C[i]--;
    }
  }
}

