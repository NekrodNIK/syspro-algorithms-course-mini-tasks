package main

func mergeSort(arr []int) {
	if len(arr) <= 1 {
		return
	}

	mid := len(arr) / 2

	mergeSort(arr[:mid])
	mergeSort(arr[mid:])

	l := len(arr) - 1
	g := l/2 + l%2

	for g > 0 {
		for j := g; j <= l; j++ {
			i := j - g
			if arr[i] > arr[j] {
				arr[i], arr[j] = arr[j], arr[i]
			}
		}
		if g <= 1 {
			g = 0
		} else {
			g = g/2 + g%2
		}
	}

}

func sortArray(nums []int) []int {
	mergeSort(nums)
	return nums
}

