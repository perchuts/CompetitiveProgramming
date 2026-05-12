#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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

int p;

inline void add(int& x, int y) {
    x += y;
    if (x >= p) x -= p;
}

int dp[2][3001], row[2][3001], ps[3001];

void solve() {
    int n, k; cin >> n >> k >> p;
    for (int i = 0; i <= k; ++i) row[1][i] = dp[1][i] = 0;
    row[1][0] = 1;
    for (int z = 0; z < n; ++z) {
        int turn = z&1, nturn = turn^1;
        ps[0] = dp[nturn][0];
        for (int i = 1; i <= k; ++i) ps[i] = ps[i-1], add(ps[i], dp[nturn][i]), dp[turn][i] = row[turn][i] = 0;
        row[turn][0] = ps[k];
        for (int i = 0; i <= k; ++i) add(row[turn][0], row[nturn][i]), add(ps[i], row[nturn][i]);
        add(row[turn][0], p-ps[0]);
        for (int i = 1; i <= k; ++i) {
            add(row[turn][i], ps[k-i]);
            add(row[turn][i], p-row[nturn][k-i]);
            add(row[turn][i], p-ps[i]);
            add(dp[turn][i], ps[i]);
        }
        dp[turn][0] = ps[0];
        for (int i = 1; i <= k; ++i) add(row[turn][i], row[turn][i-1]);
    }
    int ans = 0, turn = (n^1)&1;
    for (int i = 0; i <= k; ++i) add(ans, dp[turn][i]), add(ans, row[turn][i]);
    cout << ans << endl;
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
