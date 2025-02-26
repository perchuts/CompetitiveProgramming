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

void solve(){
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) { 
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v);
        g[v].pb(u);
    }
    string s; cin >> s;
    string ans(n, 'Z');
    vector<int> deg(n), vis(n);
    queue<int> q;
    for (int i = 0; i < n; ++i) deg[i] = sz(g[i]);
    for (int i = 0; i < n; ++i) if (deg[i] == 1) {
        q.push(i), vis[i] = 1;
        ans[i] = s[g[i][0]];
        if (ans[g[i][0]] == 'Z') ans[g[i][0]] = s[i];
        else if (ans[g[i][0]] != s[i]) {
            cout << -1 << endl;
            return;
        }
    }
    while (!q.empty()) {
        int u = q.front(), p = -1; q.pop();
        int score = 0;
        for (auto v : g[u]) {
            if (!vis[v]) {
                deg[v]--;
                if (deg[v] == 1) q.push(v), vis[v] = 1;
                if (p == -1) p = v;
                else assert(false);
            } else {
                if (ans[v] == 'Z') ans[v] = s[u];
                score += (ans[v] == 'B' ? 1 : -1);
            }
        }
        if (score == 0 and p != -1) ans[p] = s[u];
    }
    for (int i = 0; i < n; ++i) assert(ans[i] != 'Z');
    for (int i = 0; i < n; ++i) {
        int score = 0;
        for (auto v : g[i]) {
            score += (ans[v] == 'B' ? 1 : -1);
        }
        if ((score < 0 and s[i] == 'B') or (score > 0 and s[i] == 'W')) {
            cout << -1 << endl;
            return;
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
