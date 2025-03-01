package main

import (
	"fmt"
)

func insertion_sort_k(arr []string, k int) {
	for i := k; i < len(arr); i++ {
		for j := i; j >= k && arr[j-k] > arr[j]; j -= k {
			arr[j-k], arr[j] = arr[j], arr[j-k]
		}
	}
}

func shell_sort(arr []string) {
	ki := []int{4193, 1073, 281, 77, 23, 8, 1}
	for _, k := range ki {
		insertion_sort_k(arr, k)
	}
}

func cntSort(arr []string, res []string, pos int) {
	cnt := make([]int, 256)
	for _, v := range arr {
		cnt[v[pos]]++
	}

	for i := 1; i < 256; i++ {
		cnt[i] += cnt[i-1]
	}

	for i := len(arr) - 1; i >= 0; i-- {
		res[cnt[arr[i][pos]]-1] = arr[i]
		cnt[arr[i][pos]]--
	}
}

func radixSort(arr []string) {
	res := make([]string, len(arr))
	for i := len(arr[0]) - 1; i >= 0; i-- {
		cntSort(arr, res, i)
		arr, res = res, arr
	}
	copy(res, arr)
}

func main() {
	arr1 :=
		[]string{"hello", "words", "apple", "droid", "mango", "snake",
				 "merge", "world", "sorts", "radix", "shell", "round",
			     "force", "stash", "build", "power", "langs", "talks",
			     "reads", "write", "algos", "array", "light", "sleep",
			     "image", "books", "tools", "chain", "links", "point"}
	arr2 := make([]string, len(arr1))
	copy(arr2, arr1)

	radixSort(arr1)
	shell_sort(arr2)

	for i := 0; i < len(arr1); i++ {
		if arr1[i] != arr2[i] {
			panic("Not equal")
		}
	}
	fmt.Println("Equal:", arr1)
}
