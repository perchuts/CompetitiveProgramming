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
    string a, b; cin >> a >> b;
    int n = sz(a)/2;
    vector<int> A, B;
    int ca = 0, cb = 0;
    for (int i = 0; i < 2*n; ++i) {
        if (a[i] == 'U') ca++;
        else A.pb(ca);
        if (b[i] == 'U') cb++;
        else B.pb(cb);
    }
	vector<vector<vector<int>>> occ(2, vector<vector<int>>(2, vector<int>(n+1, -1)));
	for (int i = 0; i < n; ++i) {
		if (occ[0][0][A[i]] == -1) occ[0][0][A[i]] = i;
		if (occ[1][0][B[i]] == -1) occ[1][0][B[i]] = i;
		occ[0][1][A[i]] = i;
		occ[1][1][B[i]] = i;
	}
	vector<int> dp(n+1, inf);
	int opt = 0;
	for (int i = 1; i <= n; ++i) {
		int l1 = occ[0][0][i], l2 = occ[1][0][i], r1 = occ[0][1][i], r2 = occ[1][1][i];
		if (l1 == -1 or l2 == -1) continue;
		int bc = abs(l1-l2) + 2*min(l1,l2);
		dp[i] = opt + bc;
		int ac = dp[i] - 2*(min(r1,r2)+1);
		opt = min(opt, ac);
	}
	cout << dp[n] << endl;
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
