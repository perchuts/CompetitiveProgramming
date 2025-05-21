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
    vector<int> vals;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i], vals.pb(a[i]);
    int q; cin >> q;
    vector<iii> upds(q);
    for (auto& [x, y, z] : upds) {
        cin >> x;
        if (x == 1) cin >> y >> z, vals.pb(z);
        else if (x == 2) cin >> y >> z;
        else cin >> y;
    }
    sort(all(vals)), vals.erase(unique(all(vals)), end(vals));
    int N = sz(vals);
    vector<array<int, 2>> seg(4*N);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            seg[i][0] += k;
            seg[i][1] += k * vals[l];
            return;
        }
        int md = (l + r) / 2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i][0] = seg[2*i][0] + seg[2*i+1][0];
        seg[i][1] = seg[2*i][1] + seg[2*i+1][1];
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x) -> array<int, 2> {
        if (seg[i][0] <= x) return seg[i];
        if (l == r) return {x, vals[l] * x};
        int md = (l+r)/2;
        if (seg[2*i+1][0] >= x) return self(self, 2*i+1, md+1, r, x);
        auto ans = seg[2*i+1];
        auto ansL = self(self, 2*i, l, md, x-ans[0]);
        return {ans[0]+ansL[0], ans[1]+ansL[1]};
    };
    auto get = [&] (int x) { return lower_bound(all(vals), x) - begin(vals); };
    for (int i = 0; i < n; ++i) a[i] = get(a[i]), upd(upd, 1, 0, N-1, a[i], b[i]);
    for (auto [x, y, z] : upds) {
        int i = y-1;
        if (x == 1) {
            z = get(z);
            upd(upd, 1, 0, N-1, a[i], -b[i]);
            a[i] = z;
            upd(upd, 1, 0, N-1, a[i], b[i]);
        } else if (x == 2) {
            upd(upd, 1, 0, N-1, a[i], z-b[i]);
            b[i] = z;
        } else {
            auto ans = query(query, 1, 0, N-1, y);
            cout << (ans[0] < y ? -1 : ans[1]) << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
