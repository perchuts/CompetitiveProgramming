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
    auto brute = [] (int n) {
        int ans = 1e18;
        for (int m = n; m <= n + 10*n; ++m) {
            string a = to_string(m), b = to_string(m-n);
            int cur = 0;
            for (auto x : a) cur += x - '0';
            for (auto x : b) cur += x - '0';
            ckmin(ans, cur);
        }
        return ans;
    };
    int n; cin >> n;
    unordered_map<int, int> dp;
    vector<int> pw(19, 1);
    for (int i = 1; i <= 18; ++i) pw[i] = 10 * pw[i-1];
    auto go = [&] (auto&& self, int x) -> int {
        if (x == 0) return 0LL;
        if (dp.count(x)) return dp[x];
        int z = 0;
        while (z < 18 and pw[z+1] <= x) z++;
        if (pw[z] == x) return dp[x] = 1;
        int d = (x/pw[z]) % 10;
        int other = ((pw[z+1]-x)/pw[z]) % 10;
        int opt = self(self, x - d*pw[z]) + d;
        ckmin(opt, other + 1 + self(self, pw[z+1]-x-other*pw[z]));
        ckmin(opt, d + 1 + self(self, pw[z]*(d+1)-x));
        return dp[x] = opt;
    };
    cout << go(go, n) << endl;
}

int32_t main() {_

#ifndef gato
    int t = 1; cin >> t;
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
