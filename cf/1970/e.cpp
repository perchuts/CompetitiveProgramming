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

void solve(){
	int n, m; cin >> m >> n;
	vector<int> a(m), b(m);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	vector<vector<int>> ways(2, vector<int>(2)), ans;
	auto mult = [&] (vector<vector<int>> w1, vector<vector<int>> w2) {
		vector<vector<int>> nways(2, vector<int>(2));
		for (int k1 = 0; k1 < 2; ++k1) for (int k2 = 0; k2 < 2; ++k2) for (int k3 = 0; k3 < 2; ++k3) for (int k4 = 0; k4 < 2; ++k4) {
			if (k2 == 1 and k3 == 1) continue;
			nways[k1][k4] = (nways[k1][k4] + w1[k1][k2] * w2[k3][k4]) % mod;
		}
		return nways;
	};
	--n;
	for (int i = 0; i < 30; ++i) {
		if (i == 0) {
			for (int j = 0; j < m; ++j) {
				ways[0][0] = (ways[0][0] + a[j] * a[j]) % mod;
				ways[0][1] = (ways[0][1] + a[j] * b[j]) % mod;
				ways[1][0] = (ways[1][0] + b[j] * a[j]) % mod;
				ways[1][1] = (ways[1][1] + b[j] * b[j]) % mod;
			}
		} else ways = mult(ways, ways);
		if ((n & (-n)) == (1 << i)) ans = ways;
		else if (n >> i & 1) ans = mult(ways, ans);
	}
	int resp = 0;
	if (n) {
		for (int i = 0; i < m; ++i) {
			vector<int> x1 = {a[0], b[0]}, x2 = {a[i], b[i]};
			for (int k1 = 0; k1 < 2; ++k1) for (int k2 = 0; k2 < 2; ++k2) for (int k3 = 0; k3 < 2; ++k3) for (int k4 = 0; k4 < 2; ++k4) {
				if (k1 == k2 && k1 == 1) continue;
				if (k3 == k4 && k3 == 1) continue;
				resp = (resp + x1[k1] * x2[k4] * ans[k2][k3]) % mod; 
			}
		}
	} else for (int i = 0; i < m; ++i) resp = (resp + a[0] * b[i] + a[0] * a[i] + b[0] * a[i]) % mod; 
	cout << resp << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
