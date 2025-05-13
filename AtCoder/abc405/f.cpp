#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll


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
    int n, m; cin >> n >> m;
    vector<ii> edg(m);
    for (auto& [x, y] : edg) cin >> x >> y;
    int q; cin >> q;
    vector<ii> qu(q);
    for (auto& [x, y] : qu) cin >> x >> y;
    // (a, b) == query
    // (x, y) == aresta
    // a < b, x < y
    // pra ter intersecao, vamos ter:
    vector<ii> ev;
    int aa = 0;
    for (auto [x, y] : edg) {
        ev.pb({max(x, y), q+aa});
        ev.pb({min(x, y), inf});
        aa++;
    }
    for (int i = 0; i < q; ++i) ev.pb({max(qu[i].first, qu[i].second), i});
    sort(all(ev));
    vector<int> pts(2*n+5), ans(q);
    ord_set<int> s;
    int ptr = 0, cur = 0, tot = 0;
    for (auto [cc, id] : ev) {
        while (ptr != cc) pts[ptr++] = tot;
        if (id >= q) {
            pts[ptr] = ++tot;
            if (id != inf) s.insert(min(edg[id-q].first, edg[id-q].second));
        }
        else {
            int inside = (tot - pts[min(qu[id].first, qu[id].second)]);
            int dead = sz(s) - s.order_of_key(min(qu[id].first, qu[id].second));
            ans[id] = inside - 2 * dead;
        }
    }
    cout << endl;
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
