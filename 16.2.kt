fun main() {
    data class Field(val name: String, val ranges: List<IntRange>)

    val fields = mutableListOf<Field>()
    var line = readLine()!!
    while (line.isNotEmpty()) {
        val ranges = mutableListOf<IntRange>()
        val kv = line.split(":")
        for (s in kv[1].split("or")) {
            val lim = s.trim().split("-")
            ranges.add(lim[0].toInt()..lim[1].toInt())
        }
        fields.add(Field(kv[0].trim(), ranges))
        line = readLine()!!
    }

    while (line != "your ticket:") line = readLine()!!
    val own = readLine()!!.split(",").map { it.toInt() }

    val tickets = mutableListOf(own)
    while (line != "nearby tickets:") line = readLine()!!
    line = readLine() ?: ""
    while (line.isNotEmpty()) {
        val t = line.split(",").map { it.toInt() }
        if (t.all { x -> fields.any { f -> f.ranges.any { x in it } } }) {
            tickets.add(t)
        }
        line = readLine() ?: ""
    }

    val n = fields.size*2+2
    val src = 0
    val sink = n-1
    val flow = Array(n) { Array(n) {false} }
    for (i in 1..fields.size) {
        flow[src][i] = true
        flow[i + fields.size][sink] = true
    }
    for (i in 1..fields.size) {
        for (j in 1..fields.size) {
            flow[i][j+fields.size] = tickets.all { t -> fields[i-1].ranges.any { t[j-1] in it} }
        }
    }

    val used = BooleanArray(n)
    fun find(u: Int): Boolean {
        used[u] = true
        if (u == sink) return true
        for (v in 0 until n) {
            if (!used[v] && flow[u][v] && find(v)) {
                flow[u][v] = false
                flow[v][u] = true
                return true
            }
        }
        return false
    }

    while (find(src)) {
        used.fill(false)
    }

    val index = IntArray(fields.size)
    for (i in 1..fields.size) {
        for (j in 1..fields.size) {
            if (flow[j+fields.size][i]) {
                index[i-1] = j-1
                break
            }
        }
    }

    var ans: Long = 1
    for ((i, f) in fields.withIndex()) {
         if (f.name.startsWith("departure")) {
            ans *= own[index[i]]
         }
    }
    println(ans)
}
