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

void solve() {
    int n; cin >> n;
    vector<int> val(n);
    for (auto& x : val) cin >> x;
    vector<int> ord(n), inv(n), tour(n); iota(all(ord), 0); sort(all(ord), [&] (int x, int y) { return val[x] < val[y]; });
    for (int i = 0; i < n; ++i) inv[ord[i]] = i;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> in(n), out(n); int t = 0;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        tour[t] = u;
        in[u] = t++;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
        out[u] = t-1;
    };
    dfs(dfs, 0, 0);
    int q; cin >> q;
    vector<array<int, 4>> qry(q);
    vector<int> seg(4*n);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            seg[i] = k;
            return;
        }
        int md = (l+r) / 2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = seg[2*i] + seg[2*i+1];
    };
    auto query = [&] (auto&& self, int i, int l, int r, int k) -> int {
        if (l == r) return ord[l];
        int md = (l+r) / 2;
        if (k <= seg[2*i]) return self(self, 2*i, l, md, k);
        return self(self, 2*i+1, md+1, r, k-seg[2*i]);
    };
    vector<int> ans(q);
    auto solve = [&] (auto&& self, int l, int r, vector<int> ids) -> void {
        // quero olhar pras perguntas que comecam em um lado e terminam em outro lado
        if (l > r) return;
        vector<int> esq, dir, mid;
        int md = (l+r)/2;
        for (auto i : ids) {
            if (qry[i][1] < md) esq.pb(i);
            else if (md < qry[i][0]) dir.pb(i);
            else mid.pb(i);
        }
        int pL = md, pR = md;
        reverse(all(mid));
        for (auto i : mid) {
            int lx = qry[i][0], rx = qry[i][1], k = qry[i][2];
            //cout << "answering query i = " << i << ": lx = " << lx << " rx = " << rx << " k = " << k << " pL = " << pL << " pR = " << pR << endl;
            while (lx <= pL) upd(upd, 1, 0, n-1, inv[tour[pL--]], 1);
            while (pR < rx) upd(upd, 1, 0, n-1, inv[tour[++pR]], 1);
            ans[i] = query(query, 1, 0, n-1, k);
        }
        for (int j = pL+1; j <= pR; ++j) upd(upd, 1, 0, n-1, inv[tour[j]], 0);
        self(self, l, md-1, esq);
        self(self, md+1, r, dir);
    };
    //for (int i = 0; i < n; ++i) //cout << in[i] << ' ' << out[i] << endl;
    for (int i = 0; i < q; ++i) {
        int u, k; cin >> u >> k; --u;
        qry[i] = {in[u], out[u], k};
    }
    vector<int> ids(q); iota(all(ids), 0); sort(all(ids), [&] (int x, int y) { return qry[x][0] < qry[y][0]; });
    solve(solve, 0, n-1, ids);
    for (auto x : ans) cout << x+1 << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
