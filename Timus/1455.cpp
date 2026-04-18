#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

bool checker(int n, vector<string> ss, string ans) {
    int N = sz(ans);
    vector<int> dp(N+1);
    dp[0] = 1;
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < n; ++j) {
            int m = sz(ss[j]);
            if (i + m - 1 > N) continue;
            bool ok = 1;
            for (int k = 0; k < m; ++k) ok &= (ss[j][k] == ans[i+k-1]);
            if (ok) dp[i+m-1] += dp[i-1];
        }
    }
    for (auto x : dp) cout << x << " ";
    cout << endl;
    return (dp[N] > 1);
}

void solve() {
    int n; cin >> n;
    vector<string> s(n);
    for (auto& x : s) cin >> x;
    vector<vector<ii>> g;
    int N = 0;
    vector<vector<int>> id(n);
    vector<ii> inv;
    for (int i = 0; i < n; ++i) {
        id[i].resize(sz(s[i]));
        for (int j = 0; j < sz(s[i]); ++j) id[i][j] = N++, inv.pb({i, j});
    }
    g.resize(N+2);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < sz(s[i]); ++j) {
            for (int add = 0; add < n; ++add) {
                if (j == 0 and add == i) continue;
                bool ok = 1;
                int p1 = j, p2 = 0;
                while (p1 < sz(s[i]) and p2 < sz(s[add])) {
                    ok &= s[i][p1] == s[add][p2];
                    if (!ok) break;
                    ++p1, ++p2;
                }
                if (!ok) continue;
                // ele faz o W infinito
                if (p1 == sz(s[i]) and p2 == sz(s[add])) g[id[i][j]].pb({N, add});
                else if (p1 == sz(s[i])) g[id[i][j]].pb({id[add][p2], add});
                else g[id[i][j]].pb({id[i][p1], add});
            }
        }
    }
    for (int i = 0; i < n; ++i) g[N+1].pb({id[i][0], i});
    vector<int> vis(N+2);
    vector<ii> pai(N+1);
    queue<int> q;
    q.push(N+1), vis[N+1] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto [v, w] : g[u]) {
            if (!vis[v]) q.push(v), vis[v] = 1, pai[v] = {u, w};
        }
    }
    if (!vis[N]) {
        cout << "NO" << endl;
        exit(0);
    }
    cout << "YES" << endl;
    vector<int> ss;
    string ans;
    int cur = N;
    while (cur != N+1) {
        auto [nxt, word] = pai[cur];
        ss.pb(word);
        cur = nxt;
    }
    reverse(all(ss));
    string s1, s2;
    for (auto i : ss) {
        if (sz(s1) > sz(s2)) swap(s1, s2);
        s1 += s[i];
    }
    cout << s1 << endl;
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
