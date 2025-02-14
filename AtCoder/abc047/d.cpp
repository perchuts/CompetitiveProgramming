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
    int mn = a[0], d = 0;
    map<int, int> exist;
    exist[a[0]] = 1;
    for (int i = 1; i < n; ++i) {
        ckmax(d, a[i] - mn);
        ckmin(mn, a[i]);
    }
    assert(d > 0);
    int ans = 0;
    vector<ii> edg;
    for (int i = 0; i < n; ++i) {
        if (exist[a[i]-d]) edg.pb({a[i]-d, a[i]}), ans++;
        exist[a[i]] = 1;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
