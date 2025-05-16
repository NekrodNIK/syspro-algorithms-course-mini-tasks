#include <algorithm>
#include <cassert>
#include <span>
#include <vector>

class Solution {
  static std::pair<std::span<int>, std::span<int>> split(std::span<int> arr,
                                                         size_t i) {
    return {arr.subspan(0, i), arr.subspan(i, arr.size() - i)};
  }

  static void merge(std::span<int> lhs, std::span<int> rhs,
                    std::span<int> buf) {
    assert(lhs.size() + rhs.size() <= buf.size());

    int i = 0, j = 0, k = 0;
    while (i < lhs.size() && j < rhs.size())
      std::swap(buf[k++], (lhs[i] < rhs[j]) ? lhs[i++] : rhs[j++]);
    while (i < lhs.size())
      std::swap(buf[k++], lhs[i++]);
    while (j < rhs.size())
      std::swap(buf[k++], rhs[j++]);
  }

  static void mergeSortInternal(std::span<int> arr, std::span<int> buf) {
    assert(arr.size() <= buf.size());

    if (arr.size() == 1)
      std::swap(arr[0], buf[0]);
    if (arr.size() <= 1)
      return;

    auto [lhs, rhs] = split(arr, arr.size() / 2);
    mergeSort(lhs);
    mergeSort(rhs);
    merge(lhs, rhs, buf);
  }

  static void mergeSort(std::span<int> arr) {
    if (arr.size() < 1)
      return;

    size_t mid = (arr.size() + 1) / 2, next = mid;

    auto [left, right] = split(arr, mid);
    mergeSortInternal(left.subspan(0, right.size()), right);
    while (mid > 1) {
      mid = next;
      next = (mid + 1) / 2;
      std::tie(left, right) = split(arr, mid);
      
      auto [ll, lr] = split(left.subspan(0, mid), next);
      auto [_, lr_right] = split(arr, next);

      mergeSortInternal(lr, ll);
      merge(ll.subspan(0, lr.size()), right, lr_right);
    }

    if (mid == 1) {
      for (size_t i = 0; i + 1 < arr.size() && arr[i] > arr[i + 1]; i++)
        std::swap(arr[i], arr[i + 1]);
    }
  }

public:
  static std::vector<int> sortArray(std::vector<int>& nums) {
    mergeSort(nums);
    return nums;
  }
};
