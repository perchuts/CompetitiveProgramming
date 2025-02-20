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
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<iii> ev;
    for (int i = 0; i < n; ++i) ev.pb({a[i], -1, i});
    vector<int> ans(q);
    for (int i = 0; i < q; ++i) {
        int l, x; cin >> l >> x;
        --l;
        ev.pb({x, i, l});
    }
    vector<int> seg(4*n), lz(4*n);
    auto push = [&] (int i, int l, int r) {
        seg[i] += lz[i];
        if (l != r) lz[2*i] += lz[i], lz[2*i+1] += lz[i];
        lz[i] = 0;
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int y, int k) -> void {
        push(i, l, r);
        if (r < x or y < l) return;
        if (x <= l and r <= y) {
            lz[i] += k;
            push(i, l, r);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, y, k);
        self(self, 2*i+1, md+1, r, x, y, k);
        seg[i] = max(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        push(i, l, r);
        if (r < x or y < l) return 0LL;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return max(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    sort(all(ev));
    for (int l = 0, r = 0; l < sz(ev); l = r) {
        vector<ii> qu;
        auto [X, lixo1, lixo2] = ev[l];
        vector<int> uu;
        while (true) {
            auto [x, a, b] = ev[r];
            if (x != X) break;
            if (a == -1) {
                uu.pb(b);
            } else qu.pb({b, a});
            r++;
        }
        sort(rbegin(uu), rend(uu));
        for (auto pos : uu) {
            int eu = (pos?query(query, 1, 0, n-1, 0, pos-1):0) + 1;
            upd(upd, 1, 0, n-1, pos, pos, eu);
        }
        for (auto [pos, idq] : qu) ans[idq] = query(query, 1, 0, n-1, 0, pos);
    }
    for (auto x : ans) cout << x << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
