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

int solve(int n, int r, vector<int> a){
    ckmin(r, n-r);
    __int128 lx = 1, rx = 1e15, opt = rx;
    auto solve = [&] (__int128 lambda) {
        vector<pair<__int128, int>> dp(2, pair(-1e25, 0));
        dp[0] = {0, 0};
        for (int i = 0; i < n-1; ++i) {
            vector<pair<__int128, int>> ndp(2);
            ndp[0] = max(dp[0], dp[1]);
            ndp[1] = {dp[0].first+a[i]-lambda+a[i+1], dp[0].second-1};
            swap(dp, ndp);
        }
        auto ans = max(dp[0], dp[1]);
        ans.second *= -1;
        return ans;
    };
    while (lx <= rx) { 
        __int128 md = lx + (rx-lx+1)/2;
        auto [tot, used] = solve(md);
        if (used <= r) opt = md, rx = md-1;
        else lx = md+1;
    }
    auto [ans, used] = solve(opt);
    ans += opt * used;
    ans += (r-used)*opt;
    return int(ans);
}
int brute(int n, int r, vector<int> a) {
    int ans = 0;
    for (int i = 0; i < (1 << n); ++i) {
        if (__builtin_popcount(i) != r) continue;
        int cur = 0;
        for (int j = 0; j < n-1; ++j) {
            if ((i>>j&1) != (i>>(j+1)&1)) cur += a[j];
        }
        ckmax(ans, cur);
    }
    return ans;
}
int32_t main(){_
#ifndef gato
    int n, r; cin >> n >> r;
    vector<int> a(n);
    for (int i = 0; i < n-1; ++i) cin >> a[i];
    cout << solve(n, r, a) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(2, 20), r = rnd(1, n-1);
        vector<int> a(n);
        for (int i = 0; i < n-1; ++i) a[i] = rnd(1, 1e9);
        int my = solve(n, r, a), ans = brute(n, r, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << r << endl;
            for (int i = 0; i < n-1; ++i) cout << a[i] << ' ';
            cout << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
