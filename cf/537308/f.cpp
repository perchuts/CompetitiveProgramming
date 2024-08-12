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

int dp[105][105][105], qm[105][105][105];

void solve(){
	int n; cin >> n;
	vector<int> a(n), b = a;
	for (auto &x : a) cin >> x;
	for (auto &x : b) cin >> x;
	for (int i = 0; i <= n+1; ++i) for (int j = 0; j <= n+1; ++j) dp[0][i][j] = 1;
	for (int s = 1; s <= n; ++s) {
		for (int i = n-s+1; i; --i) {
			for (int j = n-s+1; j; --j) {
				if (s == 1 && a[i-1] == b[j-1]) dp[s][i][j] = 1, qm[s][i][j] = j;
				else {
					// preciso parear esse cara com alguem no meio do caminho...
					for (int k = j; k < j + s; ++k) {
						if (a[i-1] == b[k-1]) {
							if (dp[k-j][i+1][j] && dp[s-k+j-1][i+k-j+1][k+1]) dp[s][i][j] = 1, qm[s][i][j] = k;
						}
					}
				}
			}
		}
	}
	if (dp[n][1][1] == 0) {
		cout << "NO" << endl;
		return;
	}
	cout << "YES" << endl;
	auto solve = [&] (auto &&self, int s, int i, int j) -> void {
		if (s == 0) return;
		int t = qm[s][i][j];
		assert(dp[s][i][j]);
		assert(t>=j);
		cout << "S";
		self(self, t-j, i+1, j);
		cout << "C";
		self(self, s-t+j-1, i+t-j+1, t+1);
	};
	solve(solve, n, 1, 1);
	cout << endl;
}	

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
