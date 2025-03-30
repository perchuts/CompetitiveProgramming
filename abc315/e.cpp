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
    vector<vector<int>> g(n), gi(n);
    for (int i = 0; i < n; ++i) {
        int c; cin >> c;
        for (int j = 0; j < c; ++j) {
            int x; cin >> x;
            --x;
            g[i].pb(x);
            gi[x].pb(i);
        }
    }
    vector<int> mark(n);
    auto dfs = [&] (auto&& self, int u) -> void {
        mark[u] = 1;
        for (auto v : g[u]) {
            if (!mark[v]) self(self, v);
        }
    };
    dfs(dfs, 0);
    vector<int> ans, deg(n);
    for (int i = 0; i < n; ++i) {
        if (mark[i]) {
            for (auto v : g[i]) {
                if (mark[v]) deg[i]++;
            }
        }
    }
    queue<int> q;
    for (int i = 0; i < n; ++i) if (deg[i] == 0 and mark[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ans.pb(u+1);
        for (auto v : gi[u]) if (mark[v]) {
            deg[v]--;
            if (deg[v] == 0) q.push(v);
        }
    }
    ans.pop_back();
    for (auto x : ans) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
