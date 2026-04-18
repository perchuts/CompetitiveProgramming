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
    for (int i = 1; i < n; ++i) if (a[i] % 6 != a[0] % 6) {
        cout << -1 << endl;
        return;
    }
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
    int ans = 1e18, ok = 0;
    const int lim = 10;
    vector<int> p6(lim, 1), p7(lim, 1);
    for (int i = 1; i < lim; ++i) p6[i] = 6 * p6[i-1], p7[i] = 7 * p7[i-1];
    auto rec = [&] (auto&& self, int pot, vector<int> v) -> int {
        int m6 = v[0] % p6[pot];
        bool nice = 1;
        int add = (p6[pot] - m6) % p6[pot];
        for (auto& x : v) nice &= (m6 == x % p6[pot]), x += add;
        if (!nice) return -1;
        map<int, vector<int>> cc;
        for (auto x : v) cc[x%p7[pot]].pb(x);
        if (cc.size() == p7[pot]) {
            for (int i = 0; i < p7[pot]; ++i) if (!cc.count(i)) return (p7[pot]-i)*p6[pot] + m6;
        }
        int opt = -1;
        // vamos supor entao que eu some i * p6[pot]. quem que vai se fuder?
        // o cara que eh congruente a -i 6^k  mod 7^k.
        // eu preciso somar algo congruente a bicho modulo 7^k. entao pegando a solucao de 1 passo a frente, 
        // ela vai ser congruente a x * 6^k mod 6^{k+1}.
        for (int i = 0; i < p7[pot]; ++i) {
            int bicho = (p7[pot] - (i * p6[pot]) % p7[pot]) % p7[pot];
            int k = self(self, pot+1, cc[bicho]);
            if (k == -1) continue;

        }
        return opt;
    };
    rec(rec, 1, a);
    cout << (ok ? ans : -1) << endl;
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
