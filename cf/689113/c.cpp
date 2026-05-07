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
    string s, t; cin >> s >> t;
    int n = sz(s), m = sz(t);
    vector<int> w(n);
    for (auto& x : w) cin >> x;
    string S = t + "#";
    // need to m + n + m - 1 <= 
    while (sz(S) < 2*(m + n + m) + 5) S += s;
    vector<int> pi(sz(S));
    for (int i = 1, j = 0; i < sz(S); ++i) {
        while (j and S[i] != S[j]) j = pi[j-1];
        if (S[i] == S[j]) j++;
        pi[i] = j;
    }
    vector<int> seta(n, -1);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        if (pi[sz(S)-2*n+i] == m) {
            int st = (i-m+1)%n;
            st = (st+n)%n;
            seta[st] = (i + 1) % n, g[st].pb(seta[st]), g[seta[st]].pb(st);
            if (seta[st] == st) {
                cout << -1 << endl;
                return;
            }
        }
        else seta[i] = -1;
    }
    int ans = 0;
    vector<int> vis(n);
    int cnt = 0, tot = 0, te = 0;
    auto dfs = [&] (auto&& self, int u) -> void {
        vis[u] = 1;
        cnt++;
        if (seta[u] != -1) {
            tot += w[u];
        }
        for (auto v : g[u]) {
            if (u <= v) te++;
            if (!vis[v]) self(self, v);
        }
    };
    for (int i = 0; i < n; ++i) {
        if (seta[i] == -1 or vis[i]) continue;
        cnt = tot = te = 0;
        dfs(dfs, i);
        if (te == cnt) {
            cout << -1 << endl;
            return;
        }
        ckmax(ans, tot);
    }
    cout << ans << endl;
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
