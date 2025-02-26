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
    int q, k; cin >> q >> k;
    vector<ii> ops(q);
    vector<int> vals;
    for (auto& [x, y] : ops) cin >> x >> y, vals.pb(y);
    sort(all(vals)); vals.erase(unique(all(vals)), end(vals));
    int n = sz(vals);
    struct node {
        int res = 0, mn = -1, mx = -1, tot = 0;
        node() {}
    } nulo;
    vector<node> seg(4*n);
    auto merge = [&] (node a, node b) {
        node c;
        if (a.mn == -1 and b.mn == -1) return c;
        if (a.mn == -1) return b;
        if (b.mn == -1) return a;
        c.res = max({a.res, b.res, b.mn-a.mx});
        c.mn = a.mn, c.mx = b.mx;
        c.tot = a.tot + b.tot;
        return c;
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x) -> void {
        if (l == r) {
            if (!seg[i].tot) seg[i].mn = seg[i].mx = vals[l], seg[i].tot = 1;
            else seg[i].mn = seg[i].mx = -1, seg[i].tot = 0;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x);
        else self(self, 2*i+1, md+1, r, x);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
        if (y < l or r < x) return nulo;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return merge(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    //for (auto x : vals) cout << x << ' ';
    //cout << endl;
    for (auto [x, y] : ops) {
         int i = lower_bound(all(vals), y) - begin(vals);
        if (x == 1) {
            upd(upd, 1, 0, n-1, i); 
        } else {
            int l = 0, r = i-1, idl = i, idr = i;
            while (l <= r) {
                int md = l + (r-l+1)/2;
                auto ans = query(query, 1, 0, n-1, md, i);
                if (ans.res <= k) idl = md, r = md-1;
                else l = md+1;
            }
            l = i+1, r = n-1;
            while (l <= r) {
                int md = l + (r-l+1)/2;
                auto ans = query(query, 1, 0, n-1, i, md);
                if (ans.res <= k) idr = md, l = md+1;
                else r = md-1;
            }
            auto ans = query(query, 1, 0, n-1, idl, idr);
            //cout << idl << ' ' << idr << ' ' << ans.mn << ' ' << ans.mx << ' ';
            cout << ans.tot << endl;
        }
    };
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
