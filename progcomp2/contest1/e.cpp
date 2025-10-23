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
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> grid(n, vector<int>(m));
    for (auto& x : grid) for (auto& y : x) cin >> y, --y;
    vector<int> pr(n+m-1, n*m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ckmin(pr[i+j], grid[i][j]);
        }
    }
    vector<int> order(n+m-1); iota(all(order), 0);
    sort(all(order), [&] (int x, int y) { return pr[x] < pr[y]; });
    // conte quantas RBS tem com order[i] = (. se isso eh <= k, ent subtrai oq eu achei e continua
    string ans(n+m-1, '#');
    for (int i = 0; i < n+m-1; ++i) {
        auto calc = [&] () {
            vector<int> dp(n+m+1);
            dp[0] = 1;
            for (int j = 0; j < n+m-1; ++j) {
                vector<int> ndp(n+m+1);
                for (int k = 0; k <= n+m-1; ++k) {
                    if (ans[j] != '(') ndp[k] += dp[k+1];
                    if (ans[j] != ')' and k) ndp[k] += dp[k-1];
                    ckmin(ndp[k], 2e18);
                }
                swap(dp, ndp);
            }
            return dp[0];
        };
        ans[order[i]] = '(';
        int x = calc();
        if (k <= x) {}
        else {
            k -= x;
            ans[order[i]] = ')';
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << ans[i+j];
        }
        cout << endl;
    }
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
