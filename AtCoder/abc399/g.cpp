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
    int P = 998244853;
    vector<int> var(m+1), val(m+1, 1);
    vector<vector<int>> M(K, vector<int>(n));
    for (auto& x : var) x = rand() % P;
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
    int ans = 0, rank = 0;
    vector<int> pos(n+1, -1);
    vector<vector<int>> basis(n+1);
    vector<vector<int>> coord(n+1);
    auto add = [&] (int i, int j, int C) {
        for (int k = 0; k < n; ++k) {
            basis[i][k] = (basis[i][k] + C * basis[j][k]) % P;
            coord[i][k] = (coord[i][k] + C * coord[j][k]) % P;
        }
    };
    for (int i = K-1; ~i; --i) {
        basis[n] = M[i];
        coord[n] = vector<int>(n);
        int found = -1;
        for (int j = 0; j < n; ++j) {
            if (basis[n][j]) {
                if (pos[j] == -1) {
                    found = j;
                    break;
                } else {
                    int v = fexp(basis[j][j], P-2, P) * (P - basis[n][j]) % P;
                    add(n, j, v);
                }
            }  
        }
        if (found != -1) {
            pos[found] = i;
            coord[found] = coord[n];
            assert(coord[found][found] == 0);
            coord[found][found] = 1;
            basis[found] = basis[n];
            rank++;
            int X = fexp(basis[found][found], P-2, P);
            for (int j = 0; j < found; ++j) {
                if (pos[j] != -1 and basis[j][found]) add(j, found, X * (P - basis[j][found]) % P);
            }
        } else {
            int mx = -1, argmx;
            for (int j = 0; j < n; ++j) if (coord[n][j] != 0) {
                assert(pos[j] != -1);
                if (ckmax(mx, pos[j])) argmx = j;
            }
            if (mx != -1) {
                vector<int> bicho(n), ncoord(n);
                int invc = fexp(coord[n][argmx], P-2, P);
                bicho[argmx] = invc;
                pos[argmx] = i;
                for (int j = 0; j < n; ++j) {
                    if (j == argmx) continue;
                    bicho[j] = (P - coord[n][j]) * invc % P;
                }
                ncoord = coord[argmx];
                ncoord[argmx] = 0;
                for (int j = 0; j < n; ++j) {
                    ncoord[j] = (ncoord[j] + bicho[j] * coord[argmx][argmx]) % P;
                }
                for (int j = 0; j < n; ++j) {
                    if (j == argmx) {
                        coord[j] = ncoord;
                        continue;
                    }
                    if (pos[j] == -1) continue;
                    int X = coord[j][argmx];
                    coord[j][argmx] = 0;
                    for (int k = 0; k < n; ++k) {
                        coord[j][k] = (coord[j][k] + X * bicho[k]) % P;
                    }
                }
            } 
        }
        if (i == 0 or color[i-1] != color[i]) {
            if (rank != n-1) continue;
            int prim = color[*max_element(all(pos))];
            ans += c-prim;
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
