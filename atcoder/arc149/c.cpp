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
 	int n; cin >> n;
	if (n % 2) {
		vector<vector<int>> ans(n, vector<int>(n));
		vector<int> mark(n*n+1);
		ans[n/2][n/2] = 7, ans[n/2-1][n/2+1] = 1, ans[n/2][n/2+1] = 8, ans[n/2+1][n/2] = 2;
		mark[7] = mark[1] = mark[2] = mark[8] = 1;
		int act = 1;
		for (int i = 0; i < n; ++i) {
			if (i == n/2 || i == n/2+1) continue;
			while (mark[act]) act += 2;
			int shift = (i < n/2);
			ans[n/2-1+shift][i] = act;
			ans[n/2-1+shift+1][i] = act*2;
			assert(mark[act*2] == 0);
		    mark[act*2] = 1;
			mark[act] = 1;
		}
		act = 1;
		for (int i = 0; i < n/2; ++i) {
			for (int j = 0; j < n; ++j) {
				if (ans[i][j]) continue;
				while (mark[act]) act += 2;
				ans[i][j] = act;
				mark[act] = 1;
			}
		}
		act = 2;
		for (int i = n/2+1; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (ans[i][j]) continue;
				while (mark[act]) act += 2;
				ans[i][j] = act;
				mark[act] = 1;
			}
		}
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) cout << ans[i][j] << " \n"[j==n-1];
	} else {
		vector<vector<int>> ans(n, vector<int>(n));
		vector<int> mark(n*n+1);
		int act = 1;
		for (int i = 1; i <= 2 * n - 1; i += 2) {
			ans[n/2-1][i/2] = i;
			mark[i] = 1;
		}
		for (int i = 0; i < n / 2 - 1; ++i) {
			for (int j = 0; j < n; ++j) {
				while (mark[act]) act += 2;
				ans[i][j] = act;
				mark[act] = 1;
			}
		}
		ans[n/2][0] = 14, ans[n/2][1] = 6, ans[n/2][2] = 10, ans[n/2][3] = 2;
		mark[14] = mark[6] = mark[10] = mark[2] = 1;
		for (int i = 4; i < n; ++i) ans[n/2][i] = 2 * ans[n/2-1][i], mark[ans[n/2][i]] = 1;
		act = 4;
		for (int i = n/2+1; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				while (mark[act] == 1) act += 2;
				ans[i][j] = act;
				mark[act] = 1;
			}
		}

		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j) cout << ans[i][j] << " \n"[j==n-1];
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
