#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
    int n; cin >> n;
    vector<int> a(n);
    vector<int> hash(300);
    for (int i = 2; i < 10; ++i) hash[char('0'+i)] = i;
    hash['A'] = 1;
    hash['T'] = 10;
    hash['J'] = 11;
    hash['Q'] = 12;
    hash['K'] = 13;
    vector<int> cnt(20);
    for (auto& x : a) {
        char c; cin >> c;
        x = hash[c];
        cnt[x]++;
    }
    sort(all(a));
    int ans = 0;
    for (int l = 1, r = 1; l <= 13; l = r) {
        if (cnt[l] == 0) { r++; continue; }
        while (cnt[r]) r++;
        int ways = 1;
        for (int i = l; i < r; ++i) ways *= cnt[i];
        if (r-l >= 3) ans += ways * (r-l);
    }
    vector<vector<int>> dp(n+1, vector<int>(16));
    dp[0][0] = 1;
    for (auto& x : a) x = min(x, 10LL);
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i-1];
        for (int j = a[i-1]; j <= 15; ++j) dp[i][j] += dp[i-1][j-a[i-1]];
    }
    ans += dp[n][15] * 2;
    for (int i = 0; i < 20; ++i) ans += cnt[i] * (cnt[i]-1);
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
