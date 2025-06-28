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
    struct node {
        int ans = 0, lx = 0, rx = 0;
    };
    vector<int> a(n);
    vector<node> seg(4*n);
    auto upd = [&] (auto&& self, int i, int l, int r, int x) -> void {
        if (l == r) {
            a[x] ^= 1;
            seg[i].ans = seg[i].lx = seg[i].rx = a[x];
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x);
        else self(self, 2*i+1, md+1, r, x);
        seg[i].ans = seg[2*i].ans + seg[2*i+1].ans;
        seg[i].lx = seg[2*i].lx;
        seg[i].rx = seg[2*i+1].rx;
        if (seg[2*i].rx == seg[2*i+1].lx and seg[2*i].rx == 1) seg[i].ans--;
    };
    for (int i = 0; i < q; ++i) {
        int x; cin >> x; --x;
        upd(upd, 1, 0, n-1, x);
        cout << seg[1].ans << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
