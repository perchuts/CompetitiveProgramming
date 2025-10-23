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
    const int sexo = 2e5 + 69;
    //const int sexo = 9;
    vector<int> mi(sexo), smol(sexo), f(sexo), freq(sexo), sf(sexo); mi[1] = f[1] = 1;
    for (int i = 2; i < sexo; ++i) {
        if (smol[i] == 0) smol[i] = i;
        
        if (f[i/smol[i]] % smol[i]) f[i] = f[i/smol[i]] * smol[i];
        else f[i] = f[i/smol[i]] / smol[i];

        if (smol[i] != i) continue;
        for (int j = i * i; j < sexo; j += i) {
            if (smol[j] == 0) smol[j] = i;
        }
    }
    for (int i = 2; i < sexo; ++i) {
        if (smol[i] == i) { mi[i] = -1; continue; }
        for (int j = 2; ; ++j) {
            if (i % j == 0) {
                if (i % (j*j) == 0) mi[i] = 0;
                else mi[i] = -1 * mi[i/j];
                break;
            }
        }
    }
    for (int i = 0, x; i < n; ++i) cin >> x, freq[x]++;
    int ans = 0;

    int inv2 = (mod+1)/2;
    for (int g = 1; g < sexo; ++g) {
        int tot = 0;
        for (int i = g; i < sexo; i += g) {
            sf[i] = 0;
            for (int j = i; j < sexo; j += i) sf[i] = (sf[i] + freq[j] * f[j/g]) % mod;
            tot = (tot + mod + mi[i/g] * sf[i] * sf[i]) % mod;
        }
        tot = (tot - freq[g] + mod) % mod;
        tot = tot * inv2 % mod;
        ans = (ans + tot) % mod;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
