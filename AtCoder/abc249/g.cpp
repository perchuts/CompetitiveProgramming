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
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

int solve(int n, int k, vector<int> a, vector<int> b) {
    using T = bitset<1000>;
    vector<vector<int>> bases(30);
    vector base(30, vector(30, pair<T, int>()));
    vector<int> dim(30);
    auto coord = [&] (int i, int x, bool add, int w = 0) {
        T c;
        if (add) c[w] = 1;
        for (int j = 0; j < 30; ++j) {
            if (x >> j & 1) {
                if (base[i][j].second == 0) {
                    if (add) {
                        base[i][j] = {c, x};
                        dim[i]++;
                    }
                    return pair(false, c);
                }
                x ^= base[i][j].second;
                c ^= base[i][j].first;
            }
        }
        return pair(true, c);
    };
    auto get = [&] (T& c, int type) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (c[i] == 1) ans ^= (type ? b[i] : a[i]);
        }
        return ans;
    };
    for (int i = 0; i < 30; ++i) {
        for (int j = n-1; ~j; --j) {
            auto [foi, c] = coord(i, a[j] >> i, 1, j);
            if (foi) {
                bases[i].push_back(get(c, 1));
            }
        }
        vector<int> v(30);
        for (auto x : bases[i]) {
            for (int j = 29; ~j; --j) {
                if (x >> j & 1) {
                    if (v[j] == 0) { v[j] = x; break; }
                    x ^= v[j];
                }
            }
        }
        swap(v, bases[i]);
    }
    int eu = 0, ans = -1;
    auto test = [&] (int i, int w) {
        if (w == 0 and dim[i] == n) return;
        auto [foi, c] = coord(i, w, 0);
        if (foi == 0) return;
        int x = get(c, 1);
        for (int j = 29; ~j; --j) {
            if ((x >> j & 1) ^ (bases[i][j] != 0)) x ^= bases[i][j]; 
        }
        ckmax(ans, x);
    };
    for (int i = 29; ~i; --i) {
        if (k >> i & 1) test(i, eu >> i), eu += (1 << i);
    }
    test(0, k);
    return ans;
}

int brute(int n, int k, vector<int> a, vector<int> b) {
    int ans = -1;
    for (int i = 1; i < (1 << n); ++i) {
        int x1 = 0, x2 = 0;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) x1 ^= a[j], x2 ^= b[j];
        }
        if (x1 <= k) ckmax(ans, x2);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n, k; cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    cout << solve(n, k, a, b) << endl;
#else
    int t = 1;
    while (true) {
        int bits = 10;
        int n = rnd(1, 15), k = rnd(0, (1<<bits)-1);
        vector<int> a(n), b(n);
        for (auto& x : a) x = rnd(0, (1<<bits)-1);
        for (auto& x : b) x = rnd(0, (1<<bits)-1);
        int my = solve(n, k, a, b), ans = brute(n, k, a, b);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << k << endl;
            for (int i = 0; i < n; ++i) cout << a[i] << ' ' << b[i] << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
