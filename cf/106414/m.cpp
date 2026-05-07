#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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

mt19937 rng(69);

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

string solve(int n, int k, int x, int y) {
    if (x == y) return string(k, '0');
    if (x > y) swap(x, y);
    string s(k, '0');
    vector<int> base(2*k+1);
    base[0] = 1;
    for (int i = 1; i <= 2*k; ++i) {
        if (i >= x) base[i] ^= base[i-x];
        if (i >= y) base[i] ^= base[i-y];
    }
    auto solve = [&] (auto&& self, int D) -> vector<int> {
        if (D <= k) {
            vector<int> ans(k);
            for (int i = 0; i < k; ++i) ans[i] = base[D+i];
            return ans;
        }
        int st = (D-y+1)/2;
        auto v = self(self, st);
        vector<int> ans(k);
        for (int i = 0; i < k; ++i) {
            int val = D + i;
            if (val % 2 == 0) ans[i] ^= v[val/2-st];
            if (val % 2 == x % 2) ans[i] ^= v[(val-x)/2-st];
            if (val % 2 == y % 2) ans[i] ^= v[(val-y)/2-st];
        }
        return ans;
    };
    // i <= k-x: start = i + y
    // i > k-x: start = i
    // k-y+1 <= i <= k-x: start = i+y
    // k-x+1 <= i <= k: start = i
    // k+1 <= start <= k-x+y
    // k-x+1 <= start <= k
    // k-x+1 <= start <= k-x+y
    // n-(k-x+y) = n-k-y+x <= D <= n-k-1+x
    int st = n-k-y+x; ckmax(st, 0);
    auto v = solve(solve, st);
    for (int i = k-y+1; i <= k; ++i) {
        int start;
        if (i + x <= k) start = i + y;
        else start = i;
        int D = n-start;
        if (D >= 0) s[i-1] = char('0' + v[D-st]);
    }
    reverse(begin(s), end(s));
    return s;
}

string brute(int n, int k, int x, int y) {
    vector<int> bichos(n+1);
    for (int i = 1; i <= k; ++i) bichos[i] = (1 << (i-1));
    for (int i = k+1; i <= n; ++i) bichos[i] = bichos[i-x] ^ bichos[i-y];
    string ans;
    for (int i = 0; i < k; ++i) ans += char('0' + (bichos[n]>>i&1));
    reverse(all(ans));
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, k, x, y; cin >> n >> k >> x >> y;
        cout << solve(n, k, x, y) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 10), k = rnd(1, n-1), x = rnd(1, k), y = rnd(1, k);
        string my = solve(n, k, x, y);
        string ans = brute(n, k, x, y);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << k << " " << x << " " << y << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
