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
    int n, q; cin >> n >> q;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    vector<array<int, 5>> events;
    for (int i = 0; i < q; ++i) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        events.pb({c-1, a, b, i, -1});
        events.pb({d, a, b, i, 1});
    }
    for (int i = 0; i < n; ++i) events.pb({v[i], -1, 0, 0, i});
    sort(all(events));
    vector<int> bit(n+1);
    auto insert = [&] (int x) {
        while (x <= n) bit[x]++, x += x & (-x);
    };
    auto query = [&] (int x) {
        int ans = 0;
        while (x) ans += bit[x], x -= x & (-x);
        return ans;
    };
    auto Query = [&] (int l, int r) {
        return query(r) - query(l-1);
    };
    vector<int> ans(q);
    for (auto [a, b, c, d, e] : events) { 
        if (b == -1) insert(e+1);
        else {
            ans[d] += e * Query(b, c);
        }
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
