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

void solve(){
    int n, m, c, K = 0; cin >> n >> m >> c;
    vector<int> a(c), color(400);
    for (int z = 0; z < c; ++z) {
        cin >> a[z];
        for (int i = 0; i < a[z]; ++i) color[K+i] = z;
        K += a[z];
    }
    vector<vector<iii>> edg(c);
    for (int i = 0; i < m; ++i) {
        int u, v, ci; cin >> u >> v >> ci;
        --u, --v, --ci;
        if (u < v) swap(u, v);
        edg[ci].pb({u, v, 0});
    }
    auto fexp = [] (int b, int e, int m) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % m;
            e /= 2, b = b * b % m;
        }
        return ans;
    };
    int P = 998244353;
    vector<int> var(m+1), val(m+1, 1);
    vector<vector<int>> M(K, vector<int>(n));
    for (auto& x : var) x = rand() % P;
    {
        auto mult = [] (vector<vector<int>> a, vector<vector<int>> b, int P) {
            vector<vector<int>> c(sz(a), vector<int>(sz(b[0])));
            assert(sz(a[0]) == sz(b));
            for (int i = 0; i < sz(a); ++i) for (int j = 0; j < sz(b[0]); ++j) {
                for (int k = 0; k < sz(b); ++k) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % P;
            }
            return c;
        };
        auto T = [] (vector<vector<int>> aa) {
            int n = sz(aa), m = sz(aa[0]);
            vector<vector<int>> bb(m, vector<int>(n));
            for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) bb[j][i] = aa[i][j];
            return bb;
        };
        vector<vector<int>> A1(K, vector<int>(m));
        int ptr = 1;
        for (int cc = 0; cc < c; ++cc) {
            for (auto& [u, v, label] : edg[cc]) {
                label = ptr++; 
                int cnt = 0;
                for (int j = 0; j < K; ++j) if (color[j] == cc) A1[j][label-1] = fexp(label, cnt++, P);
            }
        }
        vector<vector<int>> D(m, vector<int>(m));
        for (int i = 0; i < m; ++i) D[i][i] = var[i];
        vector<vector<int>> A2(n, vector<int>(m));
        for (int cc = 0; cc < c; ++cc) {
            for (auto& [u, v, label] : edg[cc]) {
                A2[u][label-1] = 1;
                A2[v][label-1] = P-1;
            }
        }
        auto ans = mult(A1, mult(D, T(A2), P), P);
        //M = ans;
        //cout << "ans: " << endl;
        //for (auto x : ans) {
        //    for (auto y : x) cout << y << ' ';
        //    cout << endl;
        //}
        //cout << "A1: " << endl;
        //for (auto x : A1) {
        //    for (auto y : x) cout << y << ' ';
        //    cout << endl;
        //}
        //cout << endl;
        //cout << "D: " << endl;
        //for (auto x : D) {
        //    for (auto y : x) cout << y << ' ';
        //    cout << endl;
        //}
        //cout << endl;
        //cout << "A2: " << endl;
        //for (auto x : T(A2)) {
        //    for (auto y : x) cout << y << ' ';
        //    cout << endl;
        //}
        //cout << endl;
        //cout << "A1D: " << endl;
        //for (auto x : mult(A1, D, P)) {
        //    for (auto y : x) cout << y << ' ';
        //    cout << endl;
        //}
        //cout << endl;
    }
    int ptr = 1;
    for (int i = 0; i < K; ++i) {
        int cc = color[i];
        for (auto& [u, v, label] : edg[cc]) {
            if (!label) label = ptr++; 
            M[i][u] = (M[i][u] + val[label] * var[label]) % P;
            M[i][v] = (M[i][v] + val[label] * var[label] % P * (P-1)) % P;
        }
        for (int j = 1; j <= m; ++j) val[j] = val[j] * j % P;
    }
    //cout << "My: " << endl;
    //for (auto x : M) {
    //    for (auto y : x) cout << y << ' ';
    //    cout << endl;
    //}
    //cout << endl;
    //vector<int> vv(n);
    //for (int i = 0; i < n; ++i) vv[i] = (M[2][i] - (79 * M[1][i] * fexp(91, P-2, P) % P) + P) % P;
    //for (int i = 0; i < n; ++i) {
    //    vv[i] = vv[i] * fexp(vv[0], P-2, P) * M[0][0] % P;
    //    cout << vv[i] << " \n"[i==n-1];
    //}
    int ans = 0, rank = 0;
    vector<int> pos(n, -1);
    vector<vector<int>> basis(n+1);
    vector<vector<int>> coord(n+1);
    auto add = [&] (int i, int j, int C) {
        for (int k = 0; k < n; ++k) {
            basis[i][k] = (basis[i][k] + C * basis[j][k]) % mod;
            coord[i][k] = (coord[i][k] + C * coord[j][k]) % mod;
        }
    };
    for (int i = K-1; ~i; --i) {
        basis[n] = M[i];
        coord[n] = vector<int>(n);
        int found = -1;
        for (int j = 0; j < n; ++j) {
            if (basis[n][j]) {
                if (pos[j] != -1) {
                    found = j;
                    break;
                } else add(n, j, fexp(basis[j][j], P-2, P) * (P - basis[n][j]) % P);
            }  
        }
        if (found != -1) {
            assert(coord[found][found] == 0);
            pos[found] = i;
            coord[found][found] = 1;
            basis[found] = basis[n];
            rank++;
            int X = fexp(basis[found][found], P-2, P);
            for (int j = 0; j < found; ++j) {
                if (pos[j] != -1 and basis[j][found]) add(j, found, X * (P - basis[j][found]) % P);
            }
        } else {
            int mx = 0;
            for (int j = 0; j < n; ++j) if (coord[n][j] != 0) {
                assert(pos[j] != -1);
                ckmax(mx, pos[j]);
            }
            vector<int> ncoord(n);
            int invc = fexp(coord[n][mx], P-2, P);
            ncoord[mx] = invc;
            for (int j = 0; j < n; ++j) {
                if (j == mx) continue;
                ncoord[j] = (P - coord[n][j]) * invc % P;
            }
            for (int j = 0; j < n; ++j) {
                if (j == mx) {
                    coord[j] = ncoord;
                    continue;
                }
                int X = coord[j][mx];
                coord[j][mx] = 0;
                for (int k = 0; k < n; ++k) {
                    coord[j][k] = (coord[j][k] + X * ncoord[k]) % P;
                }
            }
            // quero escrever basis[mx] em termos de M[i]
            // M[i] = sum_j coord[j] basis[j]
            // M[i] - alguma coisa = coord[mx] * basis[mx]
            // -> M[i] vira 1 de mx
            // basis[mx] = ((000...1...0000) - alguma coisa) / coord[mx]
            // simplesmente de o replace!
        }
        if (i == 0 or color[i-1] != color[i]) {
            if (rank != n-1) continue;
            int prim = color[*max_element(all(pos))];
            ans += c-prim;
        }
    }
    //for (int l = 0; l < K; ++l) {
    //    if (l != 0 and color[l] == color[l-1]) continue;
    //    // vou comecar aqui~!
    //    vector<vector<int>> basis(n);
    //    int tam = 0;
    //    for (int r = l; r < K; ++r) {
    //        auto temp = M[r];
    //        for (int i = 0; i < n; ++i) {
    //            if (temp[i] != 0) {
    //                if (basis[i].empty()) {
    //                    int coeff = fexp(temp[i], P-2, P);
    //                    for (int j = i; j < n; ++j) temp[j] = temp[j] * coeff % P;
    //                    basis[i] = temp, tam++;
    //                    break;
    //                }
    //                assert(basis[i][i] == 1);
    //                int X = (P - temp[i]);
    //                for (int j = i; j < n; ++j) temp[j] = (temp[j] + X * basis[i][j]) % P;
    //            }
    //        }
    //        if (r == K-1 or color[r] != color[r+1]) {
    //            cout << color[l] << ' ' << color[r] << ": " << tam << endl;
    //            if (tam == n-1) ans++;
    //        }
    //    }
    //}
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
