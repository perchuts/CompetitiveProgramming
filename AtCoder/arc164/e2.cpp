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
    int n, q; cin >> n >> q;
    vector<int> w(n+1);
    int aa = 0;
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r;
        w[l-1]++;
        w[r]++;
        if (l == r) aa++;
    }
    if (n == 2) {
        cout << 2*aa << endl;
        exit(0);
    }
	vector<int> nw;
	for (int i = 1; i < n; ++i) if (w[i] != 0) nw.pb(w[i]);
	n = sz(nw);
	swap(w, nw);
    int tot = 1, d = 1;
    while (tot < n) tot = 2 * tot + 1, d++;
    int skip = tot - n;
	cout << tot << ' ' << skip << endl;
    cout << d << ' ';
    vector<vector<int>> dp(tot+1, vector<int>(skip+1, inf));
    dp[0][0] = 0;
    for (int i = 1; i <= tot; ++i) {
        for (int j = 0; j <= skip; ++j) {
            int act = i - j - 1;
            if (act >= n or act < 0) continue;
            dp[i][j] = dp[i-1][j] + (i&1 ? w[act] : 0);
            if (j and i % 2 == 1) ckmin(dp[i][j], dp[i-1][j-1]);
        }
    }
    cout << 2*dp[tot][skip] << endl;
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
