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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve() {
    int n, m; cin >> m >> n;
    int N = 2*n+m+10;
    vector<int> fat(N, 1), ifat(N);
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    for (int i = 1; i < N; ++i) fat[i] = fat[i-1] * i % mod;
    ifat[N-1] = fexp(fat[N-1], mod-2);
    for (int i = N-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
    int ans = 0;
    for (int D = n; D <= m; ++D) {
        if ((D & 1) != (m & 1)) continue;
        // distribui as diferencas entre os bichos
        int k = D-n;
        int ways = fat[k+2*n-1] * ifat[k] % mod * ifat[2*n-1] % mod;
        // agora falta distribuir pra chegar no m
        int falta = (m-D)/2;
        int ways2 = fat[falta+n-1] * ifat[n-1] % mod * ifat[falta] % mod;
        ans = (ans + ways * ways2) % mod;
    }
    for (int i = 0; i < n; ++i) ans = ans * 2 % mod;
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
