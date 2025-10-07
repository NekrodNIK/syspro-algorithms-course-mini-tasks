object Solution:
    def isMatch(s: String, p: String): Boolean =
        val arr = Array.ofDim[Boolean](s.length + 1, p.length + 1)

        arr(0)(0) = true

        for (j <- 1 until p.length if p(j) == '*')
            arr(0)(j + 1) = arr(0)(j - 1)

        val is_match = (x: Int, y: Int) => (p(y) == '.' || s(x) == p(y))
        for (i <- 0 until s.length; j <- 0 until p.length) {
            if (p(j) == '*') {
                arr(i+1)(j+1) = (is_match(i, j-1) && arr(i)(j+1)) || arr(i+1)(j-1)
            } else if (is_match(i, j)) {
                arr(i+1)(j+1) = arr(i)(j)
            }
        }
        
        arr(s.length)(p.length)

