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

int solve(int n, int m, int k, vector<string> grid) {
    using matrix = vector<vector<int>>;
    auto mult = [] (matrix a, matrix b) {
        int n = sz(a);
        matrix c(n, vector<int>(n));
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) for (int k = 0; k < n; ++k) 
            c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
        return c;
    };
    auto fexpm = [mult] (matrix m, int e) {
        int n = sz(m); 
        matrix ans(n, vector<int>(n));
        for (int i = 0; i < n; ++i) ans[i][i] = 1;
        while (e) {
            if (e&1) ans = mult(ans, m);
            m = mult(m, m), e /= 2;
        }
        return ans;
    };
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };


    for (auto& x : grid) cin >> x;

    int t1 = 0, t2 = 0, ones = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == 0 and grid[n-1][j] == grid[0][j] and grid[0][j] == '#') t1++;
            if (j == 0 and grid[i][0] == grid[i][m-1] and grid[i][0] == '#') t2++;
            ones += (grid[i][j] == '#');
        }
    }

    if ((t1 and t2) or k <= 1) return 1;
    if (t1+t2 == 0)            return fexp(ones, k-1);

    int border = t1+t2;

    if (t1) {
        vector<string> g2(m, string(n, '#'));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) g2[j][i] = grid[i][j];
        swap(g2, grid);
        swap(n, m);
    }

    int adj = 0;

    for (int i = 0; i < n; ++i) for (int j = 0; j < m-1; ++j) if (grid[i][j] == grid[i][j+1] and grid[i][j] == '#') adj++;
    // an = componentes totais
    // bn = componentes laterais
    // c  = qtd adjacencias horizontais
    // d  = qtd 1s
    // e  = qtd de faixas horizontais que "ciclam"
    // a{n+1} = an * d - c bn
    // b{n+1} = e * b{n}
    // a{n+1} = an * d - c e^n
    // recorrencia linear, acredito que de pra resolver com expo
    // c = 2
    // d = 6
    // e = 2
    // a1 = 1
    // a2 = 6 - 2 = 4
    // a3 = 4 * 6 - 4 = 20
    // [d   c]  [ an ]  => [ d * an - ce^n]
    // [0   e]  [-e^{n-1}]     [    e^{n}   ]
    matrix mat(2, vector<int>(2)); mat[0][0] = ones, mat[0][1] = adj, mat[1][1] = border; mat = fexpm(mat, k-1);
    int ans = (mat[0][0] - mat[0][1] + mod) % mod;
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) {
        int n, m, k; cin >> n >> m >> k;

        vector<string> grid(n);
        cout << solve(n, m, k, grid) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 10), m = rnd(1, 10), k = rnd(0, 1e18);
        vector<string> grid(n, string(m, '#'));
        cout << n << ' ' << m << ' ' << k << endl;
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (i+j != 0 and rnd(0, 1)) grid[i][j] = '.';
        for (auto x : grid) cout << x << endl;
        cout << flush;
        solve(n, m, k, grid);
    }
#endif
}
