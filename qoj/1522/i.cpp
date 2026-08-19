#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

bool checker(int n, int m, vector<vector<int>> g, vector<int> a, vector<int> given) {
    auto b = given;
    sort(all(a)), sort(all(b));
    if (a != b) return false;
    int z = a[n-1] - a[0];
    for (int i = 0; i < n; ++i) {
        for (auto j : g[i]) if (i < j) z -= abs(given[i] - given[j]);
    }
    return (z == 0);
}

vector<int> solve(int n, int m, vector<vector<int>> g, vector<int> a) {
    vector<int> dp(n), lvl(n, -1), par(n), mark(n);
    vector<ii> bdg;
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        for (auto v : g[u]) {
            if (lvl[v] == -1) lvl[v] = 1 + lvl[u], self(self, v, u), dp[u] += dp[v];
            else if (lvl[v] > lvl[u]) dp[u]--;
            else dp[u]++;
        }
        par[u] = p;
        if (u != p) dp[u]--;
        if (dp[u] == 0 and u != p) bdg.pb({u, p}), mark[u] = 1;
    };
    lvl[0] = 0;
    dfs(dfs, 0, 0);
    vector<int> tam(n), color(n, -1);
    int h = 0;
    auto dfs2 = [&] (auto&& self, int u) -> void {
        color[u] = h;
        tam[h]++;
        for (auto v : g[u]) {
            if ((mark[v] and par[v] == u) or (mark[u] and par[u] == v) or color[v] != -1) continue;
            self(self, v); 
        }
    };
    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) dfs2(dfs2, i), h++;
    }
    vector<vector<int>> g2(n);

    //cerr << "color: ";
    //for (auto x : color) //cerr << x << " ";
    //cerr << endl;

    //cerr << "g2: " << endl;

    for (int i = 0; i < n; ++i) {
        if (mark[i]) {
            g2[color[i]].pb(color[par[i]]), g2[color[par[i]]].pb(color[i]);
            //cerr << color[i] << " " << color[par[i]] << endl;
        }
    }
	//cerr << "tam: ";
	//for (auto x : tam) cerr << x << " ";
	//cerr << endl;


    vector<int> freq(n);

    for (auto x : a) freq[x-1]++;

    vector<int> non_zero, compressed;

    for (int i = 0; i < n; ++i) if (freq[i]) non_zero.pb(freq[i]), compressed.pb(i+1);

    //cerr << "non_zero: ";
    //for (auto x : non_zero) cerr << x << " ";
    //cerr << endl;
    //cerr << "compressed: ";
    //for (auto x : compressed) cerr << x << " ";
    //cerr << endl;

    vector<int> pos_esq(n+1, -1), pos_dir(n+1, -1);

    int S = 0, t = sz(non_zero);

    if (t == 1) return a;

    for (int i = 0; i < t - 1; ++i) {
        S += non_zero[i];
        pos_esq[S] = i;
    }

    S = 0;

    for (int i = t-1; i; --i) {
        S += non_zero[i];
        pos_dir[S] = i;
    }

    //cerr << "pos_esq: ";
    //for (auto x : pos_esq) cerr << x << " ";
    //cerr << endl;

    //cerr << "pos_dir: ";
    //for (auto x : pos_dir) cerr << x << " ";
    //cerr << endl;

    vector<int> up(n, -inf), down(n, inf), tr_up(n), tr_down(n), subt(n);

    auto dfs3 = [&] (auto&& self, int u, int p) -> void {
		subt[u] = tam[u];
        for (auto v : g2[u]) {
            if (v == p) continue;
            self(self, v, u);
            subt[u] += subt[v];
        }
    };

    dfs3(dfs3, 0, 0);

    auto dfs4 = [&] (auto&& self, int u, int p) -> void {
        int lu = pos_esq[subt[u]], ld = pos_dir[subt[u]];
        if (lu == 0) up[u] = 0, tr_up[u] = u;
        if (ld == t-1) down[u] = t-1, tr_down[u] = u;
        //cerr << "u = " << u << ", lu = " << lu << ", ld = " << ld << endl;
        for (auto v : g2[u]) {
            if (v == p) continue;
            self(self, v, u);

            if (ckmin(down[u], down[v])) tr_down[u] = v;
            if (ld == down[v] - 1 and ckmin(down[u], down[v] - 1)) tr_down[u] = v;


            if (ckmax(up[u], up[v])) tr_up[u] = v;
            if (lu == up[v] + 1 and ckmax(up[u], up[v] + 1)) tr_up[u] = v;
        }
    };

    dfs4(dfs4, 0, 0);

    //cerr << "down: ";
    //for (auto x : down) cerr << x << " ";
    //cerr << endl;

    //cerr << "tr_down: ";
    //for (auto x : tr_down) cerr << x << " ";
    //cerr << endl;

    //cerr << "up: ";
    //for (auto x : up) cerr << x << " ";
    //cerr << endl;

    //cerr << "tr_up: ";
    //for (auto x : tr_up) cerr << x << " ";
    //cerr << endl;

    vector<int> ans(n, -1), path;


    for (int i = 0; i < h and path.empty(); ++i) {
		if (down[i] == 1) { 
			//cerr << "CASO1" << endl;
			int cur = i;
			path.pb(i);
			while (cur != tr_down[cur]) cur = tr_down[cur], path.pb(cur);
			break;
		}
		if (up[i] == t-2) {
			//cerr << "CASO2" << endl;
			int cur = i;
			path.pb(i);
			while (cur != tr_up[cur]) cur = tr_up[cur], path.pb(cur);
			reverse(all(path));
			break;
		}
        for (int z = 0; z < 2 and path.empty(); ++z) {
            vector<int> children, mn, mx, o1, o2;
            for (auto v : g2[i]) {
                if (subt[v] < subt[i]) children.pb(v), mn.pb(down[v]), mx.pb(up[v]);
            }
            o1 = o2 = children;
            for (int j = 1; j < sz(children); ++j) if (ckmax(mx[j], mx[j-1])) o1[j] = o1[j-1];
            for (int j = sz(children)-2; j >= 0; --j) if (ckmin(mn[j], mn[j+1])) o2[j] = o2[j+1];
            for (int j = 0; j < sz(children)-1; ++j) {
                if (mx[j] + 2 != mn[j+1]) continue;
				//cerr << "CASO3" << endl;
				//cerr << "pivot: " << i << endl;
				//cerr << "sides: " << o1[j] << " " << o2[j+1] << endl;
                int cur = o1[j];
                while (tr_up[cur] != cur) path.pb(cur), cur = tr_up[cur];
                path.pb(cur);
                reverse(all(path));
                path.pb(i), cur = o2[j+1];
                while (tr_down[cur] != cur) path.pb(cur), cur = tr_down[cur];
                path.pb(cur);
                break;
            }
            reverse(all(g2[i]));
        }
    }

    if (path.empty()) return {};
    //cerr << "path: ";
    //for (auto x : path) cerr << x << " ";
    //cerr << endl;

    dfs3(dfs3, path[0], path[0]);

    int j = 0, cur = 0;

    for (int i = 0; i < sz(path); ++i) {
        int u = path[i];
		ans[u] = compressed[j];
        cur += tam[u];
        for (auto v : g2[u]) {
            if (i and path[i-1] == v) continue;
            if (i + 1 < sz(path) and path[i+1] == v) continue;
			//cout << "adding subt of " << v+1 << endl;
            cur += subt[v];
        }
		////cerr << cur << " " << j << endl;
        if (cur == non_zero[j]) j++, cur = 0;
    }

    auto dfs5 = [&] (auto&& self, int u, int p) -> void {
        for (auto v : g2[u]) {
            if (v == p) continue;
            if (ans[v] == -1) ans[v] = ans[u];
            self(self, v, u);
        }
    };

    dfs5(dfs5, path[0], path[0]);
    vector<int> resp(n);
    for (int i = 0; i < n; ++i) resp[i] = ans[color[i]];
    //assert(checker(n, m, g, a, resp));
    return resp;
}

vector<int> brute(int n, int m, vector<vector<int>> g, vector<int> a) {
    sort(all(a));
    auto A = a;
    do {
        if (checker(n, m, g, A, a)) return a;
    } while (next_permutation(all(a)));
    return {};
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> g(n);
        vector<int> a(n);
        for (int i = 0; i < m; ++i) {
            int u, v; cin >> u >> v;
            --u, --v;
            g[u].pb(v), g[v].pb(u);
        }
        for (auto& x : a) cin >> x;
        auto ans = solve(n, m, g, a);
        if (ans.empty()) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
            for (auto x : ans) cout << x << " ";
            cout << endl;
        }
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 12), m = 0;
        vector<vector<int>> g(n);
        vector<int> a(n);
        for (auto& x : a) x = rnd(1, n);
        vector<ii> edg;
        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
            if (rnd(0, 3)) m++, edg.pb({i + 1, j + 1}), g[i].pb(j), g[j].pb(i);
        }
        vector<int> vis(n);
        auto dfs = [&] (auto&& self, int u) -> void {
            vis[u] = 1;
            for (auto v : g[u]) {
                if (!vis[v]) self(self, v);
            }
        };
        dfs(dfs, 0);
        if ((*min_element(all(vis))) == 0) continue;
            cout << n << " " << m << endl;
            for (auto [x, y] : edg) cout << x << " " << y << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
        auto my = solve(n, m, g, a);
        auto ans = brute(n, m, g, a);
        bool ok = true;
        if ((ans.empty()) != (my.empty())) ok = false;
        else if (!my.empty() and checker(n, m, g, a, my) == false) ok = false;

        if (!ok) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << m << endl;
            for (auto [x, y] : edg) cout << x << " " << y << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            cout << "Solve: ";
            for (auto x : my) cout << x << " ";
            if (!my.empty()) {
                cout << (checker(n, m, g, a, my) ? "ok" : "fail") << endl;
            } else {
                cout << "impossible" << endl;
            }
            cout << "Brute: ";
            for (auto x : ans) cout << x << " ";
            if (!ans.empty()) {
                cout << (checker(n, m, g, a, ans) ? "ok" : "fail") << endl;
            } else {
                cout << "impossible" << endl;
            }
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
