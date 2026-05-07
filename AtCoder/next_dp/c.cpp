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

void solve() {
    int n; cin >> n;
    string s1, s2, s3; cin >> s1 >> s2 >> s3;
    int t1 = sz(s1), t2 = sz(s2), t3 = sz(s3);
    vector dp(t1, vector(t2, vector<ll>(t3)));
    dp[0][0][0] = 1;
    for (int t = 1; t <= n; ++t) {
        vector ndp(t1, vector(t2, vector<ll>(t3)));
        for (char c = 'a'; c <= 'z'; ++c) {
            for (int i = 0; i < t1; ++i) {
                int ni = i + (s1[i] == c);
                if (ni == t1) continue;
                for (int j = 0; j < t2; ++j) {
                    int nj = j + (s2[j] == c);
                    if (nj == t2) continue;
                    for (int k = 0; k < t3; ++k) {
                        int nk = k + (s3[k] == c);
                        if (nk == t3) continue;
                        ndp[ni][nj][nk] += dp[i][j][k];
                        if (ndp[ni][nj][nk] >= mod) ndp[ni][nj][nk] -= mod;
                    }
                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for (auto x : dp) for (auto y : x) for (auto z : y) ans += z;
    ans %= mod;
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
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
