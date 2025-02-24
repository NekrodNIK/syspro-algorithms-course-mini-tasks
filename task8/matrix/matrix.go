package matrix

type Row []int
type Matrix []Row

func (m Matrix) Rows() int { return len(m) }
func (m Matrix) Cols() int { return len(m[0]) }

func (m Matrix) Sub(from_row, to_row, from_col, to_col int) Matrix {
	sub := MakeMatrix(to_row-from_row, to_col-from_col)

	for i := from_row; i < to_row; i++ {
		for j := from_col; j < to_col; j++ {
			sub[i-from_row][j-from_col] = m[i][j]
		}
	}

	return sub
}

func MakeMatrix(rows, cols int) Matrix {
	m := make(Matrix, rows)

	for i := 0; i < m.Rows(); i++ {
		m[i] = make(Row, cols)
	}

	return m
}

func Equal(m1, m2 Matrix) bool {
	if m1.Rows() != m2.Rows() && m1.Cols() != m2.Cols() {
		return false
	}

	for i := 0; i < m1.Rows(); i++ {
		for j := 0; j < m1.Cols(); j++ {
			if m1[i][j] != m2[i][j] {
				return false
			}
		}
	}
	
	return true
}

func Addition(left, right Matrix) Matrix {
	N, M := left.Rows(), left.Cols()
	res := MakeMatrix(N, M)

	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			res[i][j] = left[i][j] + right[i][j]
		}
	}

	return res
}

func Substract(left, right Matrix) Matrix {
	N, M := left.Rows(), left.Cols()
	res := MakeMatrix(N, M)

	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			res[i][j] = left[i][j] - right[i][j]
		}
	}

	return res
}

func (m Matrix) Split() (A, B, C, D Matrix) {
	A = m.Sub(0, m.Rows()/2, 0, m.Cols()/2)
	B = m.Sub(0, m.Rows()/2, m.Cols()/2, m.Cols())

	C = m.Sub(m.Rows()/2, m.Rows(), 0, m.Cols()/2)
	D = m.Sub(m.Rows()/2, m.Rows(), m.Cols()/2, m.Cols())
	return
}

func Merge(A, B, C, D Matrix) Matrix {
	// AB
	// CD
	cond := A.Rows() == B.Rows() &&
		A.Cols() == C.Cols() &&
		D.Rows() == C.Rows() &&
		D.Cols() == B.Cols()

	if !cond {
		panic("Merge error!")
	}

	N, M := A.Rows()+C.Rows(), A.Cols()+B.Cols()
	res := MakeMatrix(N, M)

	for i := 0; i < A.Rows(); i++ {
		for j := 0; j < A.Cols(); j++ {
			res[i][j] = A[i][j]
		}
	}

	for i := 0; i < B.Rows(); i++ {
		for j := 0; j < B.Cols(); j++ {
			res[i][B.Cols()+j] = B[i][j]
		}
	}

	for i := 0; i < C.Rows(); i++ {
		for j := 0; j < C.Cols(); j++ {
			res[A.Rows()+i][j] = C[i][j]
		}
	}

	for i := 0; i < D.Rows(); i++ {
		for j := 0; j < D.Cols(); j++ {
			res[A.Rows()+i][A.Cols()+j] = D[i][j]
		}
	}

	return res
}
