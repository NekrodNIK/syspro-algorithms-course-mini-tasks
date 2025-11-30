package task45

import scala.collection.immutable.BitSet
import scala.collection.mutable.HashMap
import scala.util.Random
import java.time.LocalDateTime
import java.time.Duration

type AdjMatrix = Array[Array[Int]]

extension (lhs: Int)
  def saturating_add(rhs: Int): Int =
    val sum = lhs.toLong + rhs.toLong
    if sum >= Int.MaxValue then Int.MaxValue
    else sum.toInt

def naive(graph: AdjMatrix): Int =
  if graph.size == 2 then graph(0)(1) + graph(1)(0)
  else
    (1 until graph.size).permutations.map { p =>
      graph(0)(p.head)
        + p.sliding(2).map(t => graph(t(0))(t(1))).sum
        + graph(p.last)(0)
    }.min

def bhk(graph: AdjMatrix): Int =
  val n = graph.size
  if n == 2 then graph(0)(1) + graph(1)(0)
  else
    val arr = Array.fill(n)(HashMap[BitSet, Int]().withDefault(_ => Int.MaxValue))
    arr(0)(BitSet(0)) = 0

    for
      m <- 2 to n
      s <- BitSet.fromSpecific(1 until n).subsets(m - 1).map(_ + 0)
      v <- s
      if v != 0
    do
      arr(v)(s) = s.iterator
        .filter(_ != v)
        .map(w => arr(w)(s - v).saturating_add(graph(w)(v)))
        .min

    (1 until n)
      .map(v => arr(v)(BitSet.fromSpecific(0 until n)).saturating_add(graph(v)(0)))
      .min

def generate(size: Int, from: Int, to: Int): AdjMatrix =
  val random = new Random()
  Array.tabulate(size, size)((i, j) => if i == j then 0 else random.between(from, to+1))

@main def main: Unit =
  for n <- 2 to 300 do
    val graph = generate(n, 1, Math.pow(10, 5).toInt)

    val start_naive  = LocalDateTime.now()
    val result_naive = naive(graph)
    val end_naive    = LocalDateTime.now()

    val start_bhk  = LocalDateTime.now()
    val result_bhk = bhk(graph)
    val end_bhk    = LocalDateTime.now()

    val duration_naive = Duration.between(start_naive, end_naive).toMillis()
    val duration_bhk   = Duration.between(start_bhk, end_bhk).toMillis()

    assert(result_naive == result_bhk)
    println(s"n=$n: naive=${duration_naive}ms, bhk=${duration_bhk}ms")
