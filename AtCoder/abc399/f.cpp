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
const int mod = (119<<23)+1;
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
    vector<int> a(n), ss(k+1, 0);
    ss[0] = 1;
    for (auto& x : a) cin >> x;
    int ps = 0;
    vector<vector<int>> ncr(k+1, vector<int>(k+1));
    for (int i = 0; i <= k; ++i) for (int j = 0; j <= i; ++j) {
        if (i == j or j == 0) ncr[i][j] = 1;
        else ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ps = (ps + a[i]) % mod;
        int pot = 1;
        int x = 0;
        for (int j = 0; j <= k; ++j) {
            x = (x + pot * ss[k-j] % mod * ncr[k][j]) % mod;
            pot = pot * ps % mod;
        }
        ans = (ans + x) % mod;
        pot = 1;
        for (int j = 0; j <= k; ++j) {
            ss[j] = (ss[j] + (j % 2 ? mod - pot : pot)) % mod;
            pot = pot * ps % mod;
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
