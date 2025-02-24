package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"task8/matrix"
	"time"
)

const minMatrixSize = 64
const maxMatrixSize = 1024
const repetitions = 20

func fillRandom(m matrix.Matrix) {
	for i := 0; i < m.Rows(); i++ {
		for j := 0; j < m.Cols(); j++ {
			m[i][j] = rand.Int()
		}
	}
}

func sampleMean(measurements []float64) float64 {
	mean := 0.

	for i := 0; i < len(measurements); i++ {
		mean += measurements[i]
	}

	mean /= float64(len(measurements))
	return mean
}

func standardDeviation(measurements []float64) float64 {
	mean := sampleMean(measurements)
	dev := 0.

	for i := 0; i < len(measurements); i++ {
		v := measurements[i] - mean
		dev += v * v
	}

	dev /= float64(len(measurements))
	dev = math.Sqrt(dev)
	return dev
}

func geometricMean(measurements []float64) float64 {
	mean := 1.

	for i := 0; i < len(measurements); i++ {
		mean *= measurements[i]
	}

	mean = math.Pow(mean, 1/float64(len(measurements)))
	return mean
}

type multFunc func(l, r matrix.Matrix) matrix.Matrix

func time_measurement(f multFunc, size int) (sample, deviation, geometric float64) {
	l := matrix.MakeMatrix(size, size)
	r := matrix.MakeMatrix(size, size)
	fillRandom(l)
	fillRandom(r)

	measurements := make([]float64, repetitions)
	for i := 0; i < repetitions; i++ {
		start := time.Now()
		f(l, r)
		measurements[i] = time.Since(start).Seconds()
	}

	sample = sampleMean(measurements)
	deviation = standardDeviation(measurements)
	geometric = geometricMean(measurements)
	return
}

func main() {
	file, err := os.Create("results.csv")
	if err != nil {
		panic("Unable to open file")
	}
	defer file.Close()
	
	for i := minMatrixSize; i <= maxMatrixSize; i *= 2 {
		s, d, g := time_measurement(matrix.ClassicMult, i)
		fmt.Fprintf(file, "Classic %d;%f;%f;%f\n", i, s, d, g)
		fmt.Printf("Classic; %d; %f; %f; %f;\n", i, s, d, g)
	}
	
	
	for i := minMatrixSize; i <= maxMatrixSize; i *= 2 {
		s, d, g := time_measurement(matrix.Recursive8Mult, i)
		fmt.Fprintf(file, "Recursive %d;%f;%f;%f\n", i, s, d, g)
		fmt.Printf("Recursive; %d; %f; %f; %f;\n", i, s, d, g)
	}

	
	for i := minMatrixSize; i <= maxMatrixSize; i *= 2 {
		s, d, g := time_measurement(matrix.StrassenMult, i)
		fmt.Fprintf(file, "Strassen %d;%f;%f;%f\n", i, s, d, g)
		fmt.Printf("Strassen; %d; %f; %f; %f;\n", i, s, d, g)
	}

	fmt.Println("File written!")
}
