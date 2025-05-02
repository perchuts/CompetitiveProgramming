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
    int n, m, x, y; cin >> n >> m >> x >> y;
    vector<string> grid(n);
    vector<vector<int>> foi(n, vector<int>(m));
    for (auto& z : grid) cin >> z;
    string t; cin >> t;
    --x, --y;
    vector<ii> mp(256);
    mp['U'] = {-1, 0};
    mp['D'] = {1, 0};
    mp['R'] = {0, 1};
    mp['L'] = {0, -1};
    for (auto c : t) {
        if (grid[x][y] == '@') foi[x][y] = 1;
        auto [dx, dy] = mp[c];
        int x2 = x + dx, y2 = y + dy;
        if (min(x2, y2) >= 0 and x2 != n and y2 != m and grid[x2][y2] != '#') x = x2, y = y2;
        if (grid[x][y] == '@') foi[x][y] = 1;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) ans += foi[i][j];
    cout << x+1 << ' ' << y+1 << ' ';
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
