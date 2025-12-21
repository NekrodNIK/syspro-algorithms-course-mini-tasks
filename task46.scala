package task46

import scala.collection.mutable
import scala.collection.mutable.ArrayBuffer

class Node(
    val parent: Node,
    val charToParent: Char,
    var suffLink: Node = null,
    var terminal: String = null,
    val go: mutable.Map[Char, Node] = mutable.Map.empty,
    val goSuff: mutable.Map[Char, Node] = mutable.Map.empty,
    var count: Int = 0
)

case class FilterResult(
    triggers: Map[String, Int],
    total: Int
)

class SpamFilter {
  private var root: Node = Node(null, ' ')

  private def suf(v: Node): Node = {
    if v.suffLink == null then
      v.suffLink =
        if v == root || v.parent == root then root
        else next(suf(v.parent), v.charToParent)
    v.suffLink
  }

  private def next(v: Node, c: Char): Node = {
    if !v.go.contains(c) then
      v.goSuff(c) = if v == root then root else next(suf(v), c)
      v.goSuff(c)
    else
      v.go(c)
  }

  private def invalidateSuffix(cur: Node): Unit = {
    for child <- cur.go.values do {
      invalidateSuffix(child)
      cur.goSuff.clear()
      cur.suffLink = null
    }        
  }

  def addTrigger(trigger: String): Unit = {
    var v = root
    for c <- trigger do
      v = v.go.getOrElseUpdate(c, Node(v, c))
    v.terminal = trigger

    invalidateSuffix(root)
  }

  def apply(str: String): FilterResult = {  
    val map   = mutable.HashMap[String, Int]().withDefaultValue(0)
    var total = 0

    var cur = root

    val visited = mutable.HashSet[Node]()

    for s <- str do
      cur = next(cur, s)

      if !visited.contains(cur) then
        cur.count = 0
        visited += cur
      cur.count += 1

      var suf_node = cur
      while suf_node != root do
        val trigger = suf_node.terminal
        if trigger != null then
          map(trigger) += cur.count
          total += cur.count
        suf_node = suf(suf_node)

    FilterResult(map.toMap, total)
  }

}

object SpamFilter {
  def apply(initial_triggers: Iterable[String]): SpamFilter = {
    val obj = new SpamFilter()

    for trigger <- initial_triggers do {
      var v = obj.root
      for c <- trigger do
        v = v.go.getOrElseUpdate(c, Node(v, c))
      v.terminal = trigger
    }

    obj
  }
}

@main def main: Unit = {
  val spam_filter = SpamFilter(
    Seq(
      "buy",
      "easy money",
      "spam",
      "buy now",
      "free money",
      "click now",
      "click",
      "money",
      "binance",
      "bitcoin",
      "ton",
      "now"
    )
  )
  val str = "easy money making with cryptocurrency (ton, bitcoin, ethereum) - click now and start making money"

  var result = spam_filter(str)
  println(s"Triggers: ${result.triggers}")
  println(s"Total: ${result.total}")

  spam_filter.addTrigger("ethereum")
  result = spam_filter(str)
  println(s"Triggers: ${result.triggers}")
  println(s"Total: ${result.total}")

  result = spam_filter("easy money")
  println(s"Triggers: ${result.triggers}")
  println(s"Total: ${result.total}")
}
