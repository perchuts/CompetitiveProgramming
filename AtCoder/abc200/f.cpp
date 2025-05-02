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

int solve(string s, int k){
    struct node {
        int qnt[2], ways;
        node() { qnt[0] = qnt[1] = ways = 0; }
    };
    vector<vector<node>> dp(2, vector<node>(2));
    if (s[0] == '?') {
        for (int i = 0; i < 2; ++i) dp[i][i].qnt[i] = dp[i][i].ways = 1;
    } else {
        int i = s[0]-'0';
        dp[i][i].qnt[i] = dp[i][i].ways = 1;
    }
    int n = sz(s);
    vector<vector<node>> ans(2, vector<node>(2));
    for (int i = 1; i < n; ++i) {
        vector<vector<node>> ndp(2, vector<node>(2));
        for (int a = 0; a < 2; ++a) {
            for (int b = 0; b < 2; ++b) {
                for (int c = 0; c < 2; ++c) {
                    if (s[i] != '?' and s[i] - '0' != c) continue;
                    if (dp[a][b].ways == 0) continue;
                    ndp[a][c].qnt[c^1] += dp[a][b].qnt[c^1];
                    ndp[a][c].qnt[c] += dp[a][b].qnt[c] + (b!=c?dp[a][b].ways:0);
                    ndp[a][c].ways += dp[a][b].ways;
                }
            }
        }
        swap(dp, ndp);
        for (int a = 0; a < 2; ++a) for (int b = 0; b < 2; ++b) dp[a][b].qnt[0] %= mod, dp[a][b].qnt[1] %= mod, dp[a][b].ways %= mod;
        ans = dp;
        //for (int i = 0; i < 2; ++i) {
        //    for (int j = 0; j < 2; ++j) cout << ans[i][j].qnt[0] << ' ' << ans[i][j].qnt[1] << ' ' << ans[i][j].ways << endl;
        //}
        //cout << endl;
    }
    bool foi = 0;
    auto mult = [&] (vector<vector<node>> m1, vector<vector<node>> m2) {
        vector<vector<node>> resp(2, vector<node>(2));
        for (int a1 = 0; a1 < 2; ++a1) {
            for (int b1 = 0; b1 < 2; ++b1) {
                for (int a2 = 0; a2 < 2; ++a2) {
                    for (int b2 = 0; b2 < 2; ++b2) {
                        auto x = m1[a1][b1];
                        auto y = m2[a2][b2];
                        auto& z = resp[a1][b2];
                        int cw = x.ways*y.ways % mod;
                        z.ways = (z.ways + cw) % mod;
                        for (int i = 0; i < 2; ++i) z.qnt[i] = (z.qnt[i] + x.qnt[i] * y.ways + y.qnt[i] * x.ways) % mod;
                        if (b1 == a2) z.qnt[b1] = (z.qnt[b1] - cw + mod) % mod;
                    }
                }
            }
        }
        return resp;
    };
    while (k) {
        if (k&1) {
            if (!foi) foi = 1, ans = dp;
            else ans = mult(ans, dp);
        }
        k /= 2, dp = mult(dp, dp);
    }
    int resp = 0;
    for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) resp = (resp + ans[i][j].qnt[i^1]) % mod;
    return resp;
}

int brute(string s, int k) {
    int n = sz(s);
    vector<int> val(n), m;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '?') m.pb(i);
    }
    int ans = 0;
    vector<vector<vector<int>>> qq(2, vector<vector<int>>(2, vector<int>(3)));
    for (int mask = 0; mask < (1 << sz(m)); ++mask) {
        for (int i = 0; i < n; ++i) if (s[i] != '?') val[i] = s[i] - '0';
        for (int i = 0; i < sz(m); ++i) val[m[i]] = (mask>>i&1);
        int q0 = 0, q1 = 0;
        for (int i = 1; i < n; ++i) {
            if (val[i] != val[i-1]) {
                if (val[i-1]) q1++;
                else q0++;
            }
        }
        if (val.back()) q1++;
        else q0++;
        qq[val[0]][val.back()][0] += q0;
        qq[val[0]][val.back()][1] += q1;
        qq[val[0]][val.back()][2]++;
        if (val[0]) ans += q0;
        else ans += q1;
    }
    return ans;
}

int32_t main(){_
    string s; int k; cin >> s >> k;
    cout << solve(s, k) << endl;
    //cout << brute(s, k) << endl;
}
