package main

import "slices"

func countingSort(arr []int) {
	C := make([]int, slices.Max(arr)+1)
	for _, v := range arr {
		C[v]++
	}

	k := 0
	for i := len(C) - 1; i >= 0; i-- {
		for C[i] > 0 {
			arr[k] = i

			k++
			C[i]--
		}
	}
}

func wiggleSort(arr []int) {
	countingSort(arr)

	m := len(arr) / 2
	left, right := arr[:m], arr[m:]

	res := make([]int, len(arr))
	for i := 0; i < len(arr); i++ {
		if i%2 == 0 {
			res[i] = right[i/2]
		} else {
			res[i] = left[i/2]
		}
	}
	copy(arr, res)
}
