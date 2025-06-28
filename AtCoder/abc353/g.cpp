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

const int inf = 2e15+1;
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
    int n, c, m; cin >> n >> c >> m;
    vector<int> t(m), p(m);
    for (int i = 0; i < m; ++i) cin >> t[i] >> p[i], --t[i];
    vector<array<int, 2>> seg(4*n, {-inf, -inf});
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            ckmax(seg[i][0], -l*c + k);
            ckmax(seg[i][1], l*c + k);
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        for (int j = 0; j < 2; ++j) seg[i][j] = max(seg[2*i][j], seg[2*i+1][j]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> array<int, 2> {
        if (r < x or y < l) return {-inf, -inf};
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        auto a = self(self, 2*i, l, md, x, y);
        auto b = self(self, 2*i+1, md+1, r, x, y);
        return {max(a[0], b[0]), max(a[1], b[1])};
    };
    upd(upd, 1, 0, n-1, 0, 0);
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        auto a = query(query, 1, 0, n-1, 0, t[i])[1] - t[i] * c + p[i];
        auto b = query(query, 1, 0, n-1, t[i], n-1)[0] + t[i] * c + p[i];
        int eu = max(b, a);
        ckmax(ans, eu);
        upd(upd, 1, 0, n-1, t[i], eu);
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
