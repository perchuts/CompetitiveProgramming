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
    int n, t; cin >> n >> t;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> x1, x2;
    int m = n/2;
    for (int i = 0; i < 1<<m; ++i) {
        int x = 0;
        for (int j = 0; j < m; ++j) if (i >> j & 1) x += a[j];
        x1.pb(x);
    }
    for (int i = 0; i < 1<<(n-m); ++i) {
        int x = 0;
        for (int j = 0; j < n-m; ++j) if (i >> j & 1) x += a[m+j];
        x2.pb(x);
    }
    sort(all(x1)), sort(all(x2));
    x1.erase(unique(all(x1)), end(x1));
    x2.erase(unique(all(x2)), end(x2));
    int j = sz(x2)-1, ans = 0;
    for (int i = 0; i < sz(x1); ++i) {
        while (j >= 0 and x2[j]+x1[i] > t) --j;
        if (j >= 0 and x1[i] + x2[j] <= t) ckmax(ans, x1[i]+x2[j]);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
