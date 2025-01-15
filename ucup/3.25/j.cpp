#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'
#define int ll
//#define stress

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

int solve(int n1, int n2, int m, int k, vector<ii> pairs){
	vector<vector<int>> adj(m, vector<int>(m));
	vector<int> cover(1<<m), alone(m, 1);
	int skip = 0, forced = 0, lixo = 0, edg = k;
	for (auto& [x, y] : pairs) {
		if (adj[x][y]) edg--;
		adj[x][y] = adj[y][x] = 1;
		alone[x] = alone[y] = 0;
	}
	for (int i = 0; i < m; ++i) {
		if (adj[i][i]) forced += 1 << i, --edg;
		if (alone[i]) lixo++, skip += 1 << i;
	}
	vector<vector<array<int, 2>>> dp(1<<m, vector<array<int, 2>>(m+1));
	for (int i = 1; i < (1 << m); ++i) {
		if (i & skip) continue;
		int bit = -1;
		for (int j = 0; j < m; ++j) if (i >> j & 1) { bit = j; break; } 
		for (int j = 0; j < m; ++j) {
			if (j != bit and adj[bit][j] and (((i >> j) & 1) == 0)) cover[i]++;
		}
		cover[i] += cover[i - (1 << bit)];
	}
	vector<int> invfact(m+1, 1);
	auto fexp = [&] (int b, int e) {
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % mod;
			b = b * b % mod, e /= 2;
		}
		return ans;
	};
	for (int i = 2; i <= m; ++i) invfact[i] = fexp(i, mod-2) * invfact[i-1] % mod; 
	auto ncr = [&] (int a, int b) {
		if (a < b) return 0ll;
		int ans = 1;
		for (int i = a-b+1; i <= a; ++i) ans = ans * i % mod;
		ans = ans * invfact[b] % mod;
		return ans;
	};
	int ans = 0;
	for (int i = 1; i < (1 << m); ++i) {
		if (skip & i) continue;
		if (cover[i] == edg and ((forced & i) == forced)) {
			int tam = __builtin_popcount(i);	
			dp[i][m][0] = ncr(n1-tam+(tam+lixo-1), tam+lixo-1);
			dp[i][m][1] = ncr(n2-tam+(tam+lixo-1), tam+lixo-1);
		}
		for (int j = m-1; j >= 0; --j) {
			if (i >> j & 1) {
				dp[i][j][0] = (dp[i][j+1][0] + dp[i-(1<<j)][j+1][0]) % mod;	
				dp[i][j][1] = (dp[i][j+1][1] + dp[i-(1<<j)][j+1][1]) % mod;	
			} else {
				dp[i][j][0] = dp[i][j+1][0];
				dp[i][j][1] = dp[i][j+1][1];
			}
		}
		int tt = m - lixo - __builtin_popcount(i);
		int cnt = dp[i][0][1] * dp[i][0][0] % mod;
		if (tt & 1) ans = (ans + mod - cnt) % mod;
		else ans = (ans + cnt) % mod;
	}
	return ans;
}

int mvkaio(int n1, int n2, int m, int k, vector<ii> pairs) {
	vector<vector<int>> ncr(max(n1, n2) + 10, vector<int>(max(n1, n2) + 10));
	for (int i = 0; i <= max(n1, n2); ++i) {
		for (int j = 0; j <= i; ++j) {
			if (i == j or j == 0) ncr[i][j] = 1;
			else ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
		}
	}
	int ans = 0;
	for (int i = 1; i < (1 << m); ++i) {
		for (int j = 1; j < (1 << m); ++j) {
			bool ok = 1;
			for (auto [x, y] : pairs) {
				bool okk = 0;
				okk |= (((i >> x) & 1) and ((j >> y) & 1));
				okk |= (((j >> x) & 1) and ((i >> y) & 1));
				ok &= okk;
			}
			int c1 = __builtin_popcount(i), c2 = __builtin_popcount(j);
			if (ok == false or c1 > n1 or c2 > n2) continue;
			ans += ncr[n1-1][c1-1] * ncr[n2-1][c2-1];
		}
	}
	return ans;
}

int32_t main(){_
#ifndef stress
  int t = 1; cin >> t;
  while(t--) {
	  int n1, n2, m, k; cin >> n1 >> n2 >> m >> k;
	  vector<ii> pairs(k);
	  for (auto& [x, y] : pairs) cin >> x >> y, --x, --y;
	  cout << solve(n1, n2, m, k, pairs) << endl;
	  //cout << mvkaio(n1, n2, m, k, pairs) << endl;
  }
#else 
  int t = 1;
  while (true) {
	  int n1 = rnd(1, 10), n2 = rnd(1, 10), m = rnd(1, 10), k = rnd(1, m*m);
	  vector<ii> pairs(k);
	  for (auto& [x, y] : pairs) x = rnd(0, m-1), y = rnd(0, m-1);
	  int my = solve(n1, n2, m, k, pairs);
	  int brute = mvkaio(n1, n2, m, k, pairs);
	  if (my != brute) {
		cout << "Wrong answer on test " << t << endl;
		cout << 1 << endl;
		cout << n1 << ' ' << n2 << ' ' << m << ' ' << k << endl;
		for (auto [x, y] : pairs) cout << x + 1 << ' ' << y + 1 << endl;
		cout << "Your output: " << my << endl;
		cout << "Answer: " << brute << endl;
		exit(0);
	  }
	  cout << "Accepted on test " << t++ << endl;
  }
#endif
}
