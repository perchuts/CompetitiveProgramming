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
const int maxn = 1e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(){
    int n, m; cin >> n >> m;
    vector<int> x(n+m), y(n+m);
    for (int i = 0; i < n+m; ++i) cin >> x[i] >> y[i];
    vector<ii> seg(4*maxn, pair(inf, inf));
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int a, int b) -> void {
        if (l == r) {
            ckmin(seg[i].first, a);
            ckmin(seg[i].second, b);
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, a, b);
        else self(self, 2*i+1, md+1, r, x, a, b);
        seg[i].first = min(seg[2*i].first, seg[2*i+1].first);
        seg[i].second = min(seg[2*i].second, seg[2*i+1].second);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> ii {
        if (r < x or y < l) return pair(inf, inf);
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        auto [x1, y1] = self(self, 2*i, l, md, x, y);
        auto [x2, y2] = self(self, 2*i+1, md+1, r, x, y);
        return pair(min(x1, x2), min(y1, y2));
    };
    vector<int> ans(m, inf);
    for (int turn = 0; turn < 2; ++turn) {
        seg = vector<ii>(4*maxn, pair(inf, inf));
        vector<ii> ev;
        for (int i = 0; i < n+m; ++i) ev.pb({x[i], i});
        sort(all(ev));
        for (auto [coord, id] : ev) {
            if (id < n) upd(upd, 1, 1, maxn, y[id], -(x[id]+y[id]), -(x[id]-y[id]));
            else {
                auto le = query(query, 1, 1, maxn, 1, y[id]).first;
                auto ri = query(query, 1, 1, maxn, y[id], maxn).second;
                if (le != inf) ckmin(ans[id-n], x[id]+y[id]+le);
                if (ri != inf) ckmin(ans[id-n], x[id]-y[id]+ri);
            }
        }
        for (int i = 0; i < n+m; ++i) x[i] *= -1;
    }
    cout << *max_element(all(ans)) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
