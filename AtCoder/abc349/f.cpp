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

void solve(){
    int n, m; cin >> n >> m;
    vector<int> pws;
    int cur = m;
    for (int i = 2; i * i <= m; ++i) {
        if (cur % i) continue;
        int x = 1;
        while (cur % i == 0) cur /= i, x *= i;
        pws.pb(x);
    }
    if (cur != 1) pws.pb(cur);
    int k = sz(pws);
    vector<int> a(n), freq(1<<k);
    int sexo = 0;
    for (auto& x : a) {
        cin >> x;
        if (x == 1) sexo = (2 * sexo + 1) % mod;
        if (m % x) continue;
        int mask = 0;
        for (int i = 0; i < k; ++i) mask += (x % pws[i] ? 0 : (1 << i));
        freq[mask]++;
    }
    if (m == 1) {
        cout << sexo << endl;
        exit(0);
    }
    vector<int> pot(n+1, 1);
    for (int i = 1; i <= n; ++i) pot[i] = 2 * pot[i-1] % mod;
    vector<int> dp(1<<k);
    dp[0] = 1;
    for (int i = 0; i < (1 << k); ++i) {
        if (freq[i] == 0) continue;
        int x = (mod-1+pot[freq[i]]) % mod;
        for (int j = (1 << k) - 1; ~j; --j) {
            dp[j|i] = (dp[j|i] + dp[j] * x) % mod;
        }
    }
    cout << dp.back() << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
