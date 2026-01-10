#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < m; ++j) a[i][j] = s[j] - '0';
    }
    bool flip = 0;
    if (m > n) {
        vector<vector<int>> b(m, vector<int>(n));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
            b[j][i] = a[i][j];
        }
        swap(a, b);
        swap(n, m);
        flip = 1;
    }
    vector<vector<int>> ans(n, vector<int>(m));
    // pra cada coluna, quero guardar: pra cada linha uns trocos
    vector sexo(m, vector(m, vector(n, inf)));
    for (int l = m-1; ~l; --l) {
        for (int r = m-1; r > l; --r) {
            int lst = -1;
            for (int i = 0; i < n; ++i) {
                if (r != m-1) sexo[l][r][i] = sexo[l][r+1][i];
                if (a[i][l] == a[i][r] and a[i][r] == 1) {
                    // fiz o w
                    if (lst != -1) {
                        for (int j = lst; j <= i; ++j) ckmin(sexo[l][r][j], (r-l+1) * (i-lst+1));
                    }
                    lst = i;
                }
            }
        }
        if (l != m-1) for (int i = 0; i < n; ++i) sexo[l][l][i] = sexo[l][l+1][i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int opt = inf;
            for (int col = 0; col <= j; ++col) {
                // vou comecar aqui. entao o final precisa ser em i ou depois
                ckmin(opt, sexo[col][j][i]);
            }
            if (opt != inf) ans[i][j] = opt;
        }
    }
    if (flip) {
        vector<vector<int>> b(m, vector<int>(n));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
            b[j][i] = ans[i][j];
        }
        swap(ans, b);
        swap(n, m);
    }
    for (auto x : ans) {
        for (auto y : x) cout << y << " ";
        cout << endl;
    }
    cout << endl;
    // eh bem doente esse aqui, vou usar n * sqrt(n) de memoria

}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
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
