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
    int n, m; cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    vector<int> dp(1<<(n*m)), ok(1<<(n*m));
    for (auto& x : grid) for (auto& y : x) cin >> y, dp[0] ^= y;
    int ans = dp[0]; ok[0] = 1;
    auto get = [&] (int x, int y) { return m*x+y; };
    for (int i = 1; i < (1 << n*m); ++i) {
        for (int j = 0; j < n*m; ++j) {
            if (i >> j & 1) {
                int x1 = j / m, y1 = j % m;
                if (y1 < m-1) {
                    int k = get(x1, y1+1);
                    int sexo = i-(1<<k)-(1<<j);
                    if ((i >> k & 1) and ok[sexo]) {
                        dp[i] = dp[sexo] ^ grid[x1][y1] ^ grid[x1][y1+1];
                        ok[i] = 1;
                    }
                }
                if (x1 < n-1) {
                    int k = get(x1+1, y1);
                    int sexo = i-(1<<k)-(1<<j);
                    if ((i >> k & 1) and ok[sexo]) {
                        dp[i] = dp[sexo] ^ grid[x1+1][y1] ^ grid[x1][y1];
                        ok[i] = 1;
                    }
                }
                if (ok[i]) ckmax(ans, dp[i]);
            }
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
