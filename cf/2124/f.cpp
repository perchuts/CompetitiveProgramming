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
    int n, m; cin >> n >> m;
    vector<vector<int>> pode(n, vector<int>(n, true));
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b; --a, --b;
        pode[a][b] = 0;
    }
    vector can(n+1, vector(n+1, vector(n+1, false)));
    for (int i = 0; i < n; ++i) {
        for (int s = 1; s <= n-i; ++s) {
            for (int r = 0; r < s; ++r) {
                can[i][s][r] = true;
                for (int j = i, st = r; j < i + s; ++j, st = (st + 1) % s) {
                    if (pode[j][st] == false) can[i][s][r] = false;
                }
            }
        }
    }
    vector<int> dp(n+1);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int s = 1; s <= i; ++s) {
            for (int r = 0; r < s; ++r) {
                if (can[i-s][s][r] == true) dp[i] = (dp[i] + dp[i-s]) % mod;
            }
            if (can[i-s][s][0]) {
                for (int ss = s+1; ss+s <= i; ++ss){ 
                    if (can[i-ss-s][s][0] and can[i-ss-s][ss][0] and can[i-ss][ss][s]) dp[i] = (dp[i] - dp[i-ss-s] + mod) % mod;
                }
            }
        }
    }
    cout << dp[n] << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
