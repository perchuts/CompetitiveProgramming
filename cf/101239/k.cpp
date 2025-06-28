#include <bits/stdc++.h>
//#define GATO
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;


int tarjan(int n, vector<pair<int, int>>& edg, bool tira=false) {
    vector<vector<int>> g(n);
    for (auto &[a, b] : edg) {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int t = 0;
    stack<int> s;
    vector<int> vis(n), id(n), comp(n);

    set<pair<int, int>> rem;

    auto dfs = [&] (auto&& self, int u, int p) -> int {
        int lo = id[u] = t++;
        s.push(u);
        vis[u] = 2;

        for (int j : g[u]) if (j != p) {
            if (!vis[j]) lo = min(lo, self(self, j, u));
            else if (vis[j] == 2) lo = min(lo, id[j]);
        }

        if (lo == id[u]) {
            if (p != -1) rem.insert({u, p});
            while (1) {
                int v = s.top(); s.pop();
                vis[v] = 1; comp[v] = u;
                if (v == u) break;
            }
        }

        return lo;
    };


    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(dfs, i, -1);
        }
    }

    if (tira) {
        vector<pair<int, int>> nedg;
        for (auto &[a, b] : edg) {
            if (!rem.count({a, b}) && !rem.count({b, a})) {
                nedg.push_back({a, b});
            }
        }
        swap(edg, nedg);
    }

    //cout << "CC: ";
    //for (auto [a, b] : rem) cout << a+1 << "," << b+1 << " ";
    //cout << endl;

    return rem.size();
}

vector<int> kaio(int n, int m, vector<pair<int, int>> edg) {
    tarjan(n, edg, true);

    int g = 0;
    for (int i = 0; i < edg.size(); i++) {
        auto [a, b] = edg[i];
        edg.erase(edg.begin() + i);

        int at = 1 + tarjan(n, edg);

        g = gcd(g, at);
        edg.insert(edg.begin() + i, {a, b});
    }

    vector<int> ans;
    for (int i = 1; i <= g; i++) {
        if (g % i == 0) {
            ans.push_back(i);
        }
    }

    return ans;
}

vector<int> perchuts(int n, int m, vector<pair<int, int>> edg) {
    using ii = pair<int, int>;
    #define pb push_back

    vector<vector<int>> foi(n, vector<int>(n));
    vector<vector<int>> ignore(n, vector<int>(n));
    vector<vector<int>> g(n);
    for (auto& [u, v] : edg) {
        g[u].pb(v), g[v].pb(u);
    }
    auto go = [&] (int A, int B, int turn = -1) {
        vector<int> dp(n), lvl(n);
        vector<ii> sexo;
        auto dfs = [&] (auto&& self, int u, int p) -> void {
            lvl[u] = lvl[p] + 1;
            for (auto v : g[u]) {
                if (ignore[u][v]) continue;
                if ((u == A and v == B) or (u == B and v == A)) continue;
                if (lvl[v] == 0) {
                    self(self, v, u);
                    dp[u] += dp[v];
                } else if (lvl[v] < lvl[u]) {
                    dp[u]++;
                } else {
                    dp[u]--;
                }
            }
            if (u != p) dp[u]--;
            if (u != p and dp[u] == 0) {
                if (turn != -1) sexo.pb({min(u, p), max(u, p)});
                else ignore[u][p] = ignore[p][u] = 1;
            }
        };
        dfs(dfs, A, A);
        if (turn == -1) return;
        sexo.pb({min(A, B), max(A, B)});
        for (auto [x, y] : sexo) foi[x][y] = turn;
    };
    for (int i = 0; i < n; ++i) go(i, i);
    for (int i = 0; i < m; ++i) {
        auto [u, v] = edg[i];
        if (ignore[u][v]) continue;
        go(edg[i].first, edg[i].second, i);
    }
    vector<int> freq(m);
    for (auto [x, y] : edg) {
        if (x > y) swap(x, y);
        //cout << x + 1 << ' ' << y+1 << ' ' << foi[x][y] << endl;
        if (!ignore[x][y]) freq[foi[x][y]]++;
    }
    int G = 0;
    for (auto x : freq) G = gcd(G, x);

    vector<int> ans;
    for (int i = 1; i <= G; ++i) {
        if (G % i == 0) ans.push_back(i);
    }

    return ans;
}

int32_t main() {
#ifndef GATO
    fast_io;

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edg(m);
    for (auto &[a, b] : edg) {
        cin >> a >> b;
        a--, b--;
    }

    auto ret = perchuts(n, m, edg);

    for (auto i : ret) cout << i << " ";
    cout << endl;
#else

    for (int seed = 1; ; seed++) {
        srand(seed);

        int n = 6, m = rand() % n + n;
        vector<pair<int, int>> edg(m);
        set<pair<int, int>> used;
        for (auto &[a, b] : edg) {
            a = rand() % n;
            b = rand() % n;
            while (a == b || used.count({a, b}) || used.count({b, a})) {
                a = rand() % n;
                b = rand() % n;
            }
            used.insert({a, b});
            if (a == b) continue;
        }

        auto sol1 = kaio(n, m, edg);
        auto sol2 = perchuts(n, m, edg);
        if (sol1 != sol2) {
            cout << "WA " << seed << endl;

            cout << n << " " << m << endl;
            for (auto &[a, b] : edg) {
                cout << a + 1 << " " << b + 1 << endl;
            }
            cout << "Sol1: ";
            for (auto i : sol1) cout << i << " ";
            cout << endl;
            cout << "Sol2: ";
            for (auto i : sol2) cout << i << " ";
            cout << endl;

            break;
        }

        cout << "AC " << seed << endl;
    }

#endif
}
