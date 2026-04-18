#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'
#define gato


using namespace std;

using ll = long long;

const int maxn = 5e6 + 10;
const int maxn2 = 2e7 + 10;

int dp[maxn2];


int solve(int n) {
	if (n < maxn) return dp[n];
}
mt19937 rng(time(0));
int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
int32_t main() {_
	const int lim = 150;
	map<pair<int, int>, int> cost;
	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
	pq.push({0, 1, 0});
	cost[{1, 0}] = 0;
	const int magic = 3e5 + 30;
	while (!pq.empty()) {
		auto [d, A, B] = pq.top(); pq.pop();
		if (cost[{A, B}] != d) continue;
		cout << d << " " << A << " " << B << endl;
		for (int j = 2; j <= 13; ++j) {
			for (int k = 0; k < 2; ++k) {
				pair<int, int> eu = {A*j, j*(k+B)};
				if (eu.first * magic + eu.second > 1e12) continue;
				int oc = d + k + j + 2;
				if (!cost.count(eu) or cost[eu] > oc) cost[eu] = oc, pq.push({oc, eu.first, eu.second});
			}
		}
	}
	cout << cost.size() << endl;
	for (int i = 1; i < maxn2; ++i) {
		dp[i] = dp[i-1] + 1;
		for (int j = 2; j <= min(i, 13LL); ++j) {
			if (i % j == 0) dp[i] = min(dp[i], dp[i/j] + j + 2);
		}
	}
	//int n; cin >> n;
	int n = rnd(1e7, 2e7);
	cout << "n = " << n << endl;
	if (n < maxn) {
		cout << dp[n] << endl;
		exit(0);
	}
	int ans = 300;
	for (auto [par, val] : cost) {
		auto [A, B] = par;
		// Ax + B == N
		// x == (N-B)/A
		if (B > n or n % A != B % A) continue;
		ans = min(ans, val + dp[(n-B)/A]);
	}
	cout << ans << endl;
	cout << dp[n] << endl;
}
