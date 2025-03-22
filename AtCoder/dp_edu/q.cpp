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
    vector<int> p(n), pp(n), a(n);
    for (auto& x : p) cin >> x;
    for (auto& x : a) cin >> x;
    iota(all(pp), 0);
    sort(all(pp), [&] (int x, int y) { return p[x] < p[y]; });
    vector<int> bit(n+1);
    auto insert = [&] (int x, int k) {
        while (x <= n) ckmax(bit[x], k), x += x & (-x);
    };
    auto query = [&] (int x) {
        int ans = 0;
        while (x) ckmax(ans, bit[x]), x -= x & (-x);
        return ans;
    };
    int ans = 0;
    for (auto x : pp) {
        int my = query(x+1) + a[x];
        insert(x+1, my);
        ckmax(ans, my);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
