#include <span>
#include <vector>
class Solution {
public:
  void merge(std::span<int> left, std::span<int> right, std::vector<int>& res) {
    auto i = 0, j = 0, k = 0;

    while (k < res.size() && i < left.size() && j < right.size()) {
      if (left[i] <= right[j]) {
        res[k++] = left[i++];
      } else {
        res[k++] = right[j++];
      }
    }

    while (i < left.size())
      res[k++] = left[i++];
    while (j < right.size())
      res[k++] = right[j++];
  }

  void mergeSort(std::span<int> arr) {
    if (arr.size() <= 1)
      return;
    if (arr.size() == 2) {
      if (arr[0] > arr[1])
        std::swap(arr[0], arr[1]);
      return;
    }

    auto mid = arr.size() / 2;

    auto left = arr.subspan(0, mid);
    auto right = arr.subspan(mid, arr.size() - mid);

    std::vector<int> buf(arr.size());
    mergeSort(left);
    mergeSort(right);
    merge(left, right, buf);

    for (size_t i = 0; i < arr.size(); i++)
      arr[i] = buf[i];
  }

  std::vector<int> sortArray(std::vector<int>& nums) {
    mergeSort(nums);
    return nums;
  }
};
