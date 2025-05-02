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
    vector<int> a(n), seg(4*n);
    for (auto& x : a) cin >> x;
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        seg[i] ^= k;
        if (l == r) return;
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        if (r < x or y < l) return 0LL;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return (self(self, 2*i, l, md, x, y) ^ self(self, 2*i+1, md+1, r, x, y));
    };
    for (int i = 0; i < n; ++i) upd(upd, 1, 0, n-1, i, a[i]);
    while (q--) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 1) --x, upd(upd, 1, 0, n-1, x, y);
        else {
            --x, --y;
            cout << query(query, 1, 0, n-1, x, y) << endl;
        }
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
