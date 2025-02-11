#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
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

int solve(int n, int x, vector<int> v){
	vector<int> coeffs;
	for (int i = n-1; ~i; --i) {
		coeffs.push_back(x/v[i]);
		x %= v[i];
	}
	reverse(all(coeffs));
	vector dp(n+1, vector(3, vector(3, inf*inf)));
	dp[n][0][0] = 0;
	int ans = inf*inf;
	for (int i = n-1; ~i; --i) {
		for (int a = 0; a < 3; ++a) {
			for (int b = 0; b < 3; ++b) {
				for (int c = 0; c < 3; ++c) {
					int c1 = 0, c2 = 0;
					if (a == 1) c1 = -1;
					if (a == 2) c1 = 1;
					if (i < n-1) {
						if (b == 1) c2 = v[i+1] / v[i];
						if (b == 2) c2 = - v[i+1] / v[i];
					}
					ckmin(dp[i][a][b], dp[i+1][b][c] + abs(coeffs[i] + c1 + c2)); 
				}	
				if (i == 0 and a == 0) ckmin(ans, dp[i][a][b]);
			}
		}
	}
	return ans;
}

int brute(int n, int x, vector<int> v) {
	map<int, int> dp;
	queue<int> q;
	for (auto w : v) q.push(w), dp[w] = 1; 
	while (!q.empty()) {
		auto u = q.front();
		q.pop();
		if (u > 8e18) continue;
		if (u == x) return dp[u];
		for (auto w : v) {
			if (dp.count(u+w) == false) {
				dp[u+w] = dp[u]+1, q.push(u+w);
				if (u + w == x) return dp[u]+1;
			}
			if (u-w >= 0 and dp.count(u-w) == false) {
				if (u-w == x) return dp[u]+1;
				dp[u-w] = dp[u]+1, q.push(u-w);
			}
		}
	}
	assert(false);
	return 69;
	
}

int32_t main(){_
#ifdef stress
	int t = 1;
	while (true) {
		vector<int> vals = {1};
		int lim = 1000;
		int x = rnd(1, lim);
		while (2*vals.back() <= 1e18) {
			int flip = rnd(0, 3);
			if (!flip) break;
			int choice = rnd(2, 1e18/vals.back());
			vals.pb(vals.back()*choice);
		}
		int n = sz(vals);
		int my = solve(n, x, vals);
		int br = brute(n, x, vals);
		if (my != br) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << ' ' << x << endl;
			for (auto y : vals) cout << y << ' ';
			cout << endl;
			cout << "Your output: " << my << endl;
			cout << "Answer: " << br << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#else
	int n, x; cin >> n >> x;
	vector<int> v(n);
	for (auto& y : v) cin >> y;
	cout << solve(n, x, v) << endl;
#endif
}
