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
    int x; cin >> x;
    int ans = 1;
    auto get = [&] (int k, int add = -1) {
        vector<int> repr;
        while (k) repr.pb(k&1), k /= 2;
        reverse(all(repr));
        auto ans = repr;
        if (add != -1) ans.pb(add);
        for (int i = sz(repr)-1; ~i; --i) ans.pb(repr[i]);
        int cara = 0, pw = 1;
        reverse(all(ans));
        for (auto x : ans) cara += x * pw, pw += pw;
        return cara;
    };
    for (int i = -1; i <= 1; ++i) {
        int l = 1, r = (1LL<<30);
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (get(md, i) <= x) ckmax(ans, get(md, i)), l = md+1;
            else r = md-1;
        }
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
