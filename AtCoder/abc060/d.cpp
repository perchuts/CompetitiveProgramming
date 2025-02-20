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
    int n, W; cin >> n >> W;
    vector<int> w(n), v(n);
    for (int i = 0; i < n; ++i) cin >> w[i] >> v[i];
    vector<vector<int>> ps(4);
    for (int i = 0; i < n; ++i) ps[w[i]-w[0]].pb(v[i]);
    for (int i = 0; i < 4; ++i) {
        sort(rbegin(ps[i]), rend(ps[i]));
        for (int j = 1; j < sz(ps[i]); ++j) ps[i][j] += ps[i][j-1];
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) for (int j = 0; j + i <= n; ++j) for (int k = 0; i + j + k <= n; ++k) for (int l = 0; i + j + k + l <= n; ++l) {
        if (i > sz(ps[0])) continue;
        if (j > sz(ps[1])) continue;
        if (k > sz(ps[2])) continue;
        if (l > sz(ps[3])) continue;
        if (i*w[0]+j*(w[0]+1)+k*(w[0]+2)+l*(w[0]+3) > W) continue;
        ckmax(ans, (i?ps[0][i-1]:0) + (j?ps[1][j-1]:0) + (k?ps[2][k-1]:0) + (l?ps[3][l-1]:0));
    }
    cout << ans << endl;

}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
