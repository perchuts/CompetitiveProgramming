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

void solve(){
	int n, m; cin >> n >> m;
	vector<vector<int>> v(m, vector<int>(n)), rank(m, vector<int>(n));
	vector suff_best = vector(m, vector(n, vector(m, inf)));
	vector my_best = vector(m, vector(n, inf));
	for (auto& x : v) for (auto& y : x) cin >> y, -- y;
	for (int j = 0; j < m; ++j) for (int i = 0; i < n; ++i) rank[j][v[j][i]] = i;	
	for (int j = 0; j < m; ++j) {
		for (int i = n - 1; i >= 0; --i) {
			for (int k = 0; k < m; ++k) {
				if (i != n-1) suff_best[j][i][k] = suff_best[j][i+1][k];
				ckmin(suff_best[j][i][k], rank[k][v[j][i]]);
				ckmin(my_best[k][v[j][i]], suff_best[j][i][k]);	
			}
		}
	}
	vector bl = vector(17, vector(n, vector(m, inf)));
	for (int pot = 0; pot < 17; ++pot) {
		for (int i = 0; i < n; ++i) {
			if (pot == 0) {
				for (int k = 0; k < m; ++k) bl[0][i][k] = my_best[k][i];
			} else {
				for (int k = 0; k < m; ++k) {
					int val = v[k][bl[pot-1][i][k]];
					for (int k2 = 0; k2 < m; ++k2) ckmin(bl[pot][i][k2], bl[pot-1][val][k2]);
				}
			}
		}
	}
	int q; cin >> q;
	while (q--) {
		int U, V; cin >> U >> V;
		U--, V--;
		vector<int> my_t(m);
		for (int i = 0; i < m; ++i) my_t[i] = rank[i][U];
		int ans = 0;
		for (int j = 0; j < m; ++j) {
			if (my_t[j] < rank[j][V]) {
				ans = 1;
			}
		}
		if (ans == 1) {
			cout << ans << endl;
			continue;
		}	
		for (int pot = 16; pot >= 0; --pot) {
			bool ok = 1;
			vector<int> nt(m, 1e18);
			for (int j = 0; j < m; ++j) {
				int val = v[j][my_t[j]];	
				for (int k = 0; k < m; ++k) ckmin(nt[k], bl[pot][val][k]);
			}
			for (int j = 0; j < m; ++j) ok &= (nt[j] > rank[j][V]);
			if (ok) swap(my_t, nt), ans += (1 << pot);
		}	
		bool ok = 0;
		vector<int> nt(m, 1e18);
		for (int j = 0; j < m; ++j) {
			int val = v[j][my_t[j]];	
			for (int k = 0; k < m; ++k) ckmin(nt[k], bl[0][val][k]);
		}
		for (int j = 0; j < m; ++j) ok |= (nt[j] < rank[j][V]);
		cout << (ok ? ans + 2 : -1) << endl;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
