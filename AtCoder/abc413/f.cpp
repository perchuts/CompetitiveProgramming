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
    int n, m, k; cin >> n >> m >> k;
    vector<ii> sexo(k);
    vector<vector<int>> grid(n, vector<int>(m)), dist(n, vector<int>(m, inf)), vis = grid;
    for (auto& [x, y] : sexo) cin >> x >> y, --x, --y, grid[x][y] = 1;
    vector<int> a = {1, -1, 0, 0, 0, 0, 1, -1};
    queue<ii> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int tot = 0;
            if (grid[i][j]) q.push({i, j}), dist[i][j] = 0, vis[i][j] = 2;
        }
    }
    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();
        for (int w = 0; w < 4; ++w) {
            int x = i + a[w], y = j + a[w+4];
            if (min(x, y) >= 0 and x < n and y < m and grid[x][y] == 0) {
                if (vis[x][y] == 0) vis[x][y] = 1;
                else if (vis[x][y] == 1) {
                    vis[x][y] = 2;
                    q.push({x, y});
                    dist[x][y] = dist[i][j] + 1;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (dist[i][j] < inf) ans += dist[i][j];
        }
    }
    cout << ans << endl;
}

int32_t main() {_
    int t = 1; //cin >> t;
    while(t--) solve();
}
