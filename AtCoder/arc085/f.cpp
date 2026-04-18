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

const int inf = 1e6+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// SegTree Persistente
//
// SegTree de soma, update de somar numa posicao
//
// query(a, b, t) retorna a query de [a, b] na versao t
// update(a, x, t) faz um update v[a]+=x a partir da
// versao de t, criando uma nova versao e retornando seu id
// Por default, faz o update a partir da ultima versao
//
// build - O(n)
// query - O(log(n))
// update - O(log(n))

const int MAX = 3e5+10;

namespace seg {

ll seg[4*MAX];
int n;

ll build(int p=1, int l=0, int r=n-1) {
    if (l == r) return seg[p] = inf;
    int m = (l+r)/2;
    return seg[p] = min(build(2*p, l, m), build(2*p+1, m+1, r));
}

void buildd(int n2) {
    n = n2;
    build();
}
ll query(int a, int b, int p=1, int l=0, int r=n-1) {
    if (a <= l and r <= b) return seg[p];
    if (b < l or r < a) return inf;
    int m = (l+r)/2;
    return min(query(a, b, 2*p, l, m), query(a, b, 2*p+1, m+1, r));
}
ll update(int a, int b, int x, int p=1, int l=0, int r=n-1) {
    if (a <= l and r <= b) {
        ckmin(seg[p], x);
        return seg[p];
    }
    if (b < l or r < a) return seg[p];
    int m = (l+r)/2;
    return seg[p] = min(update(a, b, x, 2*p, l, m),
    update(a, b, x, 2*p+1, m+1, r));
}
};

void solve() {
    int n; cin >> n;
    vector<int> b(n+1);
         for (int i = 1; i <= n; ++i) cin >> b[i];
    vector<vector<int>> op(n+1);
    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r;
        op[r].pb(l);
    }
    vector<int> dp(n+1), qt0(n+1);
    seg::buildd(n+1);
    seg::update(0, 0, 0);
    for (int i = 1; i <= n; ++i) {
        qt0[i] = qt0[i-1] + (b[i] == 0);
        int opt = dp[i-1] + b[i];
        // agora vamos trabalhar nos updates
        // pra cada update, podemos setar tudo ali pra 1.
        // se o segmento eh [j, i], o proximo segmento pode ser qualquer coisa comecando no maximo em j-1.
        // tem que comecar em qualquer ponto a partir de j-1.
        // transicao valida: qt0[i] + dp[K] - qt0[pos]
        // devo inserir dp[K] - qt0[pos]
        vector<int> opts;
        for (auto j : op[i]) {
            opts.pb(qt0[i] + seg::query(j-1, i));
        }
        for (int j = 0; j < sz(opts); ++j) {
            int l = op[i][j];
            ckmin(opt, opts[j]);
        }
        cout << "updating point " << i << " at root " << i << " to " << opt-qt0[i] << endl;
        seg::update(i, i, opt - qt0[i]);
        dp[i] = opt;
        //cout << dp[i] << " ";
    }
    //cout << endl;
    cout << dp[n] << endl;
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
