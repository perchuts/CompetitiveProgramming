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
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    vector<vector<int>> vis(n, vector<int>(m));
    int a[] = {1, -1, 0, 0, 0, 0, 1, -1};
    auto dfs = [&] (auto&& self, int i, int j) -> int {
        vis[i][j] = 1;
        int ans = 1;
        for (int k = 0; k < 4; ++k) {
            int x2 = i + a[k], y2 = j + a[k+4];
            if (min(x2, y2) < 0 or x2 >= n or y2 >= m) continue;
            if (vis[x2][y2] == 0 and grid[x2][y2] == '#') ans += self(self, x2, y2);
        }
        return ans;
    };
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        if (!vis[i][j] and grid[i][j] == '#') {
            if (dfs(dfs, i, j) == 1) {
                cout << "No" << endl;
                exit(0);
            }
        }
    }
    cout << "Yes" << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
