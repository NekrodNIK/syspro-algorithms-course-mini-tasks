package main

func merge(left, right []int) ([]int, int) {
	result := make([]int, len(left)+len(right))
	i, j, k := 0, 0, 0
	counter := 0

	for i < len(left) && j < len(right) {
		if left[i] <= right[j] {
			result[k] = left[i]
			k++
			i++
		} else {
			result[k] = right[j]
			counter += len(left) - i
			k++
			j++
		}
	}

	for i < len(left) {
		result[k] = left[i]
		k++
		i++
	}

	for j < len(right) {
		result[k] = right[j]
		k++
		j++
	}

	return result, counter
}

func mergeSort(arr []int) int {
	if len(arr) == 1 {
		return 0
	}

	mid := len(arr) / 2
	c1 := mergeSort(arr[:mid])
	c2 := mergeSort(arr[mid:])

	result, c3 := merge(arr[:mid], arr[mid:])
	copy(arr, result)
	return c1 + c2 + c3
}

func isIdealPermutation(nums []int) bool {
	local := 0
	for i := 0; i < len(nums)-1; i++ {
		if nums[i] > nums[i+1] {
			local++
		}
	}

	global := mergeSort(nums)
	return local == global
}
