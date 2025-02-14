package main

// leetcode:
// https://leetcode.com/problems/h-index/submissions/1543141394

func insertion_sort_k(arr []int, k int) {
	for i := k; i < len(arr); i++ {
		for j := i; j >= k && arr[j-k] < arr[j]; j -= k {
			arr[j-k], arr[j] = arr[j], arr[j-k]
		}
	}
}

func shell_sort(arr []int) {
	ki := []int{4193, 1073, 281, 77, 23, 8, 1}
	for _, k := range ki {
		insertion_sort_k(arr, k)
	}
}

func hIndex(citations []int) int {
	shell_sort(citations)

	for i, c := range citations {
		if i >= c {
			return i
		}
	}

	return len(citations)
}
