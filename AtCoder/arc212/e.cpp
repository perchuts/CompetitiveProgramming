#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int brute(int n, vector<int> p) {
    // if pi is max amongst its neighbors, we are done!
    // 4 2 1 3
    // 4 1 2 3
    // 4 2 1 3
    //
    for (auto& x : p) x++;
    vector<int> pp(n+2);
    for (int i = 1; i <= n; ++i) pp[i] = p[i-1];

    vector dp(n+2, vector(n+2, 0LL)), ncr = dp;
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= i; ++j) {
        if (i == j or j == 0) ncr[i][j] = 1;
        else ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % mod;
    }
    for (int i = 0; i <= n; ++i) {
        if (i <= n) dp[i][i+1] = 1;
    }
    auto get = [&] (int a, int b) {
        if (min(a, b) < 0) return 1LL;
        return ncr[a][b];
    };
    // dp[l][r] where 1 <= l < r <= n
    // so preciso saber o valor de dp[0][onde[N]], dp[onde[N]][n+1]
    // T(L, R) = .
    for (int l = n+1; ~l; --l) {
        for (int r = l+2; r <= n+1; ++r) {
            for (int k = l+1; k < r; ++k) {
                    if (pp[k] < max(pp[l], pp[r])) {
                    int ways = dp[l][k] * dp[k][r] % mod * get(r-l-2, k-l-1) % mod;
                    dp[l][r] = (dp[l][r] + ways) % mod;
                }
            }
        }
    }
    int l = 0, r = n+1;
    for (int k = 1; k <= n; ++k) {
        if (pp[k] == n) {
            int ways = dp[l][k] * dp[k][r] % mod * get(r-l-2, k-l-1) % mod;
			return ways;
        }
    }
	return -1;
}

int solve(int n, vector<int> p) {
    vector<int> fat(n+1, 1), ifat(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    ifat[n] = fexp(fat[n], mod-2);
    for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    auto get = [&] (int a, int b) {
        if (min(a, b) < 0) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    vector<int> lg(n+1);
    for (int i = 2; i <= n; ++i) lg[i] = lg[i/2]+1;
    vector<vector<int>> mn(18, vector<int>(n));
    mn[0] = p;
    for (int i = 1; i < 18; ++i) {
        for (int j = 0; j + (1 << i) <= n; ++j) {
            mn[i][j] = max(mn[i-1][j], mn[i-1][j+(1<<(i-1))]);
        }
    }
    auto query = [&] (int l, int r) {
        if (l == r) return p[l];
        int tam = lg[r-l+1];
        return max(mn[tam][l], mn[tam][r-(1<<tam)+1]);
    };
    vector<int> onde(n);
    for (int i = 0; i < n; ++i) onde[p[i]] = i;
    auto rec = [&] (auto&& self, int l, int r, bool pode_esq = 0, bool pode_dir = 0) -> int {
        if (l >= r) return 1LL;
        int pos_mx = onde[query(l, r)];
        int wl = self(self, l, pos_mx-1, 1, pode_dir);
        int wr = self(self, pos_mx+1, r, pode_esq, 1);
        int ways = wl * wr % mod * get(r-l, pos_mx-l) % mod;
        if (pos_mx == onde[n-1]) return ways;
        // agora, podemos decidir se queremos a esquerda ou a direita na nossa frente,
        if (pode_esq) ways = (ways + wl * wr % mod * get(r-l, pos_mx-l-1)) % mod;
        if (pode_dir) ways = (ways + wl * wr % mod * get(r-l, r-pos_mx-1)) % mod;
        //cout << "l = " << l << " r = " << r << " ways = " << ways << " pos_mx = " << pos_mx << endl;
        return ways; 
    };
	return rec(rec, 0, n-1);
}

int32_t main() {_
#ifndef gato
    int n; cin >> n;
    vector<int> p(n);
    for (auto& x : p) cin >> x, --x;
	cout << solve(n, p) << endl;
#else
    int t = 1;
    while (true) {
		int n = rnd(2, 5);
		vector<int> p(n); iota(all(p), 0);
		shuffle(all(p), rng);
        int my = solve(n, p), ans = brute(n, p);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
			cout << n << endl;
			for (auto x : p) cout << x + 1 << " ";
			cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
