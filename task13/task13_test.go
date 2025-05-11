package task13

import (
	"math/rand"
	"sort"
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestPartition(t *testing.T) {
	arr := make([]int, 10)
	for i := 0; i < 10; i++ {
		arr[i] = rand.Intn(100)
	}

	p := partition(arr)
	assert.GreaterOrEqual(t, p, 0)
	assert.Less(t, p, len(arr))

	for i := p - 1; i >= 0; i-- {
		assert.LessOrEqual(t, arr[i], arr[p])
	}

	for i := p + 1; i < len(arr); i++ {
		assert.GreaterOrEqual(t, arr[i], arr[p])
	}
}

func TestKth(t *testing.T) {
	arr := make([]int, 1000)
	for i := 0; i < 1000; i++ {
		arr[i] = rand.Int()
	}

	sorted := make([]int, 1000)
	copy(sorted, arr)
	sort.Ints(sorted)

	for i := 0; i < 1000; i++ {
		assert.Equal(t, kth(arr, i+1), sorted[i])
	}
}

func TestFindMainPipeline1(t *testing.T) {
	arr := make([]int, 999)
	for i := 0; i < 999; i++ {
		arr[i] = rand.Int()
	}

	actual := FindMainPipeline(arr)
	sort.Ints(arr)
	assert.Equal(t, actual, arr[len(arr)/2])
}

func TestFindMainPipeline2(t *testing.T) {
	arr := make([]int, 1000)
	for i := 0; i < 1000; i++ {
		arr[i] = rand.Int()
	}

	actual := FindMainPipeline(arr)
	sort.Ints(arr)

	mid := len(arr)/2
	assert.Equal(t, actual, (arr[mid-1] + arr[mid]) / 2)
}
