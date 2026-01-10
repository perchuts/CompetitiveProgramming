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

int dp[1001][33768];
bool tr[1001][33768];

void solve() {
    int n, m, l, d, e; cin >> n >> m >> l >> d >> e;
    vector<vector<int>> g(n), g2(n);
    const int n_facts = 100;
    vector<vector<int>> onde(n_facts);
    struct memory {
        int li, ri;
        vector<int> f;
        memory (int lx, int rx, int tam) {
            li = lx, ri = rx;
            f = vector<int>(tam);
            for (auto& x : f) cin >> x, --x;
        };
        memory () {}
    };
    vector<memory> mm(n);
    for (int i = 0; i < n; ++i) {
        int a, b, c; cin >> a >> b >> c;
        mm[i] = memory(a, b, c);
        for (auto x : mm[i].f) onde[x].pb(i);
    }
    for (int i = 0; i < d; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v);
    }
    for (int i = 0; i < e; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g2[u].pb(v);
    }
    vector<vector<int>> queries(m);
    for (int i = 0; i < m; ++i) {
        int tt; cin >> tt;
        queries[i].resize(tt);
        for (auto& x : queries[i]) cin >> x, --x;
    }
    vector<vector<int>> ans(m);
    // dah pra soh fazer um knapsack nos caras importantes!
    // inicialmente vamos ignorar restricoes de dependencia, mutualidade exclusiva.
    for (int idq = 0; idq < m; ++idq) {
        vector<int> caras;
        for (auto x : queries[idq]) {
            for (auto z : onde[x]) caras.pb(z);
        }
        sort(all(caras)), caras.erase(unique(all(caras)), end(caras));
        for (int i = 1; i <= sz(caras); ++i) {
            int bicho = caras[i-1];
         int li = mm[bicho].li;
         int ri = mm[bicho].ri;
            for (int j = 0; j < l; ++j) {
                dp[i][j] = dp[i-1][j];
                tr[i][j] = 0;
                if (j >= li and dp[i][j] < dp[i-1][j-li] + ri) dp[i][j] = dp[i-1][j-li] + ri, tr[i][j] = 1;
            }
        }
        int opt = 0;
        int i = sz(caras);
        for (int j = 0; j < l; ++j) {
            if (dp[i][j] > dp[i][opt]) opt = j;
        }
        for (; i; --i) {
            if (tr[i][opt]) ans[idq].pb(caras[i-1]), opt -= mm[caras[i-1]].li;
        }
        // inicialmente podemos ignorar o mask_used.
        // preciso recuperar a resposta!!!
        // dp[idx][mem_used][mask_used]
        // 10^3 * 2^{X+ki}
        //
    }
    for (int i = 0; i < m; ++i) {
        cout << sz(ans[i]) << ' ';
        for (auto x : ans[i]) cout << x + 1 << ' ';
        cout << endl;
    }
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
