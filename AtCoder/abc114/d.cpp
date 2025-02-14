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

void solve(){
    int n; cin >> n;
    // 3 * 5 * 5
    // p^2 * q^4 * r^6
    // p, q, r primes
    vector<int> cnt(101), primes;
    for (int i = 2; i <= n; ++i) {
        bool ok = 1;
        for (int j = 2; j < i; ++j) ok &= (i % j != 0); 
        if (ok) primes.pb(i);
    }
    int m = sz(primes);
    for (int i = 2; i <= n; ++i) {
        for (auto x : primes) {
            int temp = i;
            while (temp % x == 0) cnt[x]++, temp /= x;
        }
    }
    int ans = 0;
    for (int i = 0; i < m; ++i) for (int j = 0; j < m; ++j) for (int k = j+1; k < m; ++k) {
        if (i == j or j == k or i == k) continue;
        if (cnt[primes[i]] >= 2 and cnt[primes[j]] >= 4 and cnt[primes[k]] >= 4) ans++;
    }
    for (int i = 0; i < m; ++i) for (int j = 0; j < m; ++j) {
        if (i == j) continue;
        if (cnt[primes[i]] >= 24 and cnt[primes[j]] >= 2) ans++;
        if (cnt[primes[i]] >= 14 and cnt[primes[j]] >= 4) ans++;
    }
    for (int i = 0; i < m; ++i) if (cnt[primes[i]] >= 74) ans++;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
