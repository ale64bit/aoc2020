fun main() {
    val ranges = mutableListOf<IntRange>()
    var line = readLine()!!
    while (line.isNotEmpty()) {
        for (s in line.split(":")[1].split("or")) {
            val lim = s.trim().split("-")
            ranges.add(lim[0].toInt()..lim[1].toInt())
        }
        line = readLine()!!
    }

    while (line != "your ticket:") line = readLine()!!
    /* val t = */ readLine()!!.split(",").map { it.toInt() }

    var ans = 0
    while (line != "nearby tickets:") line = readLine()!!
    line = readLine() ?: ""
    while (line.isNotEmpty()) {
        ans += line.split(",").map { it.toInt() }.filter { x -> ranges.all { x !in it } }.sum()
        line = readLine() ?: ""
    }
    println(ans)
}
