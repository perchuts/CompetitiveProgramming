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
    int n; cin >> n;
    vector<vector<int>> g(n);
    vector<int> par(n), v(n), pp(n);
    for (int i = 1; i < n; ++i) {
        int x; cin >> x; --x;
        pp[i] = x;
        g[x].pb(i), g[i].pb(x);
    }
    for (auto& x : v) cin >> x;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        par[u] = u;
        if (u != p and v[u] == 0 and v[p] == 0) par[u] = par[p];
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
    };
    dfs(dfs, 0, 0);
    vector<vector<int>> g2(n);
    vector<int> tam(n);
    for (int i = 0; i < n; ++i) {
        tam[par[i]]++;
        for (auto v : g[i]) {
            g2[par[i]].pb(par[v]);
        }
    }
    vector<int> ans;
    priority_queue<ii, vector<ii>, greater<>> pq;
    vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
        if (par[i] != i) continue;
        sort(all(g2[i]));
        g2[i].erase(unique(all(g2[i])), end(g2[i]));
        deg[i] = sz(g2[i]);
        if (sz(g2[i]) == 1) {
            deg[i] = 0;
            if (v[i] == 1) pq.push({-inf, i});
            else pq.push({tam[i], i});
        }
    }
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (v[u] == 1) {
            ans.pb(1);
        } else {
            for (int j = 0; j < w; ++j) ans.pb(0);
        }
        if (pp[u] != u) {
            deg[pp[u]]--;
            if (deg[pp[u]] == 1 and pp[u]) {
                if (v[pp[u]] == -1) pq.push({-inf, pp[u]});
                else pq.push({tam[pp[u]], pp[u]});
            }
        }
    }
    ans.pb(v[0]);
    reverse(all(ans));
    int cnt1 = 0, inv = 0;
    for (int i = 0; i < n; ++i) {
        if (ans[i]) cnt1++;
        else inv += cnt1;
    }
    cout << inv << endl;
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
