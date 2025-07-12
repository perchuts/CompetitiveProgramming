#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 1e18+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> solve(int n, int m, vector<int> a, vector<array<int, 5>> sexo) {
    vector<int> pos(n);
    vector<vector<vector<iii>>> g(5, vector<vector<iii>>(4*n));
    g[4].resize(m);
    // j < 2: descer
    // j >= 2: subir
    // j par: esquerda
    // j impar: direita
    auto init1 = [&] (auto&& self, int i, int j, int l, int r) -> void {
        if (l == r) {
            g[j][i].pb({i, 2, 0});
            g[j][i].pb({i, 3, 0});
            pos[l] = i;
            return;
        }
        int md = (l + r) / 2;
        g[j][i].pb({2*i, j, (j ? a[r] - a[md] : 0)});
        g[j][i].pb({2*i+1, j, (j ? 0 : a[md+1] - a[l])});
        self(self, 2*i, j, l, md);
        self(self, 2*i+1, j, md+1, r);
    };
    init1(init1, 1, 0, 0, n-1), init1(init1, 1, 1, 0, n-1);
    vector<ii> range(4*n);
    auto init2 = [&] (auto&& self, int i, int j, int l, int r) -> void {
        if (i != 1) g[j][i].pb({i/2, j, (j == 2 ? a[l] - a[range[i/2].first] : a[range[i/2].second] - a[r])});
        if (l == r) return;
        int md = (l + r) / 2;
        range[i] = {l, r};
        self(self, 2*i, j, l, md);
        self(self, 2*i+1, j, md+1, r);
    };
    init2(init2, 1, 2, 0, n-1), init2(init2, 1, 3, 0, n-1);
    auto add1 = [&] (auto&& self, int i, int l, int r, int x, int y, int dest, int cost) -> void {
        if (x <= l and r <= y) {
            g[3][i].pb({dest, 4, cost - a[r]});
            return;
        }
        if (r < x or y < l) return;
        int md = (l + r) / 2;
        self(self, 2*i, l, md, x, y, dest, cost);
        self(self, 2*i+1, md+1, r, x, y, dest, cost);
    };
    auto add2 = [&] (auto&& self, int i, int l, int r, int x, int y, int dest, int cost) -> void {
        if (x <= l and r <= y) {
            g[2][i].pb({dest, 4, cost + a[l]});
            return;
        }
        if (r < x or y < l) return;
        int md = (l + r) / 2;
        self(self, 2*i, l, md, x, y, dest, cost);
        self(self, 2*i+1, md+1, r, x, y, dest, cost);
    };
    auto go = [&] (auto&& self, int i, int l, int r, int x, int y, int id, int type) -> void {
        if (x <= l and r <= y) {
            if (type) g[4][id].pb({i, 0, a[l] - a[sexo[id][2]]});
            else g[4][id].pb({i, 1, a[sexo[id][3]] - a[r]});
            return;
        }
        if (r < x or y < l) return;
        int md = (l + r) / 2;
        self(self, 2*i, l, md, x, y, id, type);
        self(self, 2*i+1, md+1, r, x, y, id, type);
    };
    for (int i = 0; i < m; ++i) {
        if (sexo[i][1] < sexo[i][2]) {
            add1(add1, 1, 0, n-1, sexo[i][0], sexo[i][1], i, a[sexo[i][2]] + sexo[i][4]);
            go(go, 1, 0, n-1, sexo[i][2], sexo[i][3], i, 1);
        }
        else {
            add2(add2, 1, 0, n-1, sexo[i][0], sexo[i][1], i, -a[sexo[i][3]] + sexo[i][4]);
            go(go, 1, 0, n-1, sexo[i][2], sexo[i][3], i, 0);
        }
    }
    vector<vector<int>> dist(5, vector<int>(4*n, inf));
	dist[4] = vector<int>(m, inf);
    priority_queue<iii, vector<iii>, greater<>> pq;
    dist[2][pos[0]] = dist[3][pos[0]] = 0;
    pq.push({0, pos[0], 2});
    pq.push({0, pos[0], 3});
    while (!pq.empty()) {
        auto [d, i, j] = pq.top(); pq.pop();
        if (d != dist[j][i]) continue;
        for (auto [i2, j2, w] : g[j][i]) {
            if (ckmin(dist[j2][i2], d + w)) pq.push({d + w, i2, j2});
        }
    }
    vector<int> resp;
    for (int i = 1; i < n; ++i) {
        int ans = min(dist[2][pos[i]], dist[3][pos[i]]);
        resp.pb(ans == inf ? -1 : ans);
    }
    return resp;
}

vector<int> brute(int n, int m, vector<int> a, vector<array<int, 5>> adj) {
    vector<int> ans(n-1);
    vector<vector<int>> g(n, vector<int>(n, inf));
    for (int i = 0; i < n; ++i) g[i][i] = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = adj[i][0]; j <= adj[i][1]; ++j) {
            for (int k = adj[i][2]; k <= adj[i][3]; ++k) {
                ckmin(g[j][k], abs(a[j]-a[k]) + adj[i][4]);
            }
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ckmin(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    for (int i = 1; i < n; ++i) ans[i-1] = (g[0][i] == inf ? -1 : g[0][i]);
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    int n, m; cin >> n >> m;
    vector<int> a(n), pos(n);
    for (auto& x : a) cin >> x;
    vector<array<int, 5>> sexo(m);
    for (auto& x : sexo) for (int i = 0; i < 5; ++i) cin >> x[i], x[i] -= (i != 4);
    while(t--) {
        auto ans = solve(n, m, a, sexo);
        for (auto x : ans) cout << x << ' ';
        cout << endl;
    }
#else
    int t = 1;
    while (true) {
        int n, m; n = rnd(2, 30), m = rnd(1, 1000);
        vector<int> a(n);
        int lst = 0;
        for (auto& x : a) x = rnd(lst, lst + 10), lst = x+1;
        vector<array<int, 5>> sexo(m);
        for (auto& x : sexo) {
            x[0] = rnd(0, n-1), x[1] = rnd(x[0], n-1);
            while (x[0] == 0 and x[1] == n-1) x[0] = rnd(0, n-1), x[1] = rnd(x[0], n-1);
            int choice = (x[0] == 0 or (x[1] != n-1 and rnd(0, 1)));
            if (choice) x[2] = rnd(x[1]+1, n-1), x[3] = rnd(x[2], n-1);
            else x[3] = rnd(0, x[0]-1), x[4] = rnd(x[3], x[0]-1);
            x[4] = rnd(1, 10);
        }
        auto my = solve(n, m, a, sexo);
        auto ans = brute(n, m, a, sexo);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << endl;
            for (auto x : a) cout << x << ' ';
            cout << endl;
            for (auto x : sexo) {
                cout << x[0]+1 << ' ' << x[1]+1 << ' ' << x[2]+1 << ' ' << x[3]+1 << ' ' << x[4] << endl;
            }
            cout << "Your output: ";
            for (auto x : my) cout << x << ' ';
            cout << endl;
            cout << "Answer: ";
            for (auto x : ans) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
