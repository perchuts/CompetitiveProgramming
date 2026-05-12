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

int dp[3000][200];

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<string> bichos;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        string s;
        for (int j = 0; (1LL << j) <= a[i]; j++, ans++) s += char('0' + (a[i] >> j & 1));
        bichos.pb(s);
    }
    vector<int> dp2(1);
    for (int i = 0; i < n; ++i) {
        vector<int> ndp2(60*min((n+1)/2, i+1)+1, -10000);
        for (int w = 0; w < sz(dp2); ++w) {
            int t1 = (i == 0 ? 0 : sz(bichos[i-1])), t2 = sz(bichos[i]);
            for (int j = 0; j <= t1; ++j) {
                for (int k = 0; k <= t2; ++k) {
                    dp[j][k] = 0;
                    // can do some match!
                    if (min(j, k) and bichos[i-1][j-1] == bichos[i][k-1]) ckmax(dp[j][k], 1 + dp[j-1][k-1]);
                    if (k) ckmax(dp[j][k], dp[j][k-1]);
                    if (j) ckmax(dp[j][k], dp[j-1][k]);
                }
            }
            int qt0 = 0;
            if (i) for (auto x : bichos[i-1]) qt0 += (x == '0');
            for (int j = 0; j < t1; ++j) {
                // lets suppose i ended second string here
                if (qt0 < sz(ndp2)) ckmax(ndp2[qt0], dp[j][t2] + dp2[w]);
                qt0 -= (bichos[i-1][j] == '0');
            }
            ckmax(ndp2[0], dp[t1][t2] + dp2[w]);
            if (w != sz(dp2)-1) bichos[i-1] += '0';
        }
        for (int j = sz(ndp2)-2; j >= 0; --j) ckmax(ndp2[j], ndp2[j+1]);
        swap(ndp2, dp2);
    }
    cout << ans-dp2[0] << endl;
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
