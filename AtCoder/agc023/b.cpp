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
// String Hashing
//
// Complexidades:
// construtor - O(|s|)
// operator() - O(1)

int uniform(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
 
template<int MOD> struct str_hash {
	static int P;
	vector<ll> h, p;
	str_hash(string s) : h(s.size()), p(s.size()) {
		p[0] = 1, h[0] = s[0];
		for (int i = 1; i < s.size(); i++)
			p[i] = p[i - 1]*P%MOD, h[i] = (h[i - 1]*P + s[i])%MOD;
	}
	ll operator()(int l, int r) { // retorna hash s[l...r]
		ll hash = h[r] - (l ? h[l - 1]*p[r - l + 1]%MOD : 0);
		return hash < 0 ? hash + MOD : hash;
	}
};
template<int MOD> int str_hash<MOD>::P = uniform(256, MOD - 1); // l > |sigma|
void solve() {
    int n; cin >> n;
    vector<string> grid(n);
    for (auto& x : grid) cin >> x;
    vector<string> rows, cols;
    vector<str_hash<998244853>> r1, c1;
    vector<str_hash<998244353>> r2, c2;
    for (int i = 0; i < n; ++i) {
        rows.pb(grid[i] + grid[i]);
        string col;
        for (int j = 0; j < n; ++j) col += grid[j][i];
        col += col;
        cols.pb(col);
        r1.pb(str_hash<998244853>(grid[i]+grid[i]));
        c1.pb(str_hash<998244853>(col));
        r2.pb(str_hash<998244353>(grid[i]+grid[i]));
        c2.pb(str_hash<998244353>(col));
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            bool ok = 1;
            for (int k = 0; k < n and ok; ++k) {
                int row = i + k, col = j + k;
                if (row >= n) row -= n;
                if (col >= n) col -= n;
                ok &= (r1[row](j, j+n-1) == c1[col](i, i+n-1));
                ok &= (r2[row](j, j+n-1) == c2[col](i, i+n-1));
            }
            ans += ok;
        }
    }
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
