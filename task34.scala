object Solution:
  def numTrees(n: Int): Int =
    val arr = Array.fill(n + 1)(0)
    arr(0) = 1
    
    for
      i <- 1 to n
      j <- 1 to i
    do arr(i) += arr(j - 1) * arr(i - j)
    arr(n)
