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
    for (auto& x : grid) for (auto& y : x) cin >> y, y %= 2;
    vector<tuple<int, int, int, int>> ans;
    ii achou = {-1, -1};
    for (int i = 0; i < n; ++i) {
        if (i % 2) {
            for (int j = m-1; ~j; --j) {
                if (achou.first != -1 and j != m-1) ans.pb({i, j+1, i, j});
                if (grid[i][j]) {
                    if (achou.first == -1) achou = {i, j};
                    else grid[achou.first][achou.second] = grid[i][j] = 0, achou = {-1, -1};
                }
            }
            if (achou.first != -1 and i != n-1) {
                ans.pb({i, 0, i+1, 0});
            }
        } else {
            for (int j = 0; j < m; ++j) {
                if (achou.first != -1 and j) ans.pb({i, j-1, i, j});
                if (grid[i][j]) {
                    if (achou.first == -1) achou = {i, j};
                    else grid[achou.first][achou.second] = grid[i][j] = 0, achou = {-1, -1};
                }
            }
            if (achou.first != -1 and i != n-1) {
                ans.pb({i, m-1, i+1, m-1});
            }
        }
    }
    cout << sz(ans) << endl;
    for (auto [a, b, c, d] : ans) cout << a+1 << ' ' << b+1 << ' ' << c+1 << ' ' << d+1 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
