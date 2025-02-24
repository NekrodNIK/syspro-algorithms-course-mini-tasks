package matrix


func ClassicMult(left, right Matrix) Matrix {
	N, K, M := left.Rows(), left.Cols(), right.Cols()
	res := MakeMatrix(N, M)

	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			for k := 0; k < K; k++ {
				res[i][j] += left[i][k] * right[k][j]
			}
		}
	}

	return res
}

func Recursive8Mult(left, right Matrix) Matrix {
	if left.Rows() <= 64 {
		return ClassicMult(left, right);
	}

	A, B, C, D := left.Split()
	E, F, G, H := right.Split()

	Q1 := Addition(Recursive8Mult(A, E), Recursive8Mult(B, G))
	Q2 := Addition(Recursive8Mult(A, F), Recursive8Mult(B, H))
	Q3 := Addition(Recursive8Mult(C, E), Recursive8Mult(D, G))
	Q4 := Addition(Recursive8Mult(C, F), Recursive8Mult(D, H))

	return Merge(Q1, Q2, Q3, Q4)
}

func StrassenMult(left, right Matrix) Matrix {
	if left.Rows() <= 64 {
		return ClassicMult(left, right);
	}

	A, B, C, D := left.Split()
	E, F, G, H := right.Split()

	P1 := StrassenMult(A, Substract(F, H))
	P2 := StrassenMult(Addition(A, B), H)
	P3 := StrassenMult(Addition(C, D), E)
	P4 := StrassenMult(D, Substract(G, E))
	P5 := StrassenMult(Addition(A, D), Addition(E, H))
	P6 := StrassenMult(Substract(B, D), Addition(G, H))
	P7 := StrassenMult(Substract(A, C), Addition(E, F))

	Q1 := Addition(Substract(Addition(P5, P4), P2), P6)
	Q2 := Addition(P1, P2)
	Q3 := Addition(P3, P4)
	Q4 := Substract(Substract(Addition(P1, P5), P3), P7)

	return Merge(Q1, Q2, Q3, Q4)
}

