#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int l, r; cin >> l >> r;
	const int LCM = 2520;
	auto f = [&] (int x) {
		if (x <= 0) return 0LL;
		// dp[digito][mod][seguindo o x ou nao][quem apareceu]
		vector dp(20, vector(LCM, vector(2, vector(512, 0LL))));
		int temp = x;
		vector<int> xd;
		while (temp) xd.push_back(temp%10), temp /= 10;	
		vector<int> pot(20, 1);
		for (int i = 1; i < 20; ++i) pot[i] = (10 * pot[i-1]) % LCM;
		dp[xd.size()][0][1][0] = 1;
		for (int pos = (int)xd.size() - 1; ~pos; --pos) {
			int x_digit = xd[pos];
			for (int mod = 0; mod < LCM; ++mod) {
				for (int mask = 0; mask < 512; ++mask) {
					for (int digit = 0; digit < 9; ++digit) {
						int& DP0 = dp[pos][mod][0][mask];
						int& DP1 = dp[pos][mod][1][mask];
						if (mask >> digit & 1) {
							int val = (digit+1) * pot[pos] % 2520;	
							if (val == mod and pos < (int)xd.size()-1 and mask == (1 << digit)) DP0 += 1;
							if (digit+1 == x_digit) {
								// igual
								DP1 = (dp[pos+1][(mod-val+LCM)%LCM][1][mask] + dp[pos+1][(mod-val+LCM)%LCM][1][mask-(1<<digit)]); 
								DP0 += (dp[pos+1][(mod-val+LCM)%LCM][0][mask] + dp[pos+1][(mod-val+LCM)%LCM][0][mask-(1<<digit)]); 
							} else if (digit+1 < x_digit) {
								// menor
								DP0 += (dp[pos+1][(mod-val+LCM)%LCM][1][mask] + dp[pos+1][(mod-val+LCM)%LCM][1][mask-(1<<digit)]); 
								DP0 += (dp[pos+1][(mod-val+LCM)%LCM][0][mask] + dp[pos+1][(mod-val+LCM)%LCM][0][mask-(1<<digit)]); 
							} else {
								// maior
								DP0 += (dp[pos+1][(mod-val+LCM)%LCM][0][mask] + dp[pos+1][(mod-val+LCM)%LCM][0][mask-(1<<digit)]); 
							}
						}

					}
				}
			}
		}
		int ans = 0;
		for (int i = 1; i < 512; ++i) {
			for (int mod = 0; mod < LCM; ++mod) {
				bool ok = 1;
				for (int digit = 0; digit < 9; ++digit) {
					if (i >> digit & 1) ok &= (mod % (digit+1) == 0); 
				}
				if (ok) ans += dp[0][mod][0][i] + dp[0][mod][1][i];
			}
		}
		return ans;
	};
	cout << f(r) - f(l-1) << endl;
}
