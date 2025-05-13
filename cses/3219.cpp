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
    int n, k; cin >> n >> k;
    vector<int> seg(4*n+10);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (x >= n) return;
        if (l == r) {
            seg[i] += k;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = min(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r) -> int {
        assert(seg[i] == 0);
        if (l == r) return l;
        int md = (l+r)/2;
        if (seg[2*i] == 0) return self(self, 2*i, l, md);
        return self(self, 2*i+1, md+1, r);
    };
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    for (int i = 0; i < k; ++i) upd(upd, 1, 0, n, v[i], 1);
    cout << query(query, 1, 0, n) << ' ';
    for (int i = k; i < n; ++i){ 
        upd(upd, 1, 0, n, v[i], 1);
        upd(upd, 1, 0, n, v[i-k], -1);
        cout << query(query, 1, 0, n) << ' ';
    }
    cout << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
