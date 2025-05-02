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
    vector<int> primes;
    const int lim = 73;
    for (int i = 2; i < lim; ++i) {
        bool ok = 1;
        for (int j = 2; j*j <= i; ++j) ok &= (i % j != 0);
        if (ok) primes.pb(i);
    }
    int n = sz(primes), a, b; cin >> a >> b;
    int cnt = 0;
    vector<int> mask(b-a+1);
    for (int i = a; i <= b; ++i) {
        for (int j = 0; j < n; ++j) if (i % primes[j] == 0) mask[i-a] += 1 << j;
        if (mask[i-a] == 0) cnt++;
    }
    vector<int> ways(1<<n);
    ways[0] = (1<<cnt);
    int ans = ways[0];
    for (int i = 1; i < (1<<n); ++i) {
        for (auto x : mask) {
            if ((x & i) == x and ((x&i&(-i)) == (i&(-i)))) ways[i] += ways[i-x];
        }
        ans += ways[i];
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
