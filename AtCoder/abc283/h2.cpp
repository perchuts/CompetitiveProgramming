#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int solve(int n, int m, int r) {
    if (r > n) return 0;
    int lim = (n-r)/m, g = 1, ans = 0;
    int y = 0;
    while ((m >> y & 1) == 0) y++;
    for (int i = 0; i < y; ++i) if (r >> i & 1) ans += lim + 1;
    for (int i = y; i < 30; ++i) {
        int nn = 0;
        for (int j = 29; j > i; --j) {
            if (n >> j & 1) {
                int k = (r - nn - (1 << i)) % m;
                k = (k + m) % m;
                // x1 + (x2 << (i+1)) === k mod m
                // 0 <= x1 < 2^i
                // 0 <= x2 < 2^j-i-1
                // x1 must be equal to k in the last y bits
                // x2 * 2^(i+1) === k - x1 mod m
                // x2 * 2^(i+1-y) === (k-x1) / 2^y mod m/2^y
                // m = 2^y * (2p+1), (k-x1) = 2^y * z
                // x2 * 2^(i+1-y) === z mod (2*p+1) --- how many solutions for this? does it depend on the value of x1?
                for (int x1 = k % (1 << y); x1 < (1<<i); x1 += (1 << y)) {
                    for (int x2 = 0; x2 < (1<<(j-i-1)); x2++) {
                        ans += ((x1 + (x2 << (i+1))) % m == k);
                    }
                }
                nn += (1 << j);
            }
        }
        // mk + r >= 2^i mod 2^(i+1)
        // 2^i-r <= mk < 2^(i+1)-r mod 2^(i+1)
        // varying k, i can achieve all multiples of 2^y!!
        // period of size 2^(i+1-y)
        //
        if (n >> i & 1) {
            nn += (1 << i);
            for (int j = i-1; j >= 0; --j) {
                if (n >> j & 1) {
                    int lx = nn / m, rx = (nn + (1 << j) - 1) / m;
                    if (lx == rx) ans += (nn % m <= r and r <= (nn + (1 << j) - 1) % m);
                    else ans += rx - lx - 1 + (nn % m <= r) + (r <= (nn + (1 << j) - 1) % m);
                    nn += (1 << j);
                }
            }
        }
        if (n % m == r and (n >> i & 1)) ans++;
        // A >= 2^i mod 2^(i+1) <=> (A+2^i)/2^(i+1) - A/2^(i+1) = 1
    }
    return ans;
}

int brute(int n, int m, int r) {
    int ans = 0;
    for (int i = r; i <= n; i += m) ans += __builtin_popcount(i);
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while (t--) {
        int n, m, r; cin >> n >> m >> r;
        cout << solve(n, m, r) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 10000), m = rnd(1, n), r = rnd(0, m-1);
        int my = solve(n, m, r), ans = brute(n, m, r);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << ' ' << r << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
