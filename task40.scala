// https://leetcode.com/problems/range-sum-query-mutable/
import Math.min
import Math.max

class NumArray(nums: Array[Int]):
  val N = nums.size
  val t = Array.fill(4 * N)(0)
  build(1, 0, N - 1)

  def build(v: Int, tl: Int, tr: Int): Unit =
    if tl == tr then t(v) = nums(tl)
    else
      val m = (tl + tr) / 2
      build(v * 2, tl, m)
      build(v * 2 + 1, m + 1, tr)
      t(v) = t(v * 2) + t(v * 2 + 1)

  def update(index: Int, value: Int): Unit =
    def inner(v: Int, tl: Int, tr: Int, pos: Int, new_val: Int): Unit =
      if tl == tr then t(v) = new_val
      else
        val tm = (tl + tr) / 2
        if pos <= tm then inner(v * 2, tl, tm, pos, new_val)
        else inner(v * 2 + 1, tm + 1, tr, pos, new_val)
        t(v) = t(v * 2) + t(v * 2 + 1)
    inner(1, 0, N - 1, index, value)

  def sumRange(left: Int, right: Int): Int =
    def inner(v: Int, tl: Int, tr: Int, l: Int, r: Int): Int =
      if l > r then 0
      else if l == tl && r == tr then t(v)
      else
        val tm = (tl + tr) / 2
        inner(v * 2, tl, tm, l, min(r, tm)) + inner(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r)
    inner(1, 0, N - 1, left, right)
