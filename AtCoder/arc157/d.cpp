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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

int posx[maxn], posy[maxn];

void solve(){
	int n, m; cin >> n >> m;
	vector<string> grid(n);
	for (auto& x : grid) cin >> x;
	vector ps(n+1, vector(m+1, 0));
	for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
			ps[i][j] = ps[i-1][j] + ps[i][j-1] - ps[i-1][j-1] + (grid[i-1][j-1] == 'Y');
	}
	int y = ps[n][m];
	if (y&1 or y == 0) {
		cout << 0 << endl;
		return;
	}		
	y /= 2;
	vector<ii> ways;
	for (int i = 0; i < n; ++i) {
		int j = y / (i+1);
		if (y % (i+1) == 0 && j <= m) ways.pb({i, j-1});
	}
	int ans = 0;
	posx[0] = posy[0] = 1;
	for (auto [cx, cy] : ways) {
		int prod = 1, cur = 1;
		for (int i = 0; i <= cx; ++i) {
			int qnt = 0;
			while (cur <= n && qnt < 2*y / (cx+1)) qnt += ps[cur][m] - ps[cur-1][m], cur++;
			if (qnt != 2 * y / (cx+1)) {
				prod = 0;
				break;
			}
			int z = 1;
			while (cur <= n && ps[cur][m] - ps[cur-1][m] == 0) z++, cur++;
			if (i != cx) prod = prod * z % mod;
			posx[i+1] = cur;
		}
		if (prod == 0) continue;
		cur = 1;
		for (int i = 0; i <= cy; ++i) {
			int qnt = 0;
			while (cur <= m && qnt < 2*y / (cy+1)) qnt += ps[n][cur] - ps[n][cur-1], cur++;
			if (qnt != 2 * y / (cy+1)) {
				prod = 0;
				break;
			}
			int z = 1;
			while (cur <= m && ps[n][cur] - ps[n][cur-1] == 0) z++, cur++;
			if (i != cy) prod = prod * z % mod;
			posy[i+1] = cur;
		}
		if (prod == 0) continue;
		assert(posx[cx+1] == n+1 && posy[cy+1] == m+1);
		auto query = [&] (int x1, int y1, int x2, int y2) {
			return ps[x2][y2] - ps[x2][y1-1] - ps[x1-1][y2] + ps[x1-1][y1-1];
		};
		for (int i = 0; i <= cx && prod != 0; ++i) for (int j = 0; j <= cy && prod != 0; ++j) {
			if (query(posx[i], posy[j], posx[i+1]-1, posy[j+1]-1) != 2) prod = 0;
		}
		ans = (ans + prod) % mod;
	}	
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
