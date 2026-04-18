#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<vector<int>> paths;
int used = 0;

vector<ii> solve(int n) {
    auto ask = [&] (int x) {
        //cout << "Query: " << x << endl;
#ifndef gato
        cout << "? " << x + 1 << endl;
        vector<int> ans;
        int k; cin >> k;
        for (int i = 0; i < k; ++i) {
            int z; cin >> z; --z;
            ans.pb(z);
        }
        return ans;
#endif
        used++;
        //cout << "resp: ";
        if (x >= sz(paths)) {
            return vector<int>();
        }
        //for (auto y : paths[x]) cout << y + 1 << " ";
        //cout << endl;
        return paths[x];
    };
    vector<int> caixa(n);
    vector<vector<int>> antes(n);
    vector<int> atv(n, -1);
    // pra gente resolver o problema basta descobrir a caixa de todos os vertices!
    vector<ii> edg;
    int falta = n, cur = 1;
    atv[0] = 0;
    while (falta) {
        auto v = ask(cur);
        vector<int> mark(n);
        for (auto x : v) mark[x] = 1;
        for (int i = 0; i < n; ++i) {
            if (atv[i] != -1 and mark[i] == 0) {
                //cout << "caixa do " << i << ": ";
                //cout << atv[i] << " " << cur-1 << endl;
                caixa[i] = cur - atv[i];
                atv[i] = -1;
                falta--;
            }
        }
        vector<int> v2;
        for (int i = 0; i < sz(v); ++i) {
            int j = v[i];
            if (atv[j] != -1 and antes[j] != v2) {
                //cout << "caixa do " << j << ": ";
                //cout << atv[j] << " " << cur-1 << endl;
                caixa[j] = cur - atv[j];
                atv[j] = -1;
                falta--;
            }
            v2.pb(v[i]);
        }
        int k = sz(v);
        if (k > 1) edg.pb({v[k-2], v[k-1]});
        if (k and !caixa[v[k-1]] and atv[v[k-1]] == -1) {
            atv[v[k-1]] = cur;
            int penis = v[k-1];
            v.pop_back();
            antes[penis] = v;
        }
        if (k and caixa[v[k-1]]) cur += caixa[v[k-1]];
        else cur++;
    }
    return edg;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        auto ans = solve(n);
        cout << "! " << sz(ans) << endl;
        for (auto [x, y] : ans) cout << x + 1 << " " << y + 1 << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 15);
        vector<vector<int>> g(n);
        vector<ii> edg;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) if (rnd(0, 1)) edg.pb({j, i});
        }
        vector<int> p(n); iota(all(p), 0); shuffle(all(p), rng);
        for (auto& [u, v] : edg) g[p[u]].pb(p[v]), u = p[u], v = p[v];
        paths.clear();
        auto go = [&] (auto&& self, int u, vector<int> path) -> void {
            path.pb(u);
            paths.pb(path);
            for (auto v : g[u]) self(self, v, path);
        };
        for (int i = 0; i < n; ++i) go(go, i, {});
        sort(all(paths));
        vector<vector<int>> ans(n, vector<int>(n));
        for (auto [u, v] : edg) ans[u][v] = 1;
        //cout << "graph: " << n << " " << sz(edg) << endl;
        //for (auto [u, v] : edg) cout << u+1 << " " << v + 1 << endl;
        //cout << endl;
        auto resp = solve(n);
        //cout << "Answering: ";
        //cout << "! " << sz(resp) << endl;
        //for (auto [u, v] : resp) cout << u+1 << " " << v + 1 << endl;
        bool ok = 1;
        if (sz(resp) != sz(edg)) ok = 0;
        used = 0;
        for (auto [u, v] : resp) {
            ok &= (ans[u][v] == 1);
        }
        for (auto& [x, y] : resp) if (x < y) swap(x, y);
        for (auto& [x, y] : edg) if (x < y) swap(x, y);
        sort(all(resp)), sort(all(edg));
        if (!ok or used > n + sz(edg)) {
            cout << "Wrong answer on test " << t << endl;
            exit(0);
        }
        assert(resp == edg);
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
