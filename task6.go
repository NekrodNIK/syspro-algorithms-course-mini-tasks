package main

func step_calc(prev int) int {
	if prev <= 1 {
		return 0
	}
	return prev/2 + prev%2
}

func inPlaceMergeSort(arr []int) {
	if len(arr) <= 1 {
		return
	}

	mid := len(arr) / 2

	mergeSort(arr[:mid])
	mergeSort(arr[mid:])

	l := len(arr) - 1
	k := l/2 + l%2
	for k > 0 {
		for j := k; j <= l; j++ {
			i := j - k
			if arr[i] > arr[j] {
				arr[i], arr[j] = arr[j], arr[i]
			}
		}
		k = step_calc(k)
	}

}

func sortArray(nums []int) []int {
	inPlaceMergeSort(nums)
	return nums
}
