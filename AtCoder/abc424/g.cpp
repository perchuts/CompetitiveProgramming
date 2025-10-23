#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define gato

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

int solve(int n, int m, vector<int> a, vector<ii> v) {
    sort(begin(a), end(a));
    sort(rbegin(v), rend(v));
    vector<int> z;
    while (true) {
        if (a[n-1] == 0) break;
        for (int i = n-1; ~i; --i) {
            if (a[i]) z.pb(i), a[i]--;
        }
    }
    int N = sz(z);
    vector<int> dp(N+1);
    vector<int> temp(n);
    for (auto [x, y] : v) {
        vector<int> ndp = dp;
        for (int i = x; i <= N; ++i) {
            bool ok = true;
            for (int j = i-x; j < i; ++j) {
                ok &= temp[z[j]] == 0;
                temp[z[j]] = 1;
            }
            for (int j = i-x; j < i; ++j) temp[z[j]] = 0;
            if (ok) ckmax(ndp[i], dp[i-x] + y);
        }
        swap(dp, ndp);
    }
    return *max_element(all(dp));

}

int brute(int n, int m, vector<int> a, vector<ii> v) {
    sort(rbegin(a), rend(a));
    sort(rbegin(v), rend(v));
    int ans = 0;
    for (int i = 1; i < (1 << m); ++i) {
        auto z = a;
        bool ok = true;
        int tot = 0;
        for (int j = 0; j < m; ++j) {
            if (i >> j & 1) {
                sort(rbegin(z), rend(z));
                for (int k = 0; k < v[j].first; ++k) {
                    if (z[k] == 0) {
                        ok = false;
                        break;
                    }
                    z[k]--;
                }
                if (ok == false) break;
                tot += v[j].second;
            }
        }
        if (ok) ckmax(ans, tot);
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
        int n, m; cin >> n >> m;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<ii> v(m);
    for (auto& [x, y] : v) cin >> x >> y;
    cout << solve(n, m, a, v) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 5), m = rnd(1, 3);
        vector<int> a(n);
        for (auto& x : a) x = rnd(0, m);
        vector<ii> v(m);
        for (auto& [x, y] : v) x = rnd(0, n), y = rnd(0, 10);
        int my = solve(n, m, a, v), ans = brute(n, m, a, v);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << endl;
            for (auto x : a) cout << x << ' '; 
            cout << endl;
            for (auto [x, y] : v) cout << x << ' ' << y << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
