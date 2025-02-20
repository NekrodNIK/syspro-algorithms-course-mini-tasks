package main

func isIdealPermutation(nums []int) bool {
	local := 0
	mx := 0
	for i := 0; i < len(nums)-1; i++ {
		mx = max(mx, nums[i])
		if nums[i] > nums[i+1] {
			local++
		}
	}

	global := mergeSort(nums)
	return local == global
}
