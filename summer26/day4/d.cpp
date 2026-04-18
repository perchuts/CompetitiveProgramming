#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
//#define gato

using namespace std;

using ll = long long;

const int mod = (119<<23)+1;
bitset<100000001> np;
int solve(int n) {
	vector<int> pares = {0, 4, 6, 8};
	vector<int> impares = {1, 9};
	int N = 1000600;
	vector<int> dp1(N), dp9(N), p3(N, 1), p4(N, 1);
	for (int i = 1; i < N; ++i) p3[i] = 3 * p3[i-1] % mod, p4[i] = p4[i-1] * 4 % mod;
	// 9
	dp9[1] = 1;
	// 1
	dp1[1] = 1;
	for (int i = 2; i < N; ++i) {
		// 4[6]*9
		dp9[i] = 1;
		// 8[0]*1
		dp1[i] = 1;
		// [6,9]1 [0,6,9]* 9
		dp9[i] = (dp9[i] + 2 * p3[i-2]) % mod;
	}
	// 91
	dp1[2]++;
	// 901, 981
	dp1[3] += 2;
	// 9801, 9081
	dp1[4] += 2;
	// agora faz 6, 0, 9 e ve se da
	// 649, 949
	dp9[3] += 2;
	// 6049, 6649, 9469
	dp9[4] += 3;
	// 60049, 66049, 66649, 94669
	dp9[5] += 4;
	// 600049, 660049, 666049
	dp9[6] += 3;
	// 6000049, 6600049, 6660049
	dp9[7] += 3;
	int ans = 3 * p4[n-1] % mod;
	for (int i = 1; i <= n; ++i) {
		int ways1 = dp1[i] * p4[n-i] % mod;
		int ways9 = dp9[i] * p4[n-i] % mod;
		ans = (ans + ways1 + ways9) % mod;
	}
	return ans;
}
int brute(int n) {
	vector<int> p10(n+1, 1);
	for (int i = 1; i <= n; ++i) p10[i] = 10 * p10[i-1];
	vector<int> dp(p10[n]+1, 1);
	int ans = 0;
	for (int i = 1; i < p10[n]; ++i) {
		string s = to_string(i);
		if (np[i] == 0) {
			dp[i] = 0;
			continue;
		}
		auto remover = [&] (int id) {
			int pw = 0;
			int val = 0;
			for (int i = s.size()-1; ~i; --i) {
				if (id == i) continue;
				val += (s[i] - '0') * p10[pw++];
			}
			return val;
		};
		for (int j = 0; j < s.size(); ++j) {
			if (dp[remover(j)] == 0) { dp[i] = 0; break; }
		}
		if (s.size() == n) {
			//if (dp[i] and (s.back() == '9' or s.back() == '1')) cout << i << endl;
			ans += dp[i];
		}
	}
	return ans;
}
int32_t main() {_
#ifndef gato
	int n; cin >> n;
	cout << solve(n) << endl;
	exit(0);
#else
	for (int i = 1; i <= 8; ++i) {
		cout << "n = " << i << ": ";
		cout << solve(i) << " " << brute(i) << endl;
	}
#endif
}
