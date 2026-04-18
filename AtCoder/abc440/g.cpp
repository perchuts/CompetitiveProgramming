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

vector<int> solve(int f, int n, int m, vector<vector<string>> grid, vector<iii> queries) {
    struct cell {
        int h, x, y, par, score, lvl;
    };
    vector cti(f, vector(n, vector(m, 0)));
    vector<iii> itc(f*n*m);
    for (int i = 0; i < f; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                cti[i][j][k] = n*m*i + m*j + k;
                itc[n*m*i + m*j + k] = {i, j, k};
            }
        }
    }
    vector<cell> v(f*n*m);
    auto findp = [&] (auto&& self, int u) -> int {
        if (v[u].par == u) return u;
        return v[u].par = self(self, v[u].par);
    };
    auto unite = [&] (int x, int y) {
        x = findp(findp, x);
        y = findp(findp, y);
        if (x == y) return;
        if (v[x].lvl < v[y].lvl) swap(x, y);
        v[y].par = x;
        if (v[x].lvl == v[y].lvl) v[x].lvl++;
        v[x].score += v[y].score;
    };
    for (int i = 0; i < f*n*m; ++i) {
        auto [a, b, c] = itc[i];
        v[i].h = a;
        v[i].x = b;
        v[i].y = c;
        v[i].par = i;
        v[i].lvl = 0;
        if (grid[a][b][c] == '#') {
            v[i].score = 0;
            continue;
        }
        v[i].score = grid[a][b][c] - '0';
        // tenta ir pra frente
    }
    for (int i = 0; i < f*n*m; ++i) {
        auto [a, b, c] = itc[i];
        if (grid[a][b][c] == '#') continue;
        if (c != m-1 and grid[a][b][c+1] != '#') {
            unite(i, cti[a][b][c+1]); 
        }
        if (b != n-1 and grid[a][b+1][c] != '#') {
            unite(i, cti[a][b+1][c]); 
        }
    }
    vector<vector<int>> g(f*n*m), gi = g;
    for (int i = 0; i < f*n*m; ++i) {
        auto [a, b, c] = itc[i];
        if (a == f-1 or grid[a][b][c] == '#' or grid[a+1][b][c] == '#') continue;
        g[findp(findp, i)].pb(findp(findp, cti[a+1][b][c]));
        gi[findp(findp, cti[a+1][b][c])].pb(findp(findp, i));
    }
    for (int i = 0; i < f*n*m; ++i) {
        sort(all(g[i]));
        g[i].erase(unique(all(g[i])), end(g[i]));
        sort(all(gi[i]));
        gi[i].erase(unique(all(gi[i])), end(gi[i]));
    }
/*
3
2
5
2
9

#
#
4
#
#
                        bicho -> 4 -> 6. 
9
#
3
0
3

0
0
1
#
6

1
3 3 1

 * */
    vector<int> dp_path(f*n*m);
    vector<array<ii, 2>> tr(f*n*m), tri = tr;
    vector<array<int, 3>> skewed_dp(f*n*m);
    for (int i = f*n*m-1; ~i; --i) {
        sort(all(gi[i]), [&] (int x, int y) {
            return v[x].score > v[y].score;
        });
        sort(all(g[i]), [&] (int x, int y) {
            return dp_path[x] > dp_path[y];
        });
        dp_path[i] = v[i].score;
        tr[i][0] = {0, -1};
        tr[i][1] = {0, -1};
        if (sz(g[i]) >= 1) tr[i][0].first = dp_path[g[i][0]], tr[i][0].second = g[i][0], dp_path[i] += dp_path[g[i][0]];
        if (sz(g[i]) >= 2) tr[i][1].first = dp_path[g[i][1]], tr[i][1].second = g[i][1];
    }
    for (int i = f*n*m-1; ~i; --i) {
        // do it now!!
        for (auto x : gi[i]) ckmax(skewed_dp[i][1], dp_path[i] + v[x].score);
        for (auto x : g[i]) {
            if (tr[i][0].second == x) ckmax(skewed_dp[i][2], tr[i][1].first + v[i].score + v[x].score);
            else                      ckmax(skewed_dp[i][2], dp_path[i] + v[x].score);
        }
        // do it later..
        for (auto x : g[i]) {
            ckmax(skewed_dp[i][0], skewed_dp[x][0] + v[i].score);
            ckmax(skewed_dp[i][0], skewed_dp[x][2] + v[i].score);
            if (sz(gi[x]) > 1) {
                if (gi[x][0] != i) ckmax(skewed_dp[i][0], skewed_dp[x][1] + v[i].score);
                else               ckmax(skewed_dp[i][0], dp_path[x] + v[gi[x][1]].score + v[i].score);
            }
        }
    }
    vector<int> ans = dp_path;
    vector<int> temp_val(f*n*m);
    for (int i = f*n*m-1; ~i; --i) {
        // descer em algum filho meu ai
        for (auto j : gi[i]) {
            temp_val[j] = v[i].score + v[j].score;
            if (tr[j][0].second == i) temp_val[j] += tr[j][1].first;
            else                      temp_val[j] += tr[j][0].first;
        }
        sort(all(gi[i]), [&] (int x, int y) {
            return temp_val[x] > temp_val[y];
        });
        tri[i][0] = {0, -1};
        tri[i][1] = {0, -1};
        if (sz(gi[i]) >= 1) tri[i][0].first = temp_val[gi[i][0]], tri[i][0].second = gi[i][0];
        if (sz(gi[i]) >= 2) tri[i][1].first = temp_val[gi[i][1]], tri[i][1].second = gi[i][1];
    }
    for (int i = f*n*m-1; ~i; --i) {
        // descer em algum filho meu ai
        for (auto j : g[i]) {
            if (tri[j][0].second == i) ckmax(ans[i], v[i].score + tri[j][1].first);
            else ckmax(ans[i], v[i].score + tri[j][0].first);
        }
    }
    for (int i = f*n*m-1; ~i; --i) {
        for (auto j : g[i]) {
            ckmax(ans[i], ans[j] + v[i].score);
        }
    }
    for (int i = 0; i < f*n*m; ++i) {
        ckmax(ans[i], skewed_dp[i][2]);
        ckmax(ans[i], skewed_dp[i][1]);
        ckmax(ans[i], skewed_dp[i][0]);
        ckmax(ans[i], tri[i][0].first);
    }
    int q; cin >> q;
    vector<int> resps;
    for (auto [a, b, c] : queries) resps.pb(ans[findp(findp, cti[a][b][c])]);
    return resps;
}

vector<int> brute(int f, int n, int m, vector<vector<string>> grid, vector<iii> queries) {
    vector<int> resp;
    struct cell {
        int h, x, y, par, score, lvl;
    };
    vector cti(f, vector(n, vector(m, 0)));
    vector<iii> itc(f*n*m);
    for (int i = 0; i < f; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                cti[i][j][k] = n*m*i + m*j + k;
                itc[n*m*i + m*j + k] = {i, j, k};
            }
        }
    }
    vector<cell> v(f*n*m);
    auto findp = [&] (auto&& self, int u) -> int {
        if (v[u].par == u) return u;
        return v[u].par = self(self, v[u].par);
    };
    auto unite = [&] (int x, int y) {
        x = findp(findp, x);
        y = findp(findp, y);
        if (x == y) return;
        if (v[x].lvl < v[y].lvl) swap(x, y);
        v[y].par = x;
        if (v[x].lvl == v[y].lvl) v[x].lvl++;
        v[x].score += v[y].score;
    };
    for (int i = 0; i < f*n*m; ++i) {
        auto [a, b, c] = itc[i];
        v[i].h = a;
        v[i].x = b;
        v[i].y = c;
        v[i].par = i;
        v[i].lvl = 0;
        if (grid[a][b][c] == '#') {
            v[i].score = 0;
            continue;
        }
        v[i].score = grid[a][b][c] - '0';
        // tenta ir pra frente
    }
    for (int i = 0; i < f*n*m; ++i) {
        auto [a, b, c] = itc[i];
        if (grid[a][b][c] == '#') continue;
        if (c != m-1 and grid[a][b][c+1] != '#') {
            unite(i, cti[a][b][c+1]); 
        }
        if (b != n-1 and grid[a][b+1][c] != '#') {
            unite(i, cti[a][b+1][c]); 
        }
    }
    vector<vector<int>> g(f*n*m), gi = g;
    for (int i = 0; i < f*n*m; ++i) {
        auto [a, b, c] = itc[i];
        if (a == f-1 or grid[a][b][c] == '#' or grid[a+1][b][c] == '#') continue;
        g[findp(findp, i)].pb(findp(findp, cti[a+1][b][c]));
        gi[findp(findp, cti[a+1][b][c])].pb(findp(findp, i));
    }
    for (int i = 0; i < f*n*m; ++i) {
        sort(all(g[i]));
        g[i].erase(unique(all(g[i])), end(g[i]));
        sort(all(gi[i]));
        gi[i].erase(unique(all(gi[i])), end(gi[i]));
    }
    for (auto [fl, xx, yy] : queries) {
        // poe o troco
        int opt = 0;
        for (int o = 0; o < f; ++o) {
            if (grid[fl][xx][yy] == '#') continue;
            for (int p = 0; p < n; ++p) {
                for (int q = 0; q < m; ++q) {
                    if (o != 0 and grid[o][p][q] != '#' and grid[o-1][p][q] != '#') {
                        int z1 = findp(findp, cti[o][p][q]);
                        int z2 = findp(findp, cti[o-1][p][q]);
                        g[z1].pb(z2);
                    }
                    int z1 = findp(findp, cti[o][p][q]);
                    int z2 = (o == 0 ? -1 : findp(findp, cti[o-1][p][q]));
                    vector<int> vis(f*n*m);
                    auto backtracking = [&] (auto&& self, int u, int score, int mode) -> void {
                        if (mode == 0) {
                            ckmax(opt, score);
                        } else if (mode == 1) {
                            if (z2 != -1 and vis[z2]) ckmax(opt, score + v[z1].score);
                        } else {
                            if (vis[z1]) ckmax(opt, score + (z2 == -1 ? 0 : v[z2].score));
                        }
                        for (auto w : g[u]) {
                            if (vis[w]) continue;
                            if (mode == 1 and w == z1) continue;
                            if (mode == 2 and w == z2) continue;
                            vis[w] = 1;
                            self(self, w, score + v[w].score, mode);
                            vis[w] = 0;
                        }
                    };
                    int eu = findp(findp, cti[fl][xx][yy]);
                    vis[eu] = 1;
                    backtracking(backtracking, eu, v[eu].score, 0);
                    if (eu != z1) backtracking(backtracking, eu, v[eu].score, 1);
                    if (eu != z2) backtracking(backtracking, eu, v[eu].score, 2);
                    if (o != 0 and grid[o][p][q] != '#' and grid[o-1][p][q] != '#') g[z1].pop_back();
                }
            }
        }
        resp.pb(opt);
    }
    return resp;
}

int32_t main() {_
#ifndef gato
    int f, n, m; cin >> f >> n >> m;
    vector<vector<string>> grid(f);
    for (int i = 0; i < f; ++i) {
        grid[i].resize(n);
        for (int j = 0; j < n; ++j) cin >> grid[i][j];
    }
    int q; cin >> q;
    vector<iii> queries(q);
    for (auto& [a,b,c] : queries) cin >> a >> b >> c, --a, --b, --c;
    auto ans = solve(f, n, m, grid, queries);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int f = 8, n = rnd(1, 6), m = rnd(1, 1);
        vector<vector<string>> grid(f);
        for (int i = 0; i < f; ++i) {
            grid[i].resize(n);
            for (int j = 0; j < n; ++j) {
                if (rnd(1,4) == 4) grid[i][j] = '#';
                else grid[i][j] = char('0'+rnd(0, 9));
            }
        }
        int q = 1;
        vector<iii> queries(q);
        for (auto& [a, b, c] : queries) {
            a = rnd(0, f-1);
            b = rnd(0, n-1);
            c = rnd(0, m-1);
            if (grid[a][b][c] == '#') q = 0;
        }
        if (q == 0) continue;
        auto my = solve(f, n, m, grid, queries);
        auto ans = brute(f, n, m, grid, queries);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << f << " " << n << " " << m << endl;
            for (auto x : grid) {
                for (auto y : x) cout << y << endl;
                cout << endl;
            }
            cout << q << endl;
            for (auto [a,b,c] : queries) cout << a+1 << " " << b+1 << " " << c+1 << endl;
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
