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
    int h, w; cin >> h >> w;
    int n; cin >> n;
    map<int, vector<int>> v;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        v[x].pb(y);
    }
    int ans = 0;
    vector<int> costs;
    vector<int> dp(3);
    dp[1] = dp[2] = 1e18;
    for (auto [x, y] : v) {
        sort(all(y));
        int opt = 2 * (w - y[0]);
        ckmin(opt, 2 * (y.back()-1));
        ans += 2 * (y.back()-1);
        for (int i = 0; i < sz(y)-1; ++i) ckmin(opt, 2*(y[i]-1 + w - y[i+1]));
        vector<int> ndp(3);
        ndp[0] = dp[0] + opt;
        ndp[1] = min({dp[1] + opt, dp[0] + w-1, dp[2] + w-1});
        ndp[2] = min({dp[2] + opt, dp[1] + w-1});
        swap(dp, ndp);
    }
    cout << min(ans, dp[2]) << endl;
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
