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
	int n; cin >> n;
    if (n == 1) {
        cout << 2 << endl;
        exit(0);
    }
    auto mult = [&] (vector<vector<int>> a, vector<vector<int>> b) {
        int m = sz(a);
        vector<vector<int>> c(m, vector<int>(m));
        for (int i = 0; i < m; ++i) for (int j = 0; j < m; ++j) for (int k = 0; k < m; ++k) {
            c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
        }
        return c;
    };
    vector<vector<int>> m = {{1, 1}, {1, 0}};
    vector<vector<int>> a = {{1, 0}, {0, 1}};
    int b = 2, pot = 4, e = n-1;
    while (e) {
        if (e&1) pot = pot * b % mod, a = mult(a, m); 
        m = mult(m, m);
        b = b * b % mod;
        e /= 2;
    }
    int fn = (a[0][0] + a[0][1]) % mod;
    int ans = (4 * fn - n - 3) % mod; ans = (ans + mod) % mod; ans = ans * pot % mod;
    cout << ans << endl;
}
int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
