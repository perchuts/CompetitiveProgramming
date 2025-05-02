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

const int inf = 1e9+1;
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
    vector<vector<int>> h(n, vector<int>(n));
    for (auto& x : h) for (auto& y : x) cin >> y;
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    int ans = 0;
    for (int __ = 0; __ < 2; ++__) {
         vector<int> dp = {0, a[0]};
        for (int i = 1; i < n; ++i) {
            // colocar aqui
            vector<int> ndp = {inf*inf, inf*inf};
            for (int a1 = 0; a1 < 2; ++a1) for (int b1 = 0; b1 < 2; ++b1) {
                bool ok = 1;
                for (int j = 0; j < n; ++j) {
                    if (__ == 0) ok &= (h[i][j]+a1 != h[i-1][j]+b1);
                    else ok &= (h[j][i]+a1 != h[j][i-1]+b1);
                }
                int cost = dp[b1] + (a1 ? a[i] : 0);
                if (ok) ckmin(ndp[a1], cost);
            }
            swap(dp, ndp);
        }
        ans += min(dp[0], dp[1]);
        swap(a, b);
    }
    cout << (ans >= 1e18 ? -1 : ans) << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
