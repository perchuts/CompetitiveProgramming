#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int alpha = 26;

int solve(int n, int l, vector<string> ss) {
    vector tr(n, vector(10, vector(26, array<int, 3>())));
    auto kmp = [] (string s) {
        int n = sz(s);
        vector<int> pi(n);
        for (int i = 1, j = 0; i < n; ++i) {
            while (j and s[j] != s[i]) j = pi[j-1];
            if (s[j] == s[i]) j++;
            pi[i] = j;
        }
        return pi;
    };
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < sz(ss[i]); ++j) {
            bool rep = 0;
            for (int k = 0; k < i; ++k) {
                bool ok = 1;
                if (sz(ss[k]) <= j) continue;
                for (int w = 0; w < j; ++w) ok &= (ss[i][w] == ss[k][w]);
                if (ok) { rep = 1; break; }
            }
            string sexo;
            for (int w = 0; w < j; ++w) sexo += ss[i][w];
            for (char prox = 'a'; prox <= char('a'+alpha-1); ++prox) {
                if (rep == 1) {
                    tr[i][j][prox-'a'] = {-1, 0, 0};
                    continue;
                }
                sexo += prox;
                // achar maior sufixo prefixo da string (incluindo ela inteira!)
                vector<int> tam(n);
                int m = 0, tt = -1, quem;
                for (int w = 0; w < n; ++w) {
                    string z = ss[w] + "#" + sexo;
                    auto pi = kmp(z);
                    int novo = pi.back();
                    if (novo == sz(ss[w])) {
                        m += (1 << w);
                        novo = pi[sz(ss[w])-1];
                    }
                    if (ckmax(tt, novo)) quem = w;
                }
                tr[i][j][prox-'a'] = {quem, tt, m};
                sexo.pop_back();
            }
        }
    }
    // (mask, tamanho, tamanho do maior match proprio, quem eh esse maior match)
    // 256 * 100 * 10 * 8 * 26 * O(1)
    // devo tomar cuidado para em caso de multiplas strings terem um prefixo em comum, eu apontar pra de menor indice!
    // entao quero basicamente computar isso: dado (3o valor, 4o valor, letra), pra onde eu vou adicionando essa letra. preciso dizer tbm quem foi ocorrido depois de eu ter adicionado essa letra
    vector dp(1<<n, vector(n, vector(10, 0LL)));
    dp[0][0][0] = 1;
    for (int t = 1; t <= l; ++t) {
        vector ndp(1<<n, vector(n, vector(10, 0LL)));
        for (int mask = 0; mask < (1 << n); ++mask) {
            for (int cara = 0; cara < n; ++cara) {
                for (int tt = 0; tt < sz(ss[cara]); ++tt) {
                    if (tr[cara][tt][0][0] == -1) continue;
                    for (int add = 0; add < alpha; ++add) {
                        int nc = tr[cara][tt][add][0], nt = tr[cara][tt][add][1], nm = mask | tr[cara][tt][add][2];
                        ndp[nm][nc][nt] += dp[mask][cara][tt];
                        if (ndp[nm][nc][nt] >= mod) ndp[nm][nc][nt] -= mod;
                    }
                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < 10; ++j) ans += dp.back()[i][j];
    ans %= mod;
    return ans;
}

int brute(int n, int l, vector<string> ss) {
    string sexo;
    auto kmp = [] (string s) {
        int n = sz(s);
        vector<int> pi(n);
        for (int i = 1, j = 0; i < n; ++i) {
            while (j and s[j] != s[i]) j = pi[j-1];
            if (s[j] == s[i]) j++;
            pi[i] = j;
        }
        return pi;
    };
    int ans = 0;
    auto go = [&] (auto&& self) -> void {
        if (sz(sexo) == l) {
            int cnt = 0;
            for (int i = 0; i < n; ++i) {
                string uepa = ss[i] + "#" + sexo;
                bool foi = 0;
                auto pi = kmp(uepa);
                for (int j = sz(ss[i])+1; j < sz(uepa); ++j) foi |= (pi[j] == sz(ss[i]));
                cnt += foi;
            }
            ans += (cnt == n);
            return;
        }
        for (char c = 'a'; c <= char('a'+alpha-1); ++c) {
            sexo += c;
            self(self);
            sexo.pop_back();
        }
    };
    go(go);
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) {
		int n, l; cin >> n >> l;
		vector<string> ss(n);
		for (auto& x : ss) cin >> x;
		cout << solve(n, l, ss) << endl;
	}
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 3), l = rnd(1, 5);
        vector<string> ss(n);
        for (auto& x : ss) {
            int tam = rnd(1, min(5LL, l));
            for (int j = 0; j < tam; ++j) x += char('a' + rnd(0, alpha-1));
        }
        bool bad = 0;
        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) bad |= (ss[i] == ss[j]);
        if (bad) continue;
        int my = solve(n, l, ss), ans = brute(n, l, ss);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << l << endl;
            for (auto x : ss) cout << x << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
