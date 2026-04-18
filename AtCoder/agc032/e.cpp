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

void solve() {
    // beleza, vms particionar [2*n] em 2 conjuntos
    // S, T. [i, j] ta em S se e somente se [i, j] eh um par e a[i] + a[j] < M.
    // caso contrario [i, j] \in T.
    // claim: seja i1, ..., i|S| os elementos de S. temos que os pareamentos podem ser [i1, iS], [i2, iS-1], ... . o mesmo pode ser dito para T.
    // prova:
    // se tenho a b c d, e [a,b], [c,d],
    // 					   [a,c], [b,d] <= max do outro q eh [c,d].
    // 				se tenho [a, c], [b, d]
    // 					   [a,c], [b,c] <= max do outro q eh [b, d].
    // ok, vamos tentar encontrar tais S, T de forma que o pareamento satisfaca essa restricao.
    // se tenho a b c d com [a,c], [b,d] e a+c < M, b+d >= M:
    // is it true that max(a+b, c+d-M) <= max(a+c, b+d-M)?
    // a+b <= a+c OK!
    // c+d-M <= a+c OK!
    // then this option is always viable!
    // thus inside a color we have a structure 1 2 3 4 5 ..... 5 4 3 2 1
    // whenever we have RRRRRRRRRBR, we can move this B to the right.
    // then the problem boils down to doing this check for all ranges.
    int n, m; cin >> n >> m;
    vector<int> a(2*n);
    for (auto& x : a) cin >> x;
    sort(all(a));
    auto possible = [&] (int K) {
        int l = 1, r = n, lst_esq = 0, opt_dir = 0;
        while (l <= r) {
            int md = l + (r-l+1)/2, ok = 1;
            for (int i = 1; i <= md; ++i) {
                if (a[i-1] + a[2*md-i] > K) { ok = 0; break; }
            }
            if (ok) lst_esq = md, l = md+1;
            else r = md-1;
        }
        if (lst_esq == n) return true;
        l = n - lst_esq, r = n;
        while (l <= r) {
            int md = l + (r-l+1)/2, ok = 1;
            for (int i = 1; i <= md; ++i) {
                if (a[2*n-i] + a[2*(n-md)+i-1] < m) { ok = 0; break; }
            }
            if (ok) opt_dir = md, l = md+1;
            else r = md-1;
        }
        if (opt_dir == 0) return false;
        for (int i = 1; i <= opt_dir; ++i) {
            if (a[2*n-i] + a[2*(n-opt_dir)+i-1] > m + K) return false;
        }
        return true;
    };
    possible(0);
    int l = 0, r = m-1, ans = r;
    while (l <= r) {
        int md = l + (r-l+1)/2;
        if (possible(md)) ans = md, r = md-1;
        else l = md+1;
    }
    cout << ans << endl;
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
