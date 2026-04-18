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
	// tamanho igual ao maximo
	vector<int> suf(t2+2), ok(t2+1, 1);
	for (int i = 1; i <= t2; ++i) {
		if (n[i-1] == m[t2-i]) ok[i] = ok[i-1];
		else ok[i] = (n[i-1] > m[t2-1-i]);
	}
	// suf[i] = quebrar no ponto i ou depois
	for (int i = t2; i >= 1; --i) suf[i] = (suf[i+1] + (m[t2-i] - '0' - (i == t2)) * p10[i-1]) % mod;
	for (int quebra = 1; quebra <= t2; ++quebra) {
		int ways = (n[quebra-1] - '0' - (quebra == 1 or quebra == t2)) * suf[quebra+1] % mod * invp10[quebra] % mod;
		int k = min<int>(n[quebra-1] - (quebra == 1), m[t2-quebra] - (quebra == t2)) - '0';
		ways = (ways + k) % mod;
		if (n[quebra-1] > m[t2-quebra] and ok[quebra-1] and m[t2-quebra] != '0') ways = (ways + 1) % mod;
		ans = (ans + ways) % mod;
	}
	// da pra fazer o proprio n?
	if (t1 == t2) {
		bool okk = (n[t2-1] != '0');
		for (int i = 0; i < t2; ++i) {
			if (n[i] != m[t1-1-i]) {
				okk = (n[i] < m[t1-1-i]);
				break;
			}
		}
		if (okk) ans = (ans + 1) % mod;
	}
	cout << ans << " ";
	// tirar palindromos
	int pal = 0, okk = 1;
	for (int quebra = 1; quebra <= t2/2; ++quebra) {
		int ways = min(n[quebra-1], m[quebra-1]) - '0' - (quebra == 1); ways = ways * p10[(t2+1)/2-quebra] % mod;
		pal = (pal + ways) % mod;
		if (n[quebra-1] != m[quebra-1]) { okk = 0; break; }
	}
	if (okk and t2 % 2) {
		int ways = min(n[t2/2], m[t2/2]) - '0' - (t2 == 1);
		pal = (pal + ways) % mod;
	}
	ans = (ans + mod - pal) % mod;
	cout << ans << endl;
}
int32_t main() {_
	int t; cin >> t;
	while (t--) solve();
}
