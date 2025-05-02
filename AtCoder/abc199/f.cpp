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
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n), deg(n), A;
    for (auto& x : a) cin >> x;
    vector<ii> edg(m);
    A = a;
    for (auto& [x, y] : edg) cin >> x >> y, --x, --y, deg[x]++, deg[y]++;
    auto inv = [&] (int b) {
        int e = mod-2, ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    int invm = inv(m), inv2 = inv(2);
    using matrix = vector<vector<int>>;
    auto mult = [&] (matrix a, matrix b) {
        matrix ans(n, vector<int>(n));
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) ans[i][j] = (ans[i][j] + a[i][k] * b[k][j]) % mod;
        }
        return ans;
    };
    matrix mat(n, vector<int>(n)), ans = mat;
    for (int i = 0; i < n; ++i) mat[i][i] = (m+(mod-deg[i])*inv2 % mod) * invm % mod;
    for (auto [u, v] : edg) mat[u][v] = mat[v][u] = inv2*invm % mod;
    for (int i = 0; i < n; ++i) ans[i][i] = 1;
    while (k) {
        if (k&1) ans = mult(ans, mat);
        k /= 2, mat = mult(mat, mat);
    }
    vector<int> resp(n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) resp[i] = (resp[i] + ans[i][j] * A[j]) % mod;
    for (auto x : resp) cout << x << ' ';
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
