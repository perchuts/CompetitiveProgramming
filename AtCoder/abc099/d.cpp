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
    int n, c; cin >> n >> c;
    vector<vector<int>> d(c, vector<int>(c)), grid(n, vector<int>(n));
    for (auto& x : d) for (auto& y : x) cin >> y;
    for (auto& x : grid) for (auto& y : x) cin >> y, --y;
    vector<vector<int>> cost(3, vector<int>(c));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) for (int k = 0; k < c; ++k) {
        cost[(i+j)%3][k] += d[grid[i][j]][k];
    }
    int ans = 1e18;
    for (int i = 0; i < c; ++i) for (int j = 0; j < c; ++j) for (int k = 0; k < c; ++k) {
        if (i == j or j == k or i == k) continue;
        ckmin(ans, cost[0][i] + cost[1][j] + cost[2][k]);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
