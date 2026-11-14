#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}


int solve(int n, int m, vector<int> a) {
    vector<int> cnt(n);
    for (auto& x : a) cnt[x]++;
    vector<int> vis(n);
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        if (vis[i]) continue;
        int val = 0, tot = 0, cur = i;
        do {
            val += cnt[cur], vis[cur] = true;
            if (val & 1) tot += cur / i;
            cur *= 2, val /= 2;
        } while (cur < n and val > 0);
        if (val) tot = cur / i - 1;
        ans = ans * (1+tot) % mod;
    }
    return ans;
}

int brute(int n, int m, vector<int> a) {
    vector<int> cnt(n);
    for (auto x : a) cnt[x]++;
    set<__int128_t> bs;
    vector<int> b;
    __int128_t Z = 1;
    for (int i = 0; i < n-1; ++i) Z = 2 * Z + 1;
    auto go = [&] (auto&& self, int i) -> void {
        if (i == n) {
            __int128_t dp = 1;
            for (auto x : b) dp ^= (dp << x);
            bs.insert(dp & Z);
            return;
        }
        for (int j = 0; j <= cnt[i]; ++j) self(self, i+1), b.pb(i);
        for (int j = 0; j <= cnt[i]; ++j) b.pop_back();
    };
    go(go, 0);
    return sz(bs);
}

int32_t main() {_
#ifndef gato
    int n, m; cin >> n >> m;
    vector<int> a(m);
    for (auto& x : a) cin >> x;
    cout << solve(n, m, a) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 10), m = rnd(1, 12);
        vector<int> a(m);
        for (auto& x : a) x = rnd(1, n-1);
        int my = solve(n, m, a);
        int ans = brute(n, m, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << m << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
