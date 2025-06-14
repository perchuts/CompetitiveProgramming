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
    queue<ii> q;
    vector<vector<int>> dist(n, vector<int>(m, inf));
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'E') q.push({i, j}), dist[i][j] = 0;
        }
    }
    int a[] = {1, -1, 0, 0, 0, 0, 1, -1};
    vector<char> dirs = {'^', 'v', '<', '>'};
    auto ans = grid;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int x2 = x + a[i], y2 = y + a[i+4];
            if (min(x2, y2) < 0 or x2 == n or y2 == m or grid[x2][y2] != '.' or dist[x2][y2] == 0) continue;
            dist[x2][y2] = 0;
            ans[x2][y2] = dirs[i];
            q.push({x2, y2});
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << ans[i][j];
        }
        cout << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
