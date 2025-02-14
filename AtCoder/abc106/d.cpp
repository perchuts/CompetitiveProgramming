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
    int n, m, q; cin >> n >> m >> q;
    vector<tuple<int,int,int,int>> ev;
    for (int i = 1; i <= m; ++i) { 
        int l, r; cin >> l >> r;
        ev.pb({l, 1, r, 0});
    }
    vector<int> ans(q);
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r;
        ev.pb({l, 0, r, i});
    }
    sort(all(ev));
    reverse(all(ev));
    vector<int> bit(n+10);
    auto insert = [&] (int x, int k) {
        while (x <= n+9) bit[x] += k, x += x & (-x);
    };
    auto query = [&] (int x) {
        int ans = 0;
        while (x) ans += bit[x], x -= x & (-x);
        return ans;
    };
    for (auto [cc, type, x, y] : ev) {
        if (type == 1) {
            insert(x, 1);
        } else { 
            ans[y] = query(x);
        }
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
