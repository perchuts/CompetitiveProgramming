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
 	int n, k; cin >> n >> k;
	vector<int> a(n), b = a;
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	sort(all(a)), sort(all(b));
	reverse(all(a)), reverse(all(b));
	vector<vector<int>> dp(k+1, vector<int>(k+1)), ndp = dp;
	for (int i = 2*n-1; i >= 0; --i) {
		for (int x = 0; x <= k; ++x) {
			for (int y = 0; y <= k; ++y) {
				if (i&1) {
					ndp[x][y] = 1e18;
					int id_1 = x + i/2-y, id_2 = y + (i+1)/2 - x; 
					if (i/2 < y || (i+1)/2 < x) continue;
					if (max(id_1, id_2) > n || min(id_1, id_2) < 0) continue;
					if (id_1 != n) ndp[x][y] = dp[x][y]; // banir o cara que ta em cima!
					if (y != k && id_2 != n) ckmin(ndp[x][y], dp[x][y+1] - b[id_2]); 
				} else {
					ndp[x][y] = -1e18;
					int id_1 = x + i/2-y, id_2 = y + i/2 - x; 
					if (i/2 < max(x, y)) continue;
					if (max(id_1, id_2) > n || min(id_1, id_2) < 0) continue;
					if (id_2 != n) ndp[x][y] = dp[x][y]; // banir o cara que ta em cima!
					if (x != k && id_1 != n) ckmax(ndp[x][y], dp[x+1][y] + a[id_1]); 
				}
			}
		}
		swap(dp, ndp);
	}
	cout << dp[0][0] << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
