#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
//#define int ll

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
    for (auto& x : grid) {
        string s; cin >> s;
        for (int i = 0; i < m; ++i) x[i] = (s[i] == '#' ? 1 : -1);
    }
    if (n < m) {
        vector<vector<int>> g2(m, vector<int>(n));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) g2[j][i] = grid[i][j];
        swap(n, m);
        swap(g2, grid);
    }
    vector<vector<int>> ps(n, vector<int>(m+1));
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) ps[i][j] = ps[i][j-1] + grid[i][j-1];
    }
    int shift = n*m;
    vector<int> cnt(2*n*m+10);
    ll ans = 0;
    for (int l = 0; l < m; ++l) {
        for (int r = l; r < m; ++r) {
            int tot = 0;
            cnt[shift] = 1;
            for (int i = 0; i < n; ++i) {
                tot += ps[i][r+1] - ps[i][l];
                ans += cnt[tot+shift];
                cnt[tot+shift]++;
            }
            tot = 0;
            for (int i = 0; i < n; ++i) {
                tot += ps[i][r+1] - ps[i][l];
                cnt[tot+shift]--;
            }
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; cin >> t;
    while(t--) solve();
}
