class Queue[A](val f: LazyList[A], val r: List[A], val s: LazyList[A]):
  def isEmpty: Boolean = f.isEmpty

  def snoc(x: A): Queue[A] = Queue(f, x :: r, s)

  def head: A = f match
    case x #:: _ => x

  def tail: Queue[A] = f match
    case _ #:: f1 => Queue(f1, r, s)

object Queue:
  def one[A](first: A): Queue[A] =
    Queue(LazyList.empty, List(first), LazyList.empty)
  
  def apply[A](f: LazyList[A], r: List[A], s: LazyList[A]): Queue[A] =
    if !s.isEmpty then
      new Queue(f, r, s.tail)
    else
      val f1 = rotate(f, r, LazyList.empty)
      new Queue(f1, Nil, f1)

  def unapply[A](q: Queue[A]) = (q.f, q.r, q.s)

def rotate[A](f: LazyList[A], r: List[A], a: LazyList[A]): LazyList[A] = (f, r) match
  case (Nil, y :: _)       => y #:: a
  case (x #:: xs, y :: ys) => x #:: rotate(xs, ys, y #:: a)
  case _                   => sys.error("rotate")

@main def main =
  val v0 = Queue.one(0)    
  val v1 = v0.snoc(1)
  val v2 = v1.snoc(2)
  val v3 = v2.snoc(3)
  val v4 = v3.snoc(4)

  val v5 = v4.tail
  val v6 = v5.tail
  val v7 = v6.tail
  val v8 = v7.tail

  assert(v0.head == 0)
  assert(v1.head == 0)
  assert(v2.head == 0)
  assert(v3.head == 0)
  assert(v4.head == 0)
  assert(v5.head == 1)
  assert(v6.head == 2)
  assert(v7.head == 3)
  assert(v8.head == 4)

  var v = v3.snoc(5)
  assert(v.head == 0)
  v = v.tail
  assert(v.head == 1)
  v = v.tail
  val v9 = v
  assert(v.head == 2)
  v = v.tail
  assert(v.head == 3)
  v = v.tail
  assert(v.head == 5)

  v = v9.snoc(6)
  assert(v.head == 2)
  v = v.tail
  assert(v.head == 3)
  v = v.tail
  assert(v.head == 5)
  v = v.tail
  assert(v.head == 6)

  println("All tests passed")

  
  

  
