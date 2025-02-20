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
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    
    ii best = {-1, -1}, best2 = {1, -1};
    for (int i = 0; i < n; ++i) {
        if (a[i] > 0) ckmax(best, pair(a[i], i));
        else if (a[i] < 0) ckmin(best2, pair(a[i], i));
    }
    if (best.first == -1 and best2.first == 1) {
        cout << 0 << endl;
        exit(0);
    }
    vector<ii> ops;
    if (abs(best.first) >= abs(best2.first)) {
        for (int i = 0; i < n; ++i) ops.pb({i, best.second});
        for (int i = 1; i < n; ++i) ops.pb({i, i-1});
    } else {
        for (int i = 0; i < n; ++i) ops.pb({i, best2.second});
        for (int i = n-2; ~i; --i) ops.pb({i, i+1});
    }
    cout << sz(ops) << endl;
    for (auto [x, y] : ops) cout << y+1 << ' ' << x+1 << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
