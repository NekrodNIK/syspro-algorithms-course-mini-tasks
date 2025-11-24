package task43

import scala.collection.mutable.ArrayBuffer

class Segtree(
    val lb: Int,
    val rb: Int,
    val left: Option[Segtree],
    val right: Option[Segtree],
    val number: Int
):
  def isLeaf           = left.isEmpty && right.isEmpty
  def isNode           = !isLeaf

  def revive(i: Int): Segtree =
    if lb <= i && i <= rb then
      if isNode then Segtree.node(left.get.revive(i), right.get.revive(i))
      else Segtree.leaf(i, 1)
    else this

  def query(l: Int, r: Int): Int =
    if l > r then 0
    else if l <= lb && rb <= r then number
    else
      val m = (lb + rb) / 2
      left.get.query(l, Math.min(r, m)) + right.get.query(Math.max(l, m + 1), r)

object Segtree:
  def node(left: Segtree, right: Segtree): Segtree =
    this(left.lb, right.rb, Some(left), Some(right), left.number + right.number)

  def leaf(i: Int, number: Int): Segtree =
    this(i, i, None, None, number)

class Gte(val arr: Array[Int], val versions: Array[Segtree]):
  def apply(l: Int, r: Int, x: Int): Int =
    var low  = 0
    var high = arr.length

    while low < high do
      val mid = low + (high - low) / 2
      if arr(mid) < x then low = mid + 1
      else high = mid

    if arr.size - low < versions.size then versions(arr.size - low).query(l, r)
    else 0

object Gte:
  def build_zero(n: Int): Segtree =
    def inner(lb: Int, rb: Int): Segtree =
      if lb == rb then Segtree.leaf(lb, 0)
      else
        val m = (lb + rb) / 2
        Segtree.node(inner(lb, m), inner(m + 1, rb))
    inner(0, n - 1)

  def apply(arr: Array[Int]): Gte =
    val versions = ArrayBuffer[Segtree]()
    versions.addOne(build_zero(arr.length))
    
    val (sorted, ind) = arr.zipWithIndex.sorted.unzip
    ind.reverse.foreach(i => versions.addOne(versions.last.revive(i)))

    new Gte(sorted, versions.toArray)

def test1 =
  println("TEST1")
  var arr   = Array(1, 3, 5, 7, 9, 2, 4, 6, 8, 10)
  var gte   = Gte(arr)
  var tests = Array(
    (0, 9, 1),
    (0, 9, 10),
    (0, 9, 11),
    (0, 4, 3),
    (5, 9, 6),
    (2, 7, 4),
    (10, 5, 5),
    (3, 3, 5),
    (3, 3, 8)
  )
  check(arr, gte.apply, tests)

def test2 =
  println("TEST2")
  val arr   = Array(2, 2, 2, 5, 5, 5, 8, 8, 8)
  val gte   = Gte(arr)
  val tests = Array(
    (0, 8, 2),
    (0, 8, 5),
    (0, 8, 6),
    (0, 8, 8),
    (0, 8, 9)
  )
  check(arr, gte.apply, tests)

def test3 =
  println("TEST3")
  val arr   = Array(42)
  val gte   = Gte(arr)
  val tests = Array(
    (0, 0, 42),
    (0, 0, 41),
    (0, 0, 1),
    (0, 0, 43),
    (0, 0, 44)
  )
  check(arr, gte.apply, tests)

def check(
    arr: Array[Int],
    gte: (Int, Int, Int) => Int,
    tests: Iterable[(Int, Int, Int)]
): Unit =
  for (l, r, x) <- tests do
    val result   = gte(l, r, x)
    var expected = arr.slice(l, r + 1).count(_ >= x)
    val sign     = if result == expected then "==" else "!="
    println(s"$result $sign $expected")
    if result != expected then System.exit(0)

@main def main =
  test1
  test2
  test3
  println("all tests passed")
