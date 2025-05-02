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
    int n, k; cin >> n >> k;
    if (n == 1) {
        cout << 1 << endl;
        exit(0);
    }
    vector<int> val;
    for (int i = 1; i * i <= n; ++i) val.pb(i);
    int cur = val.back()+1;
    vector<ii> intr;
    while (cur <= n) {
        int l = cur, r = n, ans = cur;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (n/md == n/cur) ans = md, l = md+1;
            else r = md-1;
        }
        intr.pb({cur, ans});
        cur = ans+1;
    }
    int N = sz(val), M = sz(intr);
    vector<int> dp1(N), dp2(M), lim(N, M-1);
    for (int i = 1; i < N; ++i) {
        lim[i] = lim[i-1];
        while (lim[i] >= 0 and (i+1)*intr[lim[i]].first > n) lim[i]--;
    }
    iota(all(dp1), 1);
    for (int i = 0; i < M; ++i) dp2[i] = intr[i].second-intr[i].first+1+(i?dp2[i-1]:0);
    for (int __ = 2; __ <= k; ++__) {
        vector<int> ndp1(N, dp1.back()), ndp2(M);
        for (int i = 0; i < N; ++i) {
            if (lim[i] >= 0) ndp1[i] = (ndp1[i] + dp2[lim[i]]) % mod;
        }
        for (int i = 0; i < M; ++i) ndp2[i] = dp1[n/intr[i].first-1]*(intr[i].second-intr[i].first+1) % mod;
        for (int i = 1; i < N; ++i) ndp1[i] = (ndp1[i] + ndp1[i-1]) % mod;
        for (int i = 1; i < M; ++i) ndp2[i] = (ndp2[i] + ndp2[i-1]) % mod;
        swap(dp1, ndp1), swap(dp2, ndp2);
    }
    cout << (dp1.back() + dp2.back()) % mod << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
