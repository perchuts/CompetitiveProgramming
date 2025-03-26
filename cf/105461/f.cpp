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
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    vector<int> dp(5001, -1e18);
    dp[5000] = 0;
    int mn = 5000, S = 0;
    for (int i = 1; i <= n; ++i) {
        S += v[i-1];
        vector<int> ndp(5001);
        for (int j = 1; j <= 5000; ++j) {
            // colocar no outro lugar
            ndp[j] = dp[j] + min(v[i-1], mn);
            if (v[i-1] >= j) ckmax(ndp[j], dp[j] + min(v[i-1], j));
        }
        // agora vamos recalcular eu mesmo
        for (int j = v[i-1]+1; j <= 5000; ++j) ckmax(ndp[v[i-1]], dp[j] + v[i-1]);
        ckmin(mn, v[i-1]);
        swap(ndp, dp);
    }
    cout << S - *max_element(all(dp)) << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
