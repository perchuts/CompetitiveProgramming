#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 4e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
    int n, d; cin >> n >> d;
    vector<int> a(n);
    vector<int> occ(3*maxn), vis = occ;
    for (auto& x : a) cin >> x, occ[x]++;
    int ans = 0;
    for (int i = 0; i < 3*maxn; ++i) {
        if (vis[i]) continue;
        if (occ[i] != 0) {
            if (d == 0) {
                ans += occ[i]-1;
                continue;
            }
            int j = i + d;
            int dp2 = 0, dp1 = occ[i];
            while (j < 3 * maxn and occ[j]) {
                vis[j] = true;
                int ndp = occ[j] + min(dp1, dp2);
                dp2 = dp1, dp1 = ndp;
                j += d;
            }
            ans += min(dp2, dp1);
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
