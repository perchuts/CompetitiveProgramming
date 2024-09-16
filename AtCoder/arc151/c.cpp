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

void solve(){
 	int n, m; cin >> n >> m;
	if (m == 0) {
		cout << (n&1 ? "Takahashi" : "Aoki") << endl;
		return;
	}
	vector<ii> v(m);
	for (auto& [x,y] : v) cin >> x >> y;
	int xx = 0;
	for (int i = 0; i < m - 1; ++i) {
		if (v[i+1].first == v[i].first+1) continue;
		if (v[i].second == v[i+1].second) xx ^= 1;
	}
	xx ^= (v[0].first-1);
	xx ^= (n-v.back().first);
	cout << (xx ? "Takahashi" : "Aoki") << endl;
	return;
}

//bool dp[10*maxn][20];
//bool mark[10*maxn][20];
//int pot[maxn];
//
//bool solve(int mask, int tam) {
//	if (mark[mask][tam]) return dp[mask][tam];
//	mark[mask][tam] = 1;
//	vector<int> pos;
//	int tt = mask;
//	for (int i = 0; i < tam; ++i) pos.pb(tt%3), tt /= 3;
//	bool win = 0;
//	for (int i = 0; i < tam; ++i) {
//		if (pos[i]) continue;
//		int esq = (i == 0 ? 0 : pos[i-1]), dir = (i == tam-1 ? 0 : pos[i+1]);
//		int tmp = mask + pot[i];
//		if (esq != 1 && dir != 1 && solve(tmp, tam) == 0) {
//			win = 1; break;
//		}
//		tmp += pot[i];
//		if (esq != 2 && dir != 2 && solve(tmp, tam) == 0) {
//			win = 1; break;
//		}
//	}
//	return dp[mask][tam] = win;
//}

int32_t main(){_
	solve();
	exit(0);
//	pot[0] = 1;
//	for (int i = 1; i <= 20; ++i) pot[i] = 3 * pot[i-1];
//	for (int i = 1; pot[i] <= 10*maxn; ++i) 
//		for (int j = 0; j < pot[i]; ++j) solve(j, i);
//	while (true) {
//		cout << "Make a new query: " << endl;
//		int n, m; cin >> n >> m;
//		assert(pot[n] <= 10*maxn);
//		int mask = 0;
//		for (int i = 0; i < m; ++i) {
//			int x, val; cin >> x >> val;
//			mask += pot[x-1] * (val+1);
//		}
//		cout << (dp[mask][n] ? "First" : "Second") << endl;
//	}
	vector<vector<int>> dp(2000, vector<int>(9));
	auto mask = [&] (int a, int b) {
		return a + 3 * b;
	};
	for (int i = 1; i <= 100; ++i) {
		for (int j = 0; j < 9; ++j) {
			vector<int> vals(10*i+10);
			int p1 = j % 3, p2 = (j/3)%3;
			if (i == 1) {
				if (p1 != p2 && max(p1, p2) != 2) {}
				else dp[i][j] = 1;
				continue;
			}
			
			if (p1 != 0) vals[dp[i-1][mask(0, p2)]] = 1;
			if (p1 != 1) vals[dp[i-1][mask(1, p2)]] = 1;
			if (p2 != 0) vals[dp[i-1][mask(p1, 0)]] = 1;
			if (p2 != 1) vals[dp[i-1][mask(p1, 1)]] = 1;

			for (int w = 1; w < i-1; ++w) {
				for (int ww = 0; ww < 2; ++ww) {
					int xx = dp[w][mask(p1, ww)] ^ dp[i-w-1][mask(ww, p2)];
					if (xx < 10*i + 10) vals[xx] = 1;
				}
			}
			for (int p = 0; ; ++p) {
				if (vals[p] == 0) {
					dp[i][j] = p;
					break;
				}
			}
		}
	}
	for (int i = 0; i <= 100; ++i) {
		cout << "i = " << i << ": ";
		assert(dp[i][0] == dp[i][4]);
		assert(dp[i][3] == dp[i][1]);
		assert(dp[i][2] == dp[i][6] && dp[i][6] == dp[i][5] && dp[i][5] == dp[i][7]);
		cout << dp[i][0] << ' ' << dp[i][3] << ' ' << dp[i][2] << ' ' << dp[i][8] << endl;
	}

}	
