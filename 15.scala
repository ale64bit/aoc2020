object Solution extends App {

  def solve(input: List[Int], target: Int): Int = {
    val m0 = input.zipWithIndex.map { case (x, i) => (x, (i + 1, i + 1)) }.toMap.withDefaultValue((0, 0))
    val (_, ans) = ((input.size + 1) to target).foldLeft(m0, input.last) {
      case ((m, x0), turn) =>
        val (l0, r0) = m(x0)
        val x1 = r0 - l0
        val (_, r1) = m.getOrElse(x1, (turn, turn))
        (m.updated(x1, (r1, turn)), x1)
    }
    ans
  }

  val input = List(6, 19, 0, 5, 7, 13, 1)
  println(solve(input, 2020))
  println(solve(input, 30000000))
}

