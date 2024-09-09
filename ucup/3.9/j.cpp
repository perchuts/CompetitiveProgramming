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

int dist[15][15][15][15];

void solve(){
 	int t, n, k, x, y; cin >> t >> n >> k >> x >> y; 
	if (x > y) swap(x, y);
	if (t == 0) {
		cout << abs(x - y) << endl;
		return;
	}
	if ((t == 1 && abs(x - y) >= k) || k == 1) {
		cout << 1 << endl;
		return;
	}
	if (k == 2) {
		if (n <= 3) cout << -1 << endl;
		else {
			t %= 2;
			if (t == 1 && x == 2 && y == 3 && n == 4) {
				cout << 3 << endl;
				return;
			}
			if (t == 0) cout << abs(x - y) << endl;
			else {
				if (abs(x - y) == 1) cout << 2 << endl;
				else cout << 1 << endl;
			}
		}
	} else if (k == 3) {
		if (n <= 11) {
			--x, --y;
			if (t >= 10) cout << -1 << endl;
			else cout << (dist[n][t][x][y] == 69 ? -1 : dist[n][t][x][y]) << endl;
		} else {
			if (t == 1) cout << 2 << endl;
			else cout << -1 << endl;
		} 	
	} else {
		if (t == 1) {
			// preciso descobrir se eh 2 ou 3
			if ((x <= k && n - k + 1 <= x) || (y <= k && n - k + 1 <= y)) cout << -1 << endl;
			else if (k < x || y <= n - k) cout << 2 << endl;
			else cout << 3 << endl;
		} else cout << -1 << endl;
	}
}

int32_t main(){_
	for (int n = 1; n <= 11; ++n) {
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) dist[n][0][i][j] = abs(i - j);
		int maxt = 9;
		for (int t = 1; t <= maxt; ++t) {
			for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
				if (dist[n][t-1][i][j] >= 3 && dist[n][t-1][i][j] != 69) dist[n][t][i][j] = 1;
				else dist[n][t][i][j] = 69;
			}
			for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
				ckmin(dist[n][t][i][j], dist[n][t][i][k] + dist[n][t][k][j]);
			}
		}
	}
	int t; cin >> t; while (t--) solve();
}
