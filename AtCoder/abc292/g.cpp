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
    vector<string> a(n);
    for (auto& x : a) cin >> x;
    // solve[l][r][k] = preciso decidir o sufixo [k, M)
    vector dp(n+1, vector(n+1, vector(m+1, vector(11, 0LL))));
    auto add = [] (int& x, int y) {
        y %= mod;
        x += y;
        if (x >= mod) x -= mod;
    };
    for (int l = n-1; ~l; --l) {
        for (int r = l; r < n; ++r) {
            for (int k = m; ~k; --k) {
                for (int d = 9; ~d; --d) {
                    if (k == m) {
                        dp[l][r][k][d] = (l == r);
                        continue;
                    }
                    dp[l][r][k][d] = dp[l][r][k][d+1];
                    for (int s = l; s <= r; ++s) {
                        if (a[s][k] != '?' and a[s][k] != char('0'+d)) break;
                        add(dp[l][r][k][d], dp[l][s][k+1][0]*(s<r?dp[s+1][r][k][d+1]:1));
                    }
                }
            }
        }
    }
    cout << dp[0][n-1][0][0] << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
