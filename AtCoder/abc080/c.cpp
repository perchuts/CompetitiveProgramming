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
    int n; cin >> n;
    vector<vector<int>> f(n, vector<int>(10));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 5; ++j) for (int k = 0; k < 2; ++k) cin >> f[i][2*j+k];
    }
    vector<vector<int>> p(n, vector<int>(11));
    for (auto& x : p) for (auto& y : x) cin >> y;
    int ans = -1e18;
    for (int i = 1; i < (1 << 10); ++i) {
        vector<int> qnt(n);
        for (int j = 0; j < 10; ++j) {
            if (i >> j & 1) {
                for (int k = 0; k < n; ++k) {
                    if (f[k][j]) qnt[k]++;
                }
            }
        }
        int cur = 0;
        for (int j = 0; j < n; ++j) cur += p[j][qnt[j]];
        ckmax(ans, cur);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
