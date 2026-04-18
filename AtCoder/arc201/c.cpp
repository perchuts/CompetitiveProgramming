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
const int mod = (119<<23)+1;
const int maxn = 2e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int trie[maxn][2], dp[maxn], path[maxn], qt[maxn], pw[maxn];
bool mark[maxn];

void solve() {
    int n; cin >> n;
    int h = 1;
    pw[0] = 1;
    for (int i = 1; i < maxn; ++i) pw[i] = 2 * pw[i-1] % mod;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        int cur = 0, j = 0;
        for (auto c : s) {
            path[j++] = cur;
            int z = c - 'A';
            if (trie[cur][z] == 0) trie[cur][z] = h++;
            cur = trie[cur][z];
        }
        path[j] = cur, mark[cur] = 1;
        for (int k = j; ~k; --k) {
            int u = path[k];
            int v = trie[u][0], w = trie[u][1];
            dp[u] = 0;
            if (v and w) dp[u] = dp[v] * dp[w] % mod;
            qt[u] = 0;
            if (v) qt[u] += qt[v];
            if (w) qt[u] += qt[w];
            if (mark[u]) qt[u]++, dp[u] = (dp[u] + pw[qt[u]-1]) % mod;
        }
        cout << dp[0] << endl;
    }
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
