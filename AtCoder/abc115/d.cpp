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
    int n, x; cin >> n >> x;
    vector<ii> dp(n+1);
    dp[0] = {1, 1};
    for (int i = 1; i <= n; ++i) {
        dp[i].first = 2*dp[i-1].first + 3;
        dp[i].second = 2*dp[i-1].second + 1;
    }
    int ans = 0;
    for (int i = n; ~i; --i) {
        if (x == dp[i].first) {
            ans += dp[i].second;
            cout << ans << endl;
            exit(0);
        }
        assert(i);
        if (x > dp[i-1].first) {
            ans += dp[i-1].second;
            x -= dp[i-1].first+1;
            if (x == 0) {
                cout << ans << endl;
                exit(0);
            }
            x--;
            ans++;
            if (x == 0) {
                cout << ans << endl;
                exit(0);
            }
        } else {
            x--;
            if (x == 0) {
                cout << ans << endl;
                exit(0);
            }
        }
    }
    assert(false);
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
