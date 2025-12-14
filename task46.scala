package task46

import scala.collection.mutable

case class Node(
    parent: Node,
    charToParent: Char,
    var suffLink: Node = null,
    var terminal: Boolean = false,
    go: mutable.Map[Char, Node] = mutable.Map.empty
)

case class FilterResult(
    triggers: Map[String, Int],
    total: Int
)


class SpamFilter {
  private val root = Node(null, ' ')
  private case class MapValue(
    var node: Node,
    var counter: Int
  )
  private val triggerMap = mutable.Map[String, MapValue]()

  private def suf(v: Node): Node = {
    if v.suffLink == null then
      v.suffLink =
        if v == root || v.parent == root then root
        else next(suf(v.parent), v.charToParent)
    v.suffLink
  }

  private def next(v: Node, c: Char): Node = {
    if !v.go.contains(c) then
      v.go(c) =
        if v == root then root
        else next(suf(v), c)
    v.go(c)
  }

  def addTrigger(trigger: String): Unit = {
    val v = trigger.foldRight(root)((c, v) => v.go.getOrElseUpdate(c, Node(v, c)))
    v.terminal = true
    triggerMap(trigger) = MapValue(v, 0)
  }
  def addTriggers(triggers: Iterable[String]): Unit = triggers.foreach(addTrigger(_))

  def apply(str: String): FilterResult = {
    triggerMap.keys.foreach(triggerMap(_).counter = 0)

    var v = root
    for i <- 0 until str.length do
      v = next(v, str(i))

      var temp = v
      while temp != root do
        if temp.terminal then
          triggerMap.find { case (trigger, _) => temp == triggerMap(trigger)._1 } match {
            case Some((trigger, _)) => triggerMap(trigger).counter += 1
            case None               =>
          }
        temp = suf(temp)

    val total = triggerMap.values.map(_.counter).sum
    FilterResult(triggerMap.mapValues(_.counter).toMap, total)
  }
}

object SpamFilter {
  def apply(initial_triggers: Iterable[String]): SpamFilter = {
    val obj = new SpamFilter
    obj.addTriggers(initial_triggers)
    obj
  }
}

@main def main: Unit = {
  val spam_filter = SpamFilter(Seq("buy", "cat", "octocat", "toc", "octo", "crypto", "binance", "easy money"))
  val result      = spam_filter("crypto buy now easy money buybinancecryptooctocatbuy")

  println(s"Triggers: ${result.triggers}")
  println(s"Total: ${result.total}")
}
