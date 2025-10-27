class LessThan(val a: Array[Int]):
  private val n = a.length
  private val t = Array.fill(4 * n)(Array.empty[Int])

  private def sortedMerge(left: Array[Int], right: Array[Int]): Array[Int] =
    val res     = Array.fill(left.size + right.size)(0)
    var i, j, k = 0

    while i < left.size && j < right.size do
      if left(i) <= right(j) then
        res(k) = left(i)
        i += 1
      else
        res(k) = right(j)
        j += 1
      k += 1

    while i < left.length do
      res(k) = left(i)
      i += 1
      k += 1

    while j < right.length do
      res(k) = right(j)
      j += 1
      k += 1

    res

  private def build(v: Int, tl: Int, tr: Int): Unit =
    if tl == tr then t(v) = Array(a(tl))
    else
      val tm = (tl + tr) / 2
      build(v * 2, tl, tm)
      build(v * 2 + 1, tm + 1, tr)
      t(v) = sortedMerge(t(v * 2), t(v * 2 + 1))

  private def query(v: Int, tl: Int, tr: Int, l: Int, r: Int, x: Int): Int =
    if l > tr || r < tl then 0
    else if l <= tl && tr <= r then
      var left   = 0
      var right  = t(v).size - 1
      var result = -1

      while left <= right do
        val mid = (left + right) / 2
        if t(v)(mid) < x then
          result = mid
          left = mid + 1
        else right = mid - 1

      result + 1
    else
      val tm = (tl + tr) / 2
      query(v * 2, tl, tm, l, r, x) + query(v * 2 + 1, tm + 1, tr, l, r, x)

  build(1, 0, n - 1)
  def apply(l: Int, r: Int, x: Int): Int =
    query(1, 0, n - 1, l, r, x)

object Solution:
  def countSmaller(nums: Array[Int]): List[Int] =
    val lt = LessThan(nums)
    nums.indices.map(i => lt(i + 1, nums.length, nums(i))).toList
