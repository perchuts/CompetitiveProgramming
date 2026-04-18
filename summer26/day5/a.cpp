#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back
using namespace std;

using ll = long long;
const int mod = (119<<23)+1;
void solve() {
	string n, m; cin >> n >> m;
	int t1 = n.size(), t2 = m.size();
	if (t1 < t2) swap(t1, t2), swap(n, m);
	vector<int> p10(t1+1, 1), invp10(t1+1, 1);
	auto fexp = [&] (int b, int e) {
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % mod;
			e /= 2, b = b * b % mod;
		}
		return ans;
	};
	for (int i = 1; i <= t1; ++i) p10[i] = 10 * p10[i-1] % mod;
	invp10[t1] = fexp(p10[t1], mod-2);
	for (int i = t1-1; ~i; --i) invp10[i] = 10 * invp10[i+1] % mod;
	int ans = 0;
	// tamanho menor, pode qualquer merda ai
	for (int t = 2; t < t2; ++t) {
		ans = (ans + p10[t-2]*81) % mod;
		ans = (ans + mod - p10[(t-1)/2]*9) % mod;
	}
	vector<int> suf(t2+2);
	for (int i = t2; i >= 1; --i) {
		int ways = (m[t2-i] - '0');
		if (i == t2 or i == 1) ways = min(ways-1, 0LL);
		suf[i] = (suf[i+1] + ways * p10[i-1]) % mod;
	}
	for (int quebra = 1; quebra <= t2; ++quebra) {
		int ways = (n[quebra-1] - '0');
		if (quebra == 1 or quebra == t2) ways = min(ways-1, 0LL);
		ways = ways * (suf[quebra+1] * inv10[quebra]) % mod;
		int pode = min(n[quebra-1], m[t2-quebra]) - '0';
		if (quebra == 1 or quebra == t2) pode = min(pode-1, 0LL);
		ways = (ways + pode) % mod;
		// pref de tamanho quebra-1 eh do n
		// sufixo de tamanho t2-quebra+1 eh do m
		if (m[t2-quebra] < n[quebra-1]) {

		}
		ans = (ans + ways) % mod;
	}
	if (n[t2-1] != '0') {
		bool ok = 1;
		for (int i = 0; i < t2; ++i) {
			if (n[t2-1-i] != m[i]) {
				ok = (n[t2-1-i] > m[i]);
				break;
			}
		}
		if (ok) ans = (ans + 1) % mod;
	}
	int pal = 0, ok = 1;
	for (int quebra = 1; quebra <= t2/2; ++quebra) {
		if (n[quebra-1] != m[quebra-1]) {
			if (n < m) swap(n, m);
			// basta iterar ate onde vou seguir o m
			for (int segue = quebra; segue <= (t2+1)/2; ++segue) {
				int ways = m[segue-1] - '0' - (segue==1);
				pal = (pal + ways) % mod;
			}
			if (t2 % 2) pal = (pal + 1) % mod;
			ok = 0;
			break;
		}
		int ways = min(n[quebra-1], m[quebra-1]) - '0';
		if (quebra == 1) ways--;
		ways = ways * p10[(t2+1)/2 - quebra] % mod;
		pal = (pal + ways) % mod;
	}
	if (ok) {

	}
}
int32_t main() {_
	int t; cin >> t;
	while (t--) solve();
}
