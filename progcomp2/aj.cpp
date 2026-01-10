#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

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

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> g(k+1);
    vector<ii> cc(k);
    vector<int> deg(k+1);
    for (auto& [x, y] : cc) cin >> x >> y;
    k++;
    cc.pb({1, 1});
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            auto [x1, y1] = cc[i];
            auto [x2, y2] = cc[j];
            if (i != j and x1 <= x2 and y1 <= y2) g[j].pb(i), deg[i]++;
        }
    }
    int N = n+m+50;
    vector<int> fat(N, 1), ifat(N);
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    for (int i = 1; i < N; ++i) fat[i] = i * fat[i-1] % mod;
    ifat.back() = fexp(fat.back(), mod-2);
    for (int i = N-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    auto ncr = [&] (int a, int b) {
        if (min(a, b) < 0 or b > a) return 0LL;
        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
    };
    queue<int> q;
    for (int i = 0; i < k; ++i) if (deg[i] == 0) q.push(i);
    vector<int> dp(k);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        auto [x, y] = cc[u];
        dp[u] = (dp[u] + ncr(n-x+m-y, n-x)) % mod;
        for (auto v : g[u]) {
            deg[v]--;
            auto [x2, y2] = cc[v];
            int ways = ncr(x-x2+y-y2, x-x2) * dp[u] % mod;
            dp[v] = (dp[v] + mod - ways) % mod;
            if (deg[v] == 0) q.push(v);
        }
    }
    cout << dp.back() << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
