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
    int n; cin >> n;
    vector<vector<int>> div(n+1);
    vector<int> meb(n+1), fp(n+1), sqf(n+1);
    for (int i = 1; i <= n; ++i) {
        if (i > 1 and fp[i] == 0) fp[i] = i;
        for (int j = i; j <= n; j += i) {
            div[j].pb(i);
            if (fp[i] == i and fp[j] == 0) fp[j] = i;
        }
        if (i == 1) meb[i] = 1, sqf[i] = i;
        else if (fp[i] == i) meb[i] = -1, sqf[i] = i;
        else if (fp[i/fp[i]] == fp[i]) meb[i] = 0, sqf[i] = sqf[i/fp[i]];
        else meb[i] = -1 * meb[i/fp[i]], sqf[i] = fp[i] * sqf[i/fp[i]];
    }
    vector<int> s(n+1), a(n);
    for (auto& x : a) cin >> x;
    for (auto d : div[a[0]]) s[d] = a[0];
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    vector<int> fat(n+1, 1), inv(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1] % mod;
    int x = fexp(fat[n], mod-2);
    for (int i = n; i; --i) inv[i] = x * fat[i-1] % mod, x = x * i % mod;
    for (int v = 1; v < n; ++v) {
        int eu = a[v], ans = 0;
        for (auto d : div[eu]) {
            int z = sqf[eu/d], tot = 0;
            for (auto d2 : div[z]) tot = (tot + meb[d2] * s[d*d2] + mod) % mod;
            ans = (ans + tot * eu % mod * inv[d]) % mod;
        }
        cout << ans << endl;
        for (auto d : div[eu]) s[d] = (s[d] + ans * eu) % mod;
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
