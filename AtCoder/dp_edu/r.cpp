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
    int n, k; cin >> n >> k;
    vector<vector<int>> m(n, vector<int>(n));
    for (auto& x : m) for (auto& y : x) cin >> y;
    auto fexp = [&] (vector<vector<int>> mat, int e) {
        vector<vector<int>> ans(n, vector<int>(n));
        for (int i = 0; i < n; ++i) ans[i][i] = 1;
        while (e) {
            if (e&1) {
                vector<vector<int>> m2(n, vector<int>(n));
                for (int k = 0; k < n; ++k) {
                    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
                        m2[i][j] = (m2[i][j] + ans[i][k] * mat[k][j]) % mod;
                    }
                }
                ans = m2;
            }
            vector<vector<int>> m2(n, vector<int>(n));
            for (int k = 0; k < n; ++k) {
                for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
                    m2[i][j] = (m2[i][j] + mat[i][k] * mat[k][j]) % mod;
                }
            }
            mat = m2;
            e /= 2;
        }
        return ans;
    };
    m = fexp(m, k);
    int ans = 0;
    for (auto x : m) for (auto y : x) ans = (ans + y) % mod;
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
