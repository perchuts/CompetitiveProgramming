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
    vector<vector<int>> grid(n, vector<int>(m)), ps(n+1, vector<int>(m+1));
    for (auto& x : grid) for (auto& y : x) cin >> y;
    auto get = [&] (int x1, int y1, int x2, int y2) {
        ++x1, ++x2, ++y1, ++y2;
        return ps[x2][y2] - ps[x1-1][y2] - ps[x2][y1-1] + ps[x1-1][y1-1];
    };
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) ps[i][j] = ps[i-1][j] + ps[i][j-1] + grid[i-1][j-1] - ps[i-1][j-1];
    vector<int> cara(n);
    vector<int> lx(n), rx(n);
    vector<ii> ptr(n+1);
    int ans = 0;
    for (int l = 0; l < m; ++l) {
        for (int r = l; r < m; ++r) {
            int h = 0;
            ptr[0] = {-1, 0};
            for (int i = 0; i < n; ++i) {
                if (l == r) cara[i] = grid[i][l];
                else ckmin(cara[i], grid[i][r]);
                while (ptr[h].second >= cara[i]) h--;
                lx[i] = ptr[h].first+1;
                ptr[++h] = {i, cara[i]};
            }
            h = 0;
            ptr[0].first = n;
            for (int i = n-1; ~i; --i) {
                while (ptr[h].second >= cara[i]) h--;
                rx[i] = ptr[h].first-1;
                ptr[++h] = {i, cara[i]};
                ckmax(ans, get(lx[i], l, rx[i], r)*cara[i]);
            }
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

