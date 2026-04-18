#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

void solve(int n, vector<int> p) {
    if (__builtin_popcount(n) == 1 and p[n-1] != n) {
        cout << -1 << endl;
        return;
    }
    vector<vector<int>> ops;
    vector<int> onde(n+1);
    for (int i = 0; i < n; ++i) onde[p[i]] = i;
    auto apply = [&] (vector<int> v) {
        if (v.empty()) return;
        sort(all(v));
        //cout << "applying: ";
        //for (auto x : v) cout << x << " ";
        //cout << endl;
        int x = 0;
        for (int i = 0; i < sz(v); ++i) {
            x ^= p[v[i]];
            if (i and v[i] == v[i-1]) assert(false);
        }
        assert(x == 0);
        vector<int> v2 = v;
        sort(all(v2), [&] (int xx, int yy) {
            return p[xx] < p[yy];
        });
        auto np = p;
        for (int i = 0; i < sz(v); ++i) np[v[i]] = p[v2[i]];
        ops.pb(v);
        swap(p, np);
        for (int i = 0; i < n; ++i) onde[p[i]] = i;
        //cout << "result: ";
        //for (auto x : p) cout << x << " ";
        //cout << endl;
    };
    if (n % 4 == 3) {
        vector<int> v(n); iota(all(v), 0);
        apply(v);
    }
    auto apply_range = [&] (int l, int r) {
        vector<int> v1;
        for (int i = l; i <= r; ++i) v1.pb(onde[i]);
        apply(v1);
    };
    if (n % 4 == 1) {
        if (n != 1) {
            apply_range(2, n);
            apply_range(1, n-2);
            apply_range(n-3, n);
        }
    }
    if (n % 4 == 2) {
        if (n == 2) {
        } else {
            if (p[n-1] != n) { 
                vector<int> v = {n-1, onde[n]};
                // quero encontrar um parzinho pro N, um parzinho pro p[n-1]
                if (p[n-1] > n-3) v.pb(onde[n^p[n-1]]);
                else {
                    v.pb(onde[n-1]);
                    if (p[n-1] != 3) v.pb(onde[p[n-1]^3]);
                }
                apply(v);
            }
            apply_range(2, n-1);
            apply_range(1, n-3);
            apply_range(n-4, n-1);
        }
    }
    if (n % 4 == 0) {
        if (p[n-1] != n) {
            vector<int> v = {n-1, onde[n]};
            if ((p[n-1]^n) <= n) {
                v.pb(onde[p[n-1]^n]);
            } else {
                int pw = 1;
                while (2 * pw < n) pw *= 2;
                v.pb(onde[pw]);
                v.pb(onde[pw^p[n-1]^n]);
            }
            apply(v);
        }
        apply_range(1, n-1);
    }
    cout << sz(ops) << endl;
    for (auto x : ops) {
        cout << sz(x) << " ";
        for (auto i : x) cout << i + 1 << " ";
        cout << endl;
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> p(n);
        for (auto& x : p) cin >> x;
        solve(n, p);
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 20);
        vector<int> p(n); iota(all(p), 1); shuffle(all(p), rng);
        cout << n << endl;
        for (auto x : p) cout << x << " ";
        cout << endl;
        solve(n, p);
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
