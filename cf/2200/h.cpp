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
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    sort(all(a)); a.erase(unique(all(a)), end(a));
    // v_6(a[i] + C) > v_7(a[i] + C)
    // de um bound para C.
    // se C > max(a[i])
    // C = x_i * a[i] + y_i
    // a[i] -> (x_i+1) a[i] + y_i
    // assuma todo a[i] multiplo de 6.
    // 6 congruente a -1 mod 7. se existe p tal que todo a[i] != p mod 7, basta somarmos (7-p)*6 a todo numero.
    // entao a[i] eh um sistema completo de residuos modulo 7, significando que pra pelo menos um bicho, vamos ter que ir ate uma potencia superior de 6.
    // 6*q, onde q === k mod 7.
    // entao todo bicho congruente a -q mod 7 vai ter que ser observado de perto.
    // entao agora quero pegar o mod 36 desses bichos.
    // se o mod 36 desses bichos for diferente pra algum deles, fiz o L supremo, eles nao vao servir.
    // entao temos uma nova lista de numeros b, onde todo numero b eh congruente a k mod 7, e vou fazer uma operacao de somar 6*q, onde q === k mod 7.
    // b[i] = 7x + k1
    // b[i] = 36y + k2
    // q = 7x + k
    // 42x + 6k
    const int lim = 10;
    vector<int> p6(lim, 1), p7(lim, 1);
    for (int i = 1; i < lim; ++i) p6[i] = 6 * p6[i-1], p7[i] = 7 * p7[i-1];
    auto rec = [&] (auto&& self, vector<int> v) -> int {
        if (v.empty()) return 0LL;
        int m6 = v[0] % 6;
        bool nice = 1;
        int add6 = (6 - m6) % 6;
        for (auto& x : v) nice &= (m6 == x % 6), x += add6;
        if (!nice) return -1;
        vector<vector<int>> cc(7);
        for (auto x : v) cc[x%7].pb(x);
        if (cc[0].empty()) return add6;
        int opt = -1;
        for (int i = 0; i < 7; ++i) {
            int add = 6 * i;
            for (auto& x : cc[i]) x += add, assert(x % 42 == 0), x /= 42;
            int k = self(self, cc[i]);
            if (k == -1) continue;
            int real = add6 + add + 42 * k;
            if (opt == -1) opt = real;
            else ckmin(opt, real);
        }
        return opt;
    };
    cout << rec(rec, a) << endl;
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
