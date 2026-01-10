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
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> dp(n+1), rec(n+1);
    int cur = 0, opt = -1e18;
    for (int i = 1; i <= n; ++i) {
        dp[i] = -1e18;
        for (int j = i-2; j >= 0; j -= 2) {
            if (ckmax(dp[i], dp[j] + a[i-1])) rec[i] = j;
        }
        if (ckmax(dp[i], a[i-1])) rec[i] = 0;
        if (ckmax(opt, dp[i])) cur = i;
    }
    vector<int> mark(n);
    while (cur) mark[cur-1] = 1, cur = rec[cur];
    vector<int> ops;
    while (sz(mark) != 1) {
        if (mark[0] == 0) {
            mark.erase(begin(mark));
            ops.pb(1);
            continue;
        }
        if (mark.back() == 0) {
            ops.pb(sz(mark));
            mark.erase(begin(mark)+sz(mark)-1);
            continue;
        }
        if (mark[2] == 1) {
            mark.erase(begin(mark));
            mark.erase(begin(mark));
            ops.pb(2);
        } else {
            mark.erase(begin(mark)+1);
            mark.erase(begin(mark)+1);
            ops.pb(3);
        }
    }
    cout << opt << endl;
    cout << sz(ops) << endl;
    for (auto x : ops) cout << x << endl;
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
