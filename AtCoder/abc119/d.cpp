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

const int inf = 1e18;
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
    vector<set<int>> sx(2);
    for (int i = 0; i < n+m; ++i) {
        int x; cin >> x;
        sx[i<n].insert(x);
    }
    auto get_nxt = [&] (int i, int x) {
        auto it = sx[i].lower_bound(x);
        if (it == end(sx[i])) return inf;
        return *it;
    };
    auto get_prev = [&] (int i, int x) {
        auto it = sx[i].upper_bound(x);
        if (it == begin(sx[i])) return inf;
        return *prev(it);
    };
    while (q--) {
        // ambos pra frente
        int x; cin >> x;
        int ans = inf;
        int p0 = get_prev(0, x), p1 = get_prev(1, x);
        int n0 = get_nxt(0, x), n1 = get_nxt(1, x);
        if (n0 < inf and n1 < inf) ckmin(ans, abs(x-max(get_nxt(0, x), get_nxt(1, x))));
        if (p0 < inf and p1 < inf) ckmin(ans, abs(x-min(get_prev(0, x), get_prev(1, x))));
        if (n0 < inf and p1 < inf) ckmin(ans, abs(n0-p1) + min(abs(x-n0), abs(x-p1)));
        if (n1 < inf and p0 < inf) ckmin(ans, abs(n1-p0) + min(abs(x-n1), abs(x-p0)));
        cout << ans << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
