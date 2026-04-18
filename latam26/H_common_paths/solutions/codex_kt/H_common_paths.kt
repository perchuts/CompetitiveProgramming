import java.io.BufferedInputStream
import java.util.Arrays

private const val MOD = 998244353
private const val ROOT = 3
private const val MAX_LOG = 20
private const val INV2 = (MOD + 1) / 2

private lateinit var head: IntArray
private lateinit var to: IntArray
private lateinit var next: IntArray
private var edgePtr = 0

private var n = 0

private lateinit var tk: IntArray
private lateinit var subt: IntArray
private lateinit var dep: IntArray
private lateinit var szt: IntArray
private lateinit var par0: IntArray
private lateinit var compPar: IntArray
private lateinit var seen: IntArray

private lateinit var stackNode: IntArray
private lateinit var stackPar: IntArray
private lateinit var stackDepth: IntArray
private lateinit var order: IntArray

private var stamp = 1

private val roots = IntArray(MAX_LOG + 1)
private val invRoots = IntArray(MAX_LOG + 1)

private class FastScanner {
    private val input = BufferedInputStream(System.`in`)
    private val buffer = ByteArray(1 shl 16)
    private var len = 0
    private var ptr = 0

    private fun readByte(): Int {
        if (ptr >= len) {
            len = input.read(buffer)
            ptr = 0
            if (len <= 0) return -1
        }
        return buffer[ptr++].toInt()
    }

    fun nextInt(): Int {
        var c = readByte()
        while (c <= 32) c = readByte()
        var x = 0
        while (c > 32) {
            x = x * 10 + (c - '0'.code)
            c = readByte()
        }
        return x
    }
}

private class Poly(var a: IntArray = IntArray(0), var size: Int = 0) {
    fun ensureSize(need: Int) {
        if (need > a.size) {
            var cap = if (a.isEmpty()) 1 else a.size
            while (cap < need) cap = cap shl 1
            a = a.copyOf(cap)
        }
        if (need > size) {
            Arrays.fill(a, size, need, 0)
            size = need
        }
    }
}

private fun addMod(x: Int, y: Int): Int {
    var z = x + y
    if (z >= MOD) z -= MOD
    return z
}

private fun subMod(x: Int, y: Int): Int {
    var z = x - y
    if (z < 0) z += MOD
    return z
}

private fun mulMod(x: Int, y: Int): Int = ((x.toLong() * y.toLong()) % MOD).toInt()

private fun powMod(a0: Int, e0: Int): Int {
    var a = a0
    var e = e0
    var r = 1
    while (e > 0) {
        if ((e and 1) != 0) r = mulMod(r, a)
        a = mulMod(a, a)
        e = e ushr 1
    }
    return r
}

private fun initRoots() {
    var level = 1
    while (level <= MAX_LOG) {
        val len = 1 shl level
        roots[level] = powMod(ROOT, (MOD - 1) / len)
        invRoots[level] = powMod(roots[level], MOD - 2)
        level++
    }
}

private fun ntt(a: IntArray, invert: Boolean) {
    val n = a.size

    var i = 1
    var j = 0
    while (i < n) {
        var bit = n ushr 1
        while ((j and bit) != 0) {
            j = j xor bit
            bit = bit ushr 1
        }
        j = j xor bit
        if (i < j) {
            val tmp = a[i]
            a[i] = a[j]
            a[j] = tmp
        }
        i++
    }

    var len = 2
    var level = 1
    while (len <= n) {
        val wlen = if (invert) invRoots[level] else roots[level]
        val half = len ushr 1
        var start = 0
        while (start < n) {
            var w = 1
            var l = start
            var r = start + half
            val limit = start + half
            while (l < limit) {
                val u = a[l]
                val v = mulMod(a[r], w)
                a[l] = addMod(u, v)
                a[r] = subMod(u, v)
                w = mulMod(w, wlen)
                l++
                r++
            }
            start += len
        }
        len = len shl 1
        level++
    }

    if (invert) {
        val invN = powMod(n, MOD - 2)
        var k = 0
        while (k < n) {
            a[k] = mulMod(a[k], invN)
            k++
        }
    }
}

private fun multiply(a: Poly, b: Poly): Poly {
    val res = Poly()
    if (a.size == 0 || b.size == 0) return res

    val need = a.size + b.size - 1
    var nttN = 1
    while (nttN < need) nttN = nttN shl 1

    val fa = IntArray(nttN)
    val fb = IntArray(nttN)
    System.arraycopy(a.a, 0, fa, 0, a.size)
    System.arraycopy(b.a, 0, fb, 0, b.size)

    ntt(fa, false)
    ntt(fb, false)
    var i = 0
    while (i < nttN) {
        fa[i] = mulMod(fa[i], fb[i])
        i++
    }
    ntt(fa, true)

    res.ensureSize(need)
    System.arraycopy(fa, 0, res.a, 0, need)
    return res
}

private fun addPoly(p: Poly, q: Poly) {
    if (p.size < q.size) p.ensureSize(q.size)
    var i = 0
    while (i < q.size) {
        p.a[i] = addMod(p.a[i], q.a[i])
        i++
    }
}

private fun subPoly(p: Poly, q: Poly) {
    if (p.size < q.size) p.ensureSize(q.size)
    var i = 0
    while (i < q.size) {
        p.a[i] = subMod(p.a[i], q.a[i])
        i++
    }
}

private fun scalePoly(p: Poly, c: Int) {
    var i = 0
    while (i < p.size) {
        p.a[i] = mulMod(p.a[i], c)
        i++
    }
}

private fun addEdge(u: Int, v: Int) {
    to[edgePtr] = v
    next[edgePtr] = head[u]
    head[u] = edgePtr
    edgePtr++
}

private fun getDirectedSubtreeSize(x: Int, y: Int): Int {
    return if (dep[x] < dep[y]) n - subt[y] else subt[x]
}

private fun precalc() {
    var top = 0
    var ord = 0

    stackNode[top++] = 0
    par0[0] = -1
    dep[0] = 0

    while (top > 0) {
        val u = stackNode[--top]
        order[ord++] = u

        var e = head[u]
        while (e != -1) {
            val v = to[e]
            if (v != par0[u]) {
                par0[v] = u
                dep[v] = dep[u] + 1
                stackNode[top++] = v
            }
            e = next[e]
        }
    }

    var i = ord - 1
    while (i >= 0) {
        val u = order[i]
        var s = 1
        var e = head[u]
        while (e != -1) {
            val v = to[e]
            if (par0[v] == u) s += subt[v]
            e = next[e]
        }
        subt[u] = s
        i--
    }
}

private fun processSubtree(start: Int, root: Int, pol: Poly) {
    var top = 0
    stackNode[top] = start
    stackPar[top] = root
    stackDepth[top] = 1
    top++

    while (top > 0) {
        top--
        val u = stackNode[top]
        val p = stackPar[top]
        val d = stackDepth[top]

        var tot = 0
        var acum = 1

        var e = head[u]
        while (e != -1) {
            val v = to[e]
            if (v != p) {
                val dir = getDirectedSubtreeSize(v, u)
                tot = addMod(tot, mulMod(dir, acum))
                acum = addMod(acum, dir)
                if (tk[v] == 0) {
                    stackNode[top] = v
                    stackPar[top] = u
                    stackDepth[top] = d + 1
                    top++
                }
            }
            e = next[e]
        }

        tot = mulMod(tot, 2)
        tot = addMod(tot, 1)

        if (pol.size < d + 1) pol.ensureSize(d + 1)
        pol.a[d] = addMod(pol.a[d], tot)
    }
}

private fun processRoot(rt: Int): Poly {
    var k = 0
    var e = head[rt]
    while (e != -1) {
        k++
        e = next[e]
    }

    val pols = Array(k) { Poly() }
    val sizes = IntArray(k)

    var idx = 0
    e = head[rt]
    while (e != -1) {
        val x = to[e]
        sizes[idx] = getDirectedSubtreeSize(x, rt)
        if (tk[x] == 0) processSubtree(x, rt, pols[idx])
        idx++
        e = next[e]
    }

    val sum2 = Poly()
    val sumSq = Poly()

    var i = 0
    while (i < k) {
        val sq = multiply(pols[i], pols[i])
        addPoly(sum2, pols[i])
        addPoly(sumSq, sq)
        i++
    }

    val ans = multiply(sum2, sum2)
    subPoly(ans, sumSq)
    scalePoly(ans, INV2)

    var sumSizes = 0
    var sumSqSizes = 0
    i = 0
    while (i < k) {
        sumSizes = addMod(sumSizes, sizes[i])
        sumSqSizes = addMod(sumSqSizes, mulMod(sizes[i], sizes[i]))
        i++
    }

    i = 0
    while (i < k) {
        var tot = ((2L * (n - sizes[i] - 1)) % MOD).toInt()
        tot = addMod(tot, 1)
        val other = subMod(sumSizes, sizes[i])
        val other2 = subMod(sumSqSizes, mulMod(sizes[i], sizes[i]))
        tot = addMod(tot, subMod(mulMod(other, other), other2))

        scalePoly(pols[i], tot)
        addPoly(ans, pols[i])
        i++
    }

    return ans
}

private fun buildComponent(entry: Int): Int {
    stamp++
    if (stamp == Int.MAX_VALUE) {
        Arrays.fill(seen, 0)
        stamp = 1
    }

    var top = 0
    var ord = 0

    stackNode[top++] = entry
    compPar[entry] = -1
    seen[entry] = stamp

    while (top > 0) {
        val u = stackNode[--top]
        order[ord++] = u

        var e = head[u]
        while (e != -1) {
            val v = to[e]
            if (tk[v] == 0 && v != compPar[u] && seen[v] != stamp) {
                seen[v] = stamp
                compPar[v] = u
                stackNode[top++] = v
            }
            e = next[e]
        }
    }

    var i = ord - 1
    while (i >= 0) {
        val u = order[i]
        var s = 1
        var e = head[u]
        while (e != -1) {
            val v = to[e]
            if (seen[v] == stamp && compPar[v] == u) s += szt[v]
            e = next[e]
        }
        szt[u] = s
        i--
    }

    return ord
}

private fun findCentroid(compSize: Int): Int {
    var i = 0
    while (i < compSize) {
        val u = order[i]
        var maxPart = compSize - szt[u]

        var e = head[u]
        while (e != -1) {
            val v = to[e]
            if (seen[v] == stamp && compPar[v] == u && szt[v] > maxPart) {
                maxPart = szt[v]
            }
            e = next[e]
        }

        if (maxPart * 2 <= compSize) return u
        i++
    }
    return order[0]
}

private fun centroidDfs(entry: Int): Poly {
    val compSize = buildComponent(entry)
    val c = findCentroid(compSize)
    tk[c] = 1

    val ans = processRoot(c)

    var e = head[c]
    while (e != -1) {
        val v = to[e]
        if (tk[v] == 0) {
            val cur = centroidDfs(v)
            addPoly(ans, cur)
        }
        e = next[e]
    }

    return ans
}

fun main() {
    val fs = FastScanner()
    n = fs.nextInt()
    val m = n - 1

    head = IntArray(n) { -1 }
    to = IntArray(2 * m)
    next = IntArray(2 * m)

    repeat(m) {
        val u = fs.nextInt() - 1
        val v = fs.nextInt() - 1
        addEdge(u, v)
        addEdge(v, u)
    }

    tk = IntArray(n)
    subt = IntArray(n)
    dep = IntArray(n)
    szt = IntArray(n)
    par0 = IntArray(n)
    compPar = IntArray(n)
    seen = IntArray(n)

    stackNode = IntArray(n)
    stackPar = IntArray(n)
    stackDepth = IntArray(n)
    order = IntArray(n)

    initRoots()
    precalc()

    val ans = centroidDfs(0)
    if (ans.size < n) ans.ensureSize(n)

    val out = StringBuilder()
    var i = 1
    while (i < n) {
        if (i > 1) out.append(' ')
        out.append(ans.a[i])
        i++
    }
    out.append('\n')
    print(out.toString())
}
