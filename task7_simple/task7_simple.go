package main

func isIdealPermutation(nums []int) bool {
	mx := 0
	for i := 0; i < len(nums)-1; i++ {
		if mx > nums[i+1] {
			return false
		}
        mx = max(mx, nums[i])
	}
	return true
}
