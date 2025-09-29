object Solution:
  def calculateMinimumHP(dungeon: Array[Array[Int]]): Int =
    val n = dungeon.length
    val m = dungeon(0).length
    val arr = Array.fill[Int]((n+1)*(m+1))(Int.MaxValue).grouped(m+1).toArray
    
    arr(n-1)(m) = 1
    arr(n)(m-1) = 1
    
    for (i <- n-1 to 0 by -1; j <- m-1 to 0 by -1)
      arr(i)(j) = Math.max(1, Math.min(arr(i+1)(j), arr(i)(j + 1)) - dungeon(i)(j))
    
    arr(0)(0)
        
