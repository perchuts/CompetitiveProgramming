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

int brute(int n, vector<int> a) {
    vector<int> dp(n+1);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        int mn = a[i-1], mx = a[i-1];
        for (int j = i-1; j >= 0; --j) {
            dp[i] = (dp[i] + dp[j] * (mx-mn)) % mod;
            if (j) ckmin(mn, a[j-1]), ckmax(mx, a[j-1]);
        }
    }
    return dp[n];
}

int solve(int n, vector<int> a){
    vector<int> pref(n+1); pref[0] = 1;
    vector<ii> b = {{inf, 0}}, l = {{0, 0}};
    int dp = 0;
    for (int i = 0; i < n; ++i) {
        int eu = dp;
        while (b.back().first < a[i]) {
            int lx = rbegin(b)[1].second;
            int x = (pref[b.back().second-1] - (lx?pref[lx-1]:0) + mod) % mod;
            eu = (eu + (a[i] - b.back().first) * x) % mod;
            b.pop_back();
        }
        while (l.back().first > a[i]) {
            int lx = rbegin(l)[1].second;
            int x = (pref[l.back().second-1] - (lx?pref[lx-1]:0) + mod) % mod;
            eu = (eu + (2*mod - a[i] + l.back().first) * x) % mod;
            l.pop_back();
        }
        pref[i+1] = (pref[i] + eu) % mod;
        dp = eu, b.pb({a[i], i+1}), l.pb({a[i], i+1});
    }
    return dp;
}

int32_t main(){_
#ifndef gato
    int n; cin >> n;
    vector<int> v(n);
    for (auto& x : v) cin >> x;
    cout << solve(n, v) << endl;
#else
    int t = 1;
    while (true) { 
        int n = rnd(1, 1000);
        vector<int> v(n);
        for (auto& x : v) x = rnd(1, 1e9);
        int my = solve(n, v), ans = brute(n, v);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl;
            for (auto x : v) cout << x << ' ';
            cout << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
