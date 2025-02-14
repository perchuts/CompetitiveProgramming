#include <bits/stdc++.h>
using namespace std;
//#define stress
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int solve(int n, string s) {
	int N = n;
	vector<int> blocos;
	int cur = 0, ponta1 = 0, ponta2 = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '1') {
			if (cur != 0) {
				if (i == cur) ponta1 = cur; 
				else blocos.push_back(cur);
			}
			cur = 0;
		}
		else cur++;
	}
	if (cur) ponta2 = cur;
	n = blocos.size();
	vector dp(n+1, vector(2, vector(2, 0)));
	sort(rbegin(blocos), rend(blocos));
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j < 2; ++j) {
			for (int k = 0; k < 2; ++k) {
				if (j > ponta1 or k > ponta2) continue; 
				int tempo = 2 * i + j + k;
				if (i) {
					dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k] + max(0, min(1, blocos[i-1] - 2*(tempo-2))));
					dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k] + max(0, blocos[i-1] - 2*(tempo-2) - 1));
				}
				if (j) dp[i][j][k] = max(dp[i][j][k], dp[i][j-1][k] + max(0, ponta1 - tempo + 1));
				if (k) dp[i][j][k] = max(dp[i][j][k], dp[i][j][k-1] + max(0, ponta2 - tempo + 1));
			}
		}
	}
	return N - max({dp[n][0][0], dp[n][0][1], dp[n][1][0], dp[n][1][1]});
}

int brute(int n, string state) {
	vector<int> p(n); iota(begin(p), end(p), 0);
	int ans = 0;
	do {
		string s = state;
		for (int j = 0; j < n; ++j) {
			if (s[p[j]] == '0') s[p[j]] = '3';	
			for (int i = 1; i < n; ++i) {
				if (s[i] == '1' and s[i-1] == '0') s[i-1] = '2';
				if (s[i-1] == '1' and s[i] == '0') s[i] = '2';
			}
			for (int i = 0; i < n; ++i) if (s[i] == '2') s[i] = '1';
		}
		int cur = 0;
		for (auto x : s) cur += (x == '0' or x == '3');
		ans = max(ans, cur);
	} while (next_permutation(begin(p), end(p)));
	return n - ans;
}

int32_t main() {
#ifndef stress
	fast_io;
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		string s; cin >> s;
		cout << solve(n, s) << endl;
	}
#else
	int t = 1;
	while (true) {
		int n = rand() % 8 + 1;
		string s(n, '#');
		for (auto& x : s) x = char(rand()%2 + '0');
		int my = solve(n, s), br = brute(n, s);
		if (my != br) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << endl;
			cout << s << endl;
			cout << "Your output: " << my << endl;
			cout << "Answer: " << br << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#endif
}
