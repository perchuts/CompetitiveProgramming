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

void solve(){
    int n, m; cin >> n >> m;
    vector<vector<int>> a(8), b(8);
    for (int i = 4; i <= 3*n+m; ++i) a[i%8].pb(i);
    for (int i = 4; i <= 3*m+n; ++i) b[i%8].pb(i);
    vector<ii> ans;
    for (int u = 0; u < 8; ++u) {
        int v = 3 * u % 8;
        int i = 0, j = 0;
        while (i < sz(a[u]) and j < sz(b[v])) {
            int x = (3*a[u][i]-b[v][j])/8;
            int y = (3*b[v][j]-a[u][i])/8;
            if (x < 1 or n < x) j++;
            else if (y < 1 or m < y) i++;
            else ans.pb({x, y}), i++, j++;
        }
    }
    cout << sz(ans) << endl;
    for (auto [x, y] : ans) cout << x << ' ' << y << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
