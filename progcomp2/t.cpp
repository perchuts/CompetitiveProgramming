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
    int n, q; cin >> n >> q;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    const int B = 400;
    vector<vector<iii>> qu(n/B+1);
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r; --l, --r;
        qu[l/B].pb({r, l, i});
    }
    vector<int> ans(q);
    int mx = *max_element(all(v));
    vector<int> bit(mx+1);
    auto add = [&] (int x, int k) {
        while (x <= mx) bit[x] += k, x += x & (-x);
    };
    auto query = [&] (int x) {
        int ans = 0;
        while (x) ans += bit[x], x -= x & (-x);
        return ans;
    };
    int lx = 0, rx = 0;
    for (int i = 0; i <= n/B; ++i) {
        sort(all(qu[i]));
        for (auto [r, l, id] : qu[i]) {
            while (lx < l) add(v[lx++], -1);
            while (l < lx) add(v[--lx], 1);
            while (rx <= r) add(v[rx++], 1);
            while (r+1 < rx) add(v[--rx], -1);
            int llx = 1, rrx = n;
            while (llx <= rrx) {
                int md = llx + (rrx-llx+1)/2;
                if (r-l+1 - query(md-1) >= md) ans[id] = md, llx = md+1;
                else rrx = md-1;
            }
        }
    }
    for (auto x : ans) cout << x << endl;
    
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
