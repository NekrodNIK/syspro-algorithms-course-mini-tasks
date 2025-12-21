class Queue[A](
    val f: List[A] = Nil,
    val f1: List[A] = Nil,
    val r: List[A] = Nil,
    val r1: List[A] = Nil,
    val s: List[A] = Nil,
    val recopy: Boolean = false,
    val toCopy: Int = 0,
    val copied: Boolean = false
):

  def empty =
    !recopy && r.size == 0

  def push(x: A): Queue[A] =
    if !recopy then
      val fn = x :: f
      val Q1 = Queue(fn, f1, r, r1, s, recopy, toCopy, copied)
      Q1.checkRecopy
    else
      val fn1 = x :: f1
      val Q1  = Queue(f, fn1, r, r1, s, recopy, toCopy, copied)
      Q1.checkNormal

  def pop: (Queue[A], A) =
    if !recopy then
      val x :: rn = r: @unchecked
      val Q1      = Queue(f, f1, rn, r1, s, recopy, toCopy, copied)
      (Q1.checkRecopy, x)
    else
      var x :: rn1 = r1: @unchecked
      var curCopy  = toCopy
      var rn       = r

      if toCopy > 0 then curCopy = curCopy - 1
      else
        val _x :: _rn = rn: @unchecked
        x = _x
        rn = _rn

      val Q1 = Queue(f, f1, rn, rn1, s, recopy, toCopy, copied)
      (Q1.checkNormal, x)

  def checkRecopy: Queue[A] =
    if f.size > r.size then
      val Q1 = Queue(f, f1, r, r1, s, true, r.size, false)
      Q1.checkNormal
    else Queue(f, f1, r, r1, s, false, toCopy, copied)

  def checkNormal: Queue[A] =
    val Q1 = additionalOperations
    Queue(Q1.f, Q1.f1, Q1.r, Q1.r1, Q1.s, Q1.s.size != 0, Q1.toCopy, Q1.copied)

  def additionalOperations: Queue[A] =
    var toDo      = 3
    var rn        = r
    var sn        = s
    var curCopied = copied
    while !curCopied && toDo > 0 && rn.size > 0 do
      val x :: _rn = rn: @unchecked
      rn = _rn
      sn = x :: sn
      toDo = toDo - 1

    var fn = f
    while toDo > 0 & fn.size > 0 do
      curCopied = true
      val x :: _fn = fn: @unchecked
      fn = _fn
      rn = x :: rn
    toDo = toDo - 1

    var curCopy = toCopy
    while toDo > 0 && sn.size > 0 do
      val x :: _sn = sn: @unchecked
      sn = _sn
      if curCopy > 0 then rn = x :: rn
      else
        curCopy = curCopy - 1
        toDo = toDo - 1
    var fn1 = f1
    if s.size == 0 then
      val c = fn
      fn = fn1
      fn1 = c
    Queue(fn, fn1, rn, r1, sn, recopy, curCopy, curCopied)

@main def main =
  val v0 = Queue().push(0)
  val v1 = v0.push(1)
  val v2 = v1.push(2)
  val v3 = v2.push(3)
  val v4 = v3.push(4)

  val v5 = v4.pop._1
  val v6 = v5.pop._1
  val v7 = v6.pop._1
  val v8 = v7.pop._1

  assert(v0.pop._2 == 0)
  assert(v1.pop._2 == 0)
  assert(v2.pop._2 == 0)
  assert(v3.pop._2 == 0)
  assert(v4.pop._2 == 0)
  assert(v5.pop._2 == 1)
  assert(v6.pop._2 == 2)
  assert(v7.pop._2 == 3)
  assert(v8.pop._2 == 4)

  var v = v3.push(5)
  assert(v.pop._2 == 0)
  v = v.pop._1
  assert(v.pop._2 == 1)
  v = v.pop._1
  val v9 = v
  assert(v.pop._2 == 2)
  v = v.pop._1
  assert(v.pop._2 == 3)
  v = v.pop._1
  assert(v.pop._2 == 5)

  v = v9.push(6)
  assert(v.pop._2 == 2)
  v = v.pop._1
  assert(v.pop._2 == 3)
  v = v.pop._1
  assert(v.pop._2 == 5)
  v = v.pop._1
  assert(v.pop._2 == 6)

  println("All tests passed")
