#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
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

int solve(int n, string s) {
    // se 
    vector<int> a;
    a.pb(s[0] == 'A' ? 1 : -1);
    for (int i = 1; i < n; ++i) {
        a.pb((s[i] == 'A' ? 1 : -1));
    }
    // se
    if (a[n-1] == 1) return false;
    int cp = a[n-1], mnp = a[n-1];
    for (int i = n-2; i >= 0; --i) {
        int ncp = cp + a[i];
        int nmnp = min(ncp, mnp + a[i]);
        swap(cp, ncp), swap(nmnp, mnp);
        if (mnp > 0) return false;
    }
    return true;
}

int dp[3050][3050][2];

int brute(int n, string s) {
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) dp[i][j][0] = dp[i][j][1] = -1;
    auto win = [&] (int l, int r, int tipo) {
        if (min(l, r) < 0 or max(l, r) >= n or l > r) return tipo^1;
        return dp[l][r][tipo];
    };
    for (int l = n-1; ~l; --l) {
        for (int r = l; r < n; ++r) {
            for (int k = l; k <= r; ++k) {
                if (s[k] == 'A') dp[l][r][0] = 1;
                if (s[k] == 'B') dp[l][r][1] = 0;
            }
            for (int k = l; k <= r; ++k) {
                if (s[k] == 'A' and win(k+1, r, 1) == false) dp[l][r][0] = false;
                if (s[k] == 'B' and win(l, k-1, 0) == true) dp[l][r][1] = true;
            }
            if (dp[l][r][0] == -1) dp[l][r][0] = dp[l][r][1];
            if (dp[l][r][1] == -1) dp[l][r][1] = dp[l][r][0];
        }
    }

    return dp[0][n-1][0];
}

int32_t main() {_
#ifndef gato
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": ";
        int n; string s; cin >> n >> s;
        cout << (!solve(n, s) ? "Alice" : "Bob") << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(1,30);
        string s(n, 'A');
        for (auto& x : s) if (rnd(0, 5)) x = 'B';
        int my = solve(n, s), ans = brute(n, s);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << endl << s << endl;
            cout << "Your output: " << (!my ? "Alice" : "Bob") << endl;
            cout << "Answer: " << (!ans ? "Alice" : "Bob") << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
