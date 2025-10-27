object Solution:
  def findTheCity(n: Int, edges: Array[Array[Int]], distanceThreshold: Int): Int =
    var B = Array.fill(n, n)(Int.MaxValue)

    for i <- 0 until n
    do B(i)(i) = 0

    for (from, to, w) <- edges.iterator.map((arr) => (arr(0), arr(1), arr(2)))
    do
      B(from)(to) = w
      B(to)(from) = w

    for 
      k <- 0 until n
      i <- 0 until n
      j <- 0 until n
      if (B(i)(k) != Int.MaxValue && B(k)(j) != Int.MaxValue)
    do B(i)(j) = Math.min(B(i)(j), B(i)(k) + B(k)(j))

    var ansInd = Int.MaxValue
    var ansCnt = Int.MaxValue

    for i <- 0 until n
    do
      var cnt = 0
      for
        j <- 0 until n
        if (i != j && B(i)(j) <= distanceThreshold)
      do cnt += 1

      if (cnt <= ansCnt)
        ansInd = i
        ansCnt = cnt

    ansInd
