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
// Simplex
//
// Maximiza c^T x s.t. Ax <= b, x >= 0
//
// O(2^n), porem executa em O(n^3) no caso medio

const double eps = 1e-7;

namespace Simplex {
vector<vector<double>> T;
int n, m;
vector<int> X, Y;

void pivot(int x, int y) {
    swap(X[y], Y[x-1]);
    for (int i = 0; i <= m; i++) if (i != y) T[x][i] /= T[x][y];
    T[x][y] = 1/T[x][y];
    for (int i = 0; i <= n; i++) if (i != x and abs(T[i][y]) > eps) {
        for (int j = 0; j <= m; j++) if (j != y) T[i][j] -= T[i][y] * T[x][j];
        T[i][y] = -T[i][y] * T[x][y];
    }
}

// Retorna o par (valor maximo, vetor solucao)
pair<double, vector<double>> simplex(
    vector<vector<double>> A, vector<double> b, vector<double> c) {
    n = b.size(), m = c.size();
    T = vector(n + 1, vector<double>(m + 1));
    X = vector<int>(m);
    Y = vector<int>(n);
    for (int i = 0; i < m; i++) X[i] = i;
    for (int i = 0; i < n; i++) Y[i] = i+m;
    for (int i = 0; i < m; i++) T[0][i] = -c[i];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) T[i+1][j] = A[i][j];
        T[i+1][m] = b[i];
    }
    while (true) {
        int x = -1, y = -1;
        double mn = -eps;
        for (int i = 1; i <= n; i++) if (T[i][m] < mn) mn = T[i][m], x = i;
        if (x < 0) break;
        for (int i = 0; i < m; i++) if (T[x][i] < -eps) { y = i; break; }

        if (y < 0) return {-1e18, {}}; // sem solucao para  Ax <= b
        pivot(x, y);
    }
    while (true) {
        int x = -1, y = -1;
        double mn = -eps;
        for (int i = 0; i < m; i++) if (T[0][i] < mn) mn = T[0][i], y = i;
        if (y < 0) break;
        mn = 1e200;
        for (int i = 1; i <= n; i++) if (T[i][y] > eps and T[i][m] / T[i][y] < mn)
            mn = T[i][m] / T[i][y], x = i;

        if (x < 0) return {1e18, {}}; // c^T x eh ilimitado
        pivot(x, y);
    }
    vector<double> r(m);
    for(int i = 0; i < n; i++) if (Y[i] < m) r[Y[i]] = T[i+1][m];
    return {T[0][m], r};
}
}
void solve(){
    int n; cin >> n;
    vector<vector<int>> adj(n, vector<int>(n)), ide = adj;
    vector<iii> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> adj[i][j];
            if (adj[i][j] == -1) adj[i][j] = inf;
            else if (i != j) {
                ide[i][j] = sz(edges);
                edges.pb({i, j, adj[i][j]});
            }
        }
    }
    for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ckmin(adj[i][j], adj[i][k] + adj[k][j]);
    auto get = [&] (int u, int v) {
        vector<int> res;
        while (u != v) {
            int cara = -1, best = inf;
            for (int i = 0; i < n; ++i) {
                if (adj[u][v] == adj[u][i] + adj[i][v] and u != i and ckmin(best, adj[u][i])) cara = i;
            }
            res.pb(ide[u][cara]), u = cara;
        }
        return res;
    };
    int m = sz(edges);
    vector<vector<double>> A;
    vector<double> B;
    int r; cin >> r;
    vector<iii> sexo(r);
    vector<int> mark(m);
    for (auto& [x, y, z] : sexo) {
        cin >> x >> y >> z;
        int tot = 0;
        auto path = get(x, y);
        for (auto i : path) mark[i] = 1;
        vector<double> row(m), row2(m);
        for (int i = 0; i < m; ++i) {
            if (mark[i] == 0) continue;
            auto [u, v, w] = edges[i];
            tot += w;
            row[i] = w;
            row2[i] = -w;
        }
        A.pb(row), A.pb(row2);
        B.pb(z-tot);
        B.pb(-(z-tot));
        for (auto i : path) mark[i] = 0;
    }
    vector<double> can(m);
    for (int i = 0; i < m; ++i) {
        can[i] = 1;
        A.pb(can);
        B.pb(1);
        can[i] = 0;
    }
    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        auto path = get(u, v);
        for (auto i : path) mark[i] = 1;
        vector<double> C(m);
        double fl = 0;
        for (int i = 0; i < m; ++i) {
            if (mark[i] == 0) continue;
            auto [u, v, w] = edges[i];
            fl += w;
            C[i] = -w;
        }
        auto [ans, cert] = Simplex::simplex(A, B, C);
        for (auto& x : C) x *= -1;
        auto [ans2, cert2] = Simplex::simplex(A, B, C);
        for (auto i : path) mark[i] = 0;
        cout << u << ' ' << v << ' ';
        cout << fixed << setprecision(10) << fl-ans << ' ' << fl+ans2 << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
