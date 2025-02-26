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
const int mod = (119<<23)+1;
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
    vector<int> pos(n), d(n);
    for (int i = 0; i < n; ++i) cin >> pos[i] >> d[i];
    vector<int> seg(4*n);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int k) -> void {
        if (l == r) {
            seg[i] = k;
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, k);
        else self(self, 2*i+1, md+1, r, x, k);
        seg[i] = max(seg[2*i], seg[2*i+1]);
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> int {
        if (r < x or y < l or x > y) return 0;
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        return max(self(self, 2*i, l, md, x, y), self(self, 2*i+1, md+1, r, x, y));
    };
    vector<int> ord(n); iota(all(ord), 0);
    sort(all(ord), [&] (int x, int y) {
        return pos[x] < pos[y];
    });
    vector<int> dp(n);
    for (int i = n-1; ~i; --i) {
        int l = i+1, r = n-1, ptr = i;
        while (l <= r) {
            int md = l + (r-l+1)/2;
            if (pos[ord[md]] < pos[ord[i]] + d[ord[i]]) ptr = md, l = md+1;
            else r = md-1;
        }
        dp[i] = max(i, query(query, 1, 0, n-1, i+1, ptr));
        upd(upd, 1, 0, n-1, i, dp[i]);
    }
    vector<int> bit(n+1);
    auto insert = [&] (int x, int k) {
        while (x <= n) bit[x] = (bit[x] + k) % mod, x += x & (-x);
    };
    auto qry = [&] (int x) {
        int ans = 0;
        while (x) ans = (ans + bit[x]) % mod, x -= x & (-x);
        return ans;
    };
    int ans = 1;
    for (int i = n-1; ~i; --i) {
        int mx = dp[i]+1;
        int my = (mod + 1 + qry(n) - qry(mx)) % mod;
        insert(i+1, my);
        ans = (ans + my) % mod;
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
