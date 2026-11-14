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

void solve() {
    int n, k, a; cin >> n >> k >> a;
    int S = 0;
    vector<vector<ii>> pts(k+1);
    for (int i = 0; i < n; ++i) {
        int x, y, c; cin >> x >> y >> c;
        S += c;
        pts[x].pb({y, c});
    }
    vector<int> dp_col(k+1), seg(4*k, -1e18), lz(4*k);
    auto push = [&] (int i, int l, int r) {
        seg[i] += lz[i];
        if (l != r) lz[2*i] += lz[i], lz[2*i+1] += lz[i];
        lz[i] = 0;
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int y, int c, bool z = 0) -> void {
        push(i, l, r);
        if (r < x or y < l) return;
        if (x <= l and r <= y) {
            if (z) seg[i] = c;
            else lz[i] += c, push(i, l, r);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, y, c, z);
        self(self, 2*i+1, md+1, r, x, y, c, z);
        seg[i] = max(seg[2*i], seg[2*i+1]);
    };
    int ans = S;
    for (int i = k-1; ~i; --i) {
        upd(upd, 1, 0, k-1, k-1-i, k-1-i, ((k-1-i) - k) * a + dp_col[i+1], 1);
        for (auto [y, c] : pts[i]) {
             upd(upd, 1, 0, k-1, 0, y, c);
        }
        dp_col[i] = max(seg[1] + i*a, dp_col[i+1]);
        ckmin(ans, S - dp_col[i]);
    }
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
