package main

import (
	"math/rand"
)

func partition(arr []int) int {
	i := -1
	j := len(arr)

	pivot := arr[rand.Intn(len(arr))]
	for {
		i++
		for arr[i] < pivot {
			i++
		}

		j--
		for arr[j] > pivot {
			j--
		}

		if i >= j {
			break
		}

		arr[i], arr[j] = arr[j], arr[i]
	}
	return i
}

func kth(arr []int, k int) int {
	for {
		if len(arr) == 1 {
			return arr[0]
		}

		p := partition(arr)

		if p+1 == k {
			return arr[p]
		}

		if p+1 > k {
			arr = arr[:p]
		} else {
			arr = arr[p+1:]
			k -= p + 1
		}
	}
}

func findMainPipeline(arr []int) int {
	mid := len(arr) / 2

	lower := kth(arr, mid)
	upper := kth(arr, mid+1)
	if len(arr)%2 == 0 {
		return (lower + upper) / 2
	}

	return upper
}

func main() {
	
}
