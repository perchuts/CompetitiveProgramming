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

void solve() {
    int n, q; cin >> n >> q;
    int z = (mod+1)/2;
    vector<ii> seg(4*n);
    vector<int> lz(4*n);
    // a[i] -> a[i] + k
    // k^2 + a[i]^2 + 2 * a[i] * k
    auto push = [&] (int i, int l, int r) {
        if (lz[i] == 0) return;
        auto& [sum, sq_sum] = seg[i];
        sq_sum += lz[i] * lz[i] % mod * (r-l+1) % mod;
        sq_sum += 2 * lz[i] * sum % mod;
        sq_sum %= mod;
        sum = (sum + lz[i] * (r-l+1)) % mod;
        if (l != r) lz[2*i] = (lz[2*i] + lz[i]) % mod, lz[2*i+1] = (lz[2*i+1] + lz[i]) % mod;
        lz[i] = 0;
    };
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int y, int k) -> void {
        push(i, l, r);
        if (r < x or y < l) return;
        if (x <= l and r <= y) {
            lz[i] = (lz[i] + k) % mod;
            push(i, l, r);
            return;
        }
        int md = (l+r)/2;
        self(self, 2*i, l, md, x, y, k);
        self(self, 2*i+1, md+1, r, x, y, k);
        seg[i].first = (seg[2*i].first + seg[2*i+1].first) % mod;
        seg[i].second = (seg[2*i].second + seg[2*i+1].second) % mod;
    };
    auto query = [&] (auto&& self, int i, int l, int r, int x, int y) -> ii {
        push(i, l, r);
        if (r < x or y < l) return pair(0LL, 0LL);
        if (x <= l and r <= y) return seg[i];
        int md = (l+r)/2;
        auto [l1, l2] = self(self, 2*i, l, md, x, y);
        auto [r1, r2] = self(self, 2*i+1, md+1, r, x, y);
        return pair((l1+r1)%mod, (l2+r2)%mod);
    };
    while (q--) {
        int l, r, k; cin >> l >> r >> k; --l, --r;
        upd(upd, 1, 0, n-1, l, r, k);
        auto [sum, sq_sum] = query(query, 1, 0, n-1, l, r);
        int ans = (sum*sum%mod - sq_sum) % mod;
        ans = (ans + mod) % mod;
        ans = ans * z % mod;
        cout << ans << endl;
    }
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
