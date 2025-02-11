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
    int n, x; cin >> n >> x;
    vector<int> p(n), c(n);
    for (int i = 0; i < n; ++i) cin >> p[i] >> c[i];
    int ans = 1e18;
    for (int i = 0; i < (1 << n); ++i) {
        int score = 0, qnt = 0;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) score += p[j] * 100 * (j+1) + c[j], qnt += p[j];
        }
        for (int j = n-1; ~j; --j) {
            if (i >> j & 1) continue;
            for (int k = 0; k < p[j]; ++k) {
                if (score < x) score += (j+1) * 100, qnt++;
            }
        }
        if (score >= x) ckmin(ans, qnt);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
