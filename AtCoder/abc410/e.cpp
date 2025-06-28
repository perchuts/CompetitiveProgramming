#include <bits/stdc++.h>
//#define gato
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

int solve(int n, int h, int m, vector<int> a, vector<int> b){
    vector<int> ord(n); iota(all(ord), 0);
    vector<vector<int>> dp1(n+2, vector<int>(3001, -inf));
    dp1[0][m] = h;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp1[i][j] = dp1[i-1][j] - a[ord[i-1]];
            if (j + b[ord[i-1]] <= m) ckmax(dp1[i][j], dp1[i-1][j + b[ord[i-1]]]);
            if (dp1[i][j] >= 0) ckmax(ans, i);
        }
    }
    return ans;
}
int brute(int n, int h, int m, vector<int> a, vector<int> b) {
    int ans = 0;
    for (int i = 0; i < (1 << n); ++i) {
        int tot = 0;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) tot += a[j];
        }
        int aa = __builtin_popcount(i);
        if (tot <= h) ckmax(ans, aa);
        for (int j = i; j; j = (j-1)&i) {
            int t1 = 0, t2 = 0;
            for (int k = 0; k < n; ++k) {
                if (i >> k & 1) {
                    if (j >> k & 1) t2 += b[k];
                    else t1 += a[k];
                }
            }
            if (t1 <= h and t2 <= m) ckmax(ans, aa);
        }
    }
    return ans;
}
int32_t main(){_
#ifndef gato
    int n, h, m; cin >> n >> h >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i];
    cout << solve(n, h, m, a, b) << endl;
#else
int t = 1;
    while (true) {
        int n = rnd(1, 10), h = rnd(1, 3000), m = rnd(1, 3000);
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) a[i] = rnd(1, 3000), b[i] = rnd(1, 3000);
        int my = solve(n, h, m, a, b), ans = brute(n, h, m, a, b);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << h << ' ' << m << endl;
            for (int i = 0; i < n; ++i) cout << a[i] << ' ' << b[i] << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
