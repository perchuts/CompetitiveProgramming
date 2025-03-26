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
    struct node {
        bool ok = 1;
        int ss = 0, min_pref = 0;
        node(){}
    } nulo;
    nulo.min_pref = 1e18;
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<node> seg(4*n);
    auto merge = [] (node a, node b) {
        node res;
        res.ss = a.ss + b.ss;
        res.min_pref = min(a.min_pref, a.ss + b.min_pref);
        res.ok = (a.ok and (a.ss + b.min_pref >= 0));
        return res;
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            seg[i].ok = (k == 1);
            seg[i].ss = seg[i].min_pref = k;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = merge(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> node {
        if (r < x or y < l) return nulo;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return merge(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    vector<int> val(300);
    val[')'] = -1;
    val['('] = 1;
    for (int i = 0; i < n; ++i) upd(upd, 1, 0, n-1, i, val[s[i]]);
    while (q--) {
        int op, l, r; cin >> op >> l >> r;
        --l, --r;
        if (op == 1) {
            swap(s[l], s[r]);
            upd(upd, 1, 0, n-1, l, val[s[l]]);
            upd(upd, 1, 0, n-1, r, val[s[r]]);
        } else {
            auto res = query(query, 1, 0, n-1, l, r);
            cout << ((res.ok and res.ss == 0) ? "Yes" : "No") << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
