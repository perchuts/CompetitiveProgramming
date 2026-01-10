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
    int n; cin >> n;
    vector<int> p(n), onde(n);
    for (auto& x : p) cin >> x, --x;
    for (int i = 0; i < n; ++i) onde[p[i]] = i;
    vector<int> bit(n+1);
    auto query = [&] (int x) {
        int ans = 0;
        while (x) ans += bit[x], x -= x & (-x);
        return ans % mod;
    };
    auto add = [&] (int x, int y) {
        while (x <= n) bit[x] = (bit[x] + y) % mod, x += x & (-x);
    };
    vector<int> esq(n), dir(n);
    for (int i = 0; i < n; ++i) {
        int pos = onde[i];
        esq[pos] = (query(pos)) % mod;
        add(pos+1, esq[pos] + 1);
    }
    for (int i = 1; i <= n; ++i) bit[i] = 0;
    for (int i = 0; i < n; ++i) {
        int pos = onde[i];
        dir[pos] = (query(n) - query(pos) + mod) % mod;
        add(pos+1, dir[pos] + 1);
    }
    vector<int> esq2(n), dir2(n);
    for (int i = 1; i <= n; ++i) bit[i] = 0;
    for (int i = n-1; ~i; --i) {
        int pos= onde[i];
        esq2[pos] = query(pos);
        add(pos+1, esq[pos]);
    }
    for (int i = 1; i <= n; ++i) bit[i] = 0;
    for (int i = n-1; ~i; --i) {
        int pos= onde[i];
        dir2[pos] = (query(n) - query(pos) + mod) % mod;
        add(pos+1, dir[pos]);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) ans = (ans + esq[i] * dir[i]) % mod;
    vector<int> suf(n+1), pw(n+1, 1), pw2(n+1, 1);
    for (int i = 1; i <= n; ++i) pw[i] = pw[i-1] * ((mod+1)/2) % mod, pw2[i] = 2 * pw2[i-1] % mod;
    for (int i = n; i; --i) {
        if (i != n) suf[i] = suf[i+1];
        suf[i] = (suf[i] + dir2[i-1] * pw2[i-1]) % mod;
    }
    for (int i = 0; i < n-1; ++i) {
        int eu = esq2[i] * pw[i+1] % mod;
        ans = (ans + eu * suf[i+2]) % mod;
        ans = (ans + esq2[i] * dir2[i]) % mod;
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
