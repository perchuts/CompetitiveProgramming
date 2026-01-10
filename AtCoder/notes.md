# Some problem notes
Just leaving notes on some problems. There are problems in which i find the solution beautiful, or my solution is completely different from editorial's. I just want to register such things here.

<details>
<summary> [ARC156C](https://atcoder.jp/contests/arc156/tasks/arc156_c) </summary>
Thought of a construction using the centroid of the tree. It pairs nodes from different subtrees (p[x] = y, p[y] = x) and nodes with lower height are paired first.). Edi solution is kinda trivial, much easier than mine, but I thought that this construction and its proof are cute.
</details>

<details>
<summary> [ABC366G](https://atcoder.jp/contests/abc366/tasks/abc366_g) </summary>
Interesting XOR Basis problem! Although constraints make it not too hard to come up with the solution
</details>

<details>
<summary> [ABC346G](https://atcoder.jp/contests/abc346/tasks/abc346_g) </summary>
Solved using Divide and Conquer + ordered set. Works in O(n log^2 n), but runs kinda fast (~600ms)
</details>

<details>
<summary> [ARC202B](https://atcoder.jp/contests/arc202/tasks/arc202_b) </summary>
My solution also splits into two cases, but my observations were very different. Just like the editorial, trivially `n` even does not work, and we can rearrange rows to have our steps be (-1, 1) or (-1, -1).

For a fixed tour, define an `N × M` matrix called `step`, where `step[i][j] ∈ {1, -1}` is the direction we choose to go when, in our tour, we are at position `(i, j)`.

First, fix some row `i`. Claim that `step[i][j] = step[i][k]` for all `j ≡ k (mod 2)`. If this is not the case, we can find an index `a` such that `step[i][a] = 1` and `step[i][a+2] = -1`, which contradicts the fact that we had a tour.

Therefore, we only need to decide `step[i][0]` and `step[i][1]` for each row `i`. However, this does not prevent every shorter cycle: we can still have a cycle ending at `(0, 0)`. For a cycle to happen at `(0, 0)`, the second time we visit zero must occur at `K·N` steps, for some `1 ≤ K < M`. At this point, it is necessary to split into two cases.

Case 1: `M` is even. Notice that row-wise we have a checkered pattern (considering cyclic neighborhood), so `K` must be even. Since `N` is odd, for each `2N` consecutive steps we visit an even and an odd position from each row. Thus the only thing that matters is `S = ∑ (step[i][0] + step[i][1])`, and we must require that `S, 2S, …, (M/2-1)·S` are not multiples of `M` (\*). For a single row, the sum can be `-2`, `0`, or `2`. For `-2` and `2` there is only one way, namely `step[i][0] = step[i][1] = ±1`. For `0`, we have two possibilities. We model this counting problem with a generating function: for every `S` satisfying (\*), we want the coefficient `[x^S] (x^(-2) + 2 + x^2)^N`. Let `P(x) = (x^(-2) + 2 + x^2)^N`. We can compute `P(x)` with a single NTT in `O(N log N)`, and then iterate over all valid `S`.

Case 2: `M` is odd. In this case, it turns out that `step[i][j] = step[i][k]` for all `j, k`, in order to avoid a cycle ending at any position other than `(0, 0)`. To prevent a cycle at `(0, 0)`, we must have `S = ∑ step[i][0]` such that `S, 2S, 3S, …, (M−1)S` are not multiples of `M`. This means that after `N, 2N, …, (M−1)N` steps we return to row zero but cannot be at column zero. Equivalently, `gcd(M, S) = 1`, and the contribution to the answer is a binomial coefficient.
</details>


