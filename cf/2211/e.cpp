#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
int n;
vector<int> solve(vector<ll> a, vector<vector<int>> g) {
#ifndef gato
	cin >> n;
#endif
    //int n; cin >> n;
    // 1 indexed
    //vector<vector<int>> g(n+1);
    vector<int> par(n+1), ans(n+1), subt(n+1);
    vector<vector<pair<int, ll>>> up(n+1, vector<pair<int, ll>>(20));
    vector<vector<pair<ll, int>>> tr(n+1);
    vector layers(n+1, vector<vector<int>>(20));
#ifndef gato
	a.resize(n+1);
	g.resize(n+1);
#endif
    // where is this shit from

    for (int i = n; i >= 1; --i) {
        ans[i] = subt[i] = 1;
		int k;
#ifndef gato
        cin >> a[i] >> k;
		g[i].resize(k);
        for (auto& x : g[i]) cin >> x, ans[i] += ans[x], subt[i] += subt[x];
#else
		k = sz(g[i]);
        for (auto x : g[i]) ans[i] += ans[x], subt[i] += subt[x];
#endif
        if (k == 0) {
            cout << 1 << endl;
            tr[i] = { {a[i], i} };
            continue;
        }
        sort(all(g[i]), [&] (int x, int y) { return subt[x] > subt[y]; });
        // update lca down
        for (auto v : g[i]) {
            up[v][0] = {i, gcd(a[i], a[v])};
            layers[i][0].pb(v);
        }
        for (int j = 1; j < 20; ++j) {
            for (auto v : layers[i][j-1]) {
                for (auto w : layers[v][j-1]) {
                    layers[i][j].pb(w);
                    up[w][j] = {i, gcd(up[v][j-1].second, up[w][j-1].second)};
                }
            }
        }
        auto query = [&] (int u) {
            ll gg = 0;
            for (int j = 19; ~j; --j) {
                if (up[u][j].first) gg = gcd(gg, up[u][j].second), u = up[u][j].first;
            }
            assert(u == i);
            return gg;
        };
        swap(tr[i], tr[g[i][0]]);
        bool ok = 0;
        while (!tr[i].empty()) {
            auto [gg, z] = tr[i].back();
            gg = gcd(gg, a[i]);
            gg = gcd(gg, query(z));
            if (gg != 1) { tr[i].back() = {gg, i}, ok = 1; break; }
            else tr[i].pop_back();
        }
        for (auto v : g[i]) {
            for (auto [gg, z] : tr[v]) {
                gg = gcd(gg, query(z));
                if (gg != 1) tr[i].pb({gg, i}), ok = 1;
            }
        }
        ans[i] -= ok;
		if (ok == 0) {
			tr[i] = {{a[i], i}};
		}
        cout << ans[i] << endl;
    }
    return ans;
}

vector<int> brute(vector<ll> a, vector<vector<int>> g) {
    vector<int> ans(sz(a));
    auto go = [&] (auto&& self, int u, int v, int cur, int cv = 1) -> void {
        if (cur == 1) return;
        int S = 0;
        for (auto w : g[v]) S += ans[w];
        ckmin(ans[u], cv+S);
        for (auto w : g[v]) {
            self(self, u, w, gcd(cur, a[w]), cv+S-ans[w]);
        }
    };
    auto dfs = [&] (auto&& self, int u) -> void {
        for (auto v : g[u]) self(self, v);
        ans[u] = n;
        go(go, u, u, a[u]);
    };
    dfs(dfs, 1);
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve({}, {});
#else
    int t = 1;
    while (true) {
        n = rnd(2, 20);
        vector<vector<int>> g(n+1);
        vector<ll> a(n+1);
        for (int i = 1; i <= n; ++i) a[i] = rnd(2, 700);
        for (int i = 2; i <= n; ++i) {
            int p = rnd(1, i-1);
            g[p].pb(i);
        }
        vector<int> my = solve(a, g);
        vector<int> ans = brute(a, g);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (int i = n; i >= 1; --i) {
                cout << a[i] << " ";
                cout << sz(g[i]) << " ";
                for (auto x : g[i]) cout << x << " ";
                cout << endl;
            }
            cout << "Solve: ";
            for (auto x : my) cout << x << " "; 
            cout << endl;
            cout << "Brute: ";
            for (auto x : ans) cout << x << " "; 
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
