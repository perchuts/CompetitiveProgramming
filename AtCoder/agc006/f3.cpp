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

void brute(int n, int m, vector<vector<int>> g) {
    set<ii> check;
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i)  {
        for (auto j : g[i]) {
            check.insert({i, j});
            adj[i][j] = 1;
        }
    }
    while (true) {
        bool foi = 0;
        for (int i = 0; i < n; ++i) {
            for (auto j : g[i]) {
                for (auto k : g[j]) {
                    if (adj[k][i] == 0) {
                        foi = 1;
                        adj[k][i] = 1;
                        g[k].pb(i);
                        check.insert({k, i});
                        break;
                    }
                }
                if (foi) break;
            }
            if (foi) break;
        }
        if (foi == 0) break;
    }
    cout << sz(check) << endl;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n), gi(n);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].pb(v);
        gi[v].pb(u);
    }
    //brute(n, m, g);
    vector<int> vis(n), comp(n);
    stack<int> S;
    auto dfs = [&] (auto&& self, int k) -> void {
        vis[k] = 1;
        for (int i = 0; i < (int) g[k].size(); i++)
            if (!vis[g[k][i]]) self(self, g[k][i]);

        S.push(k);
    };
    auto scc = [&] (auto&& self, int k, int c) -> void {
        vis[k] = 1;
        comp[k] = c;
        for (int i = 0; i < (int) gi[k].size(); i++)
            if (!vis[gi[k][i]]) self(self, gi[k][i], c);
    };
    auto kosaraju = [&] () {
        for (int i = 0; i < n; i++) vis[i] = 0;
        for (int i = 0; i < n; i++) if (!vis[i]) dfs(dfs, i);

        for (int i = 0; i < n; i++) vis[i] = 0;
        while (S.size()) {
            int u = S.top();
            S.pop();
            if (!vis[u]) scc(scc,u, u);
        }
    };
    kosaraju();
    vector<int> tam(n);
    vector<vector<int>> g2(n), gi2(n), gg(n);
    for (int i = 0; i < n; ++i) {
        tam[comp[i]]++;
        for (auto j : g[i]) {
            if (comp[i] != comp[j]) g2[comp[i]].pb(comp[j]), gi2[comp[j]].pb(comp[i]), gg[comp[i]].pb(comp[j]), gg[comp[j]].pb(comp[i]);
        }
    }
    for (int i = 0; i < n; ++i) {
        sort(all(g2[i])), g2[i].erase(unique(all(g2[i])), end(g2[i]));
        sort(all(gi2[i])), gi2[i].erase(unique(all(gi2[i])), end(gi2[i]));
        vis[i] = 0;
    }

    vector<int> color(n, -1);
    vector<int> freq(3);
    vector<int> cur_comp;
    auto explore = [&] (auto&& self, int u) -> void {
        cur_comp.pb(u);
        vis[u] = 1;
        for (auto v : gg[u]) {
            if (!vis[v]) self(self, v);
        }
    };
    //auto explore = [&] (auto&& self, int u) -> bool {
    //    vis[u] = 1;
    //    freq[color[u]]++;
    //    bool ok = true;
    //    for (auto v : g[u]) {
    //        if (vis[v]) {
    //            ok &= (color[v] == (1 + color[u]) % 3);
    //        } else { 
    //            color[v] = (1 + color[u]) % 3;
    //            ok &= self(self, v);
    //        }
    //    }
    //    return ok;
    //};

    int ans = 0;
    vector<vector<int>> bichos(n);
    for (int i = 0; i < n; ++i) bichos[comp[i]].pb(i);
    vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
        if (comp[i] != i) continue;
        if (!vis[i]) {
            cur_comp.clear();
            freq[0] = freq[1] = freq[2] = 0;
            explore(explore, i);
            for (auto u : cur_comp) {
                for (auto v : g2[u]) deg[v]++;
            }
            queue<int> q;
            for (auto u : cur_comp) {
                if (deg[u] == 0) q.push(u);
            }
            while (!q.empty()) {

            }
            //ans += freq[0] * freq[1] + freq[1] * freq[2] + freq[2] * freq[0];
            //ans += (freq[0]+freq[1]+freq[2])*(freq[0]+freq[1]+freq[2]);
            // se essa componente tiver qualquer SCC de tamanho > 1 e nao divisivel por 3, entao ela sera uma clique! -> falso
        }
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
