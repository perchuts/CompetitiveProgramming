#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
//#define int ll
using namespace std;

using ll = long long;

int32_t main() {_ 
	int n; cin >> n;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	auto mover = [&] (int mask, int k) {

		int nmask = ((1 << k) - 1) & mask;

		int sexo = (1 << 30) - (1 << (k+1)); 
		nmask |= ((mask & sexo) >> k);
		return nmask;
	};
	map<int, vector<int>> primes;
	for (int i = 0; i < n; ++i) {
		int cur = a[i];
		for (ll j = 2; j * j <= a[i]; ++j) {
			int cnt = 0;
			while (cur % j == 0) {
				cnt++, cur /= j;
			}
			if (cnt) primes[j].push_back(cnt);
		}
		if (cur != 1) primes[cur].pb(1);
	}
	unordered_map<int, int8_t> mex;
	auto rec = [&] (auto&& self, int mask) -> int8_t {
		if (mask == 0) return 0;
		if (mex.count(mask)) return mex[mask];
		bitset<30> zz;
		for (int i = 1; (1LL << i) <= mask; ++i) {
			zz[self(self, mover(mask, i))] = 1;	
		}
		for (int8_t j = 0; ; ++j) {
			if (zz[j] == 0) {
				mex[mask] = j;
				break;
			}
		}
		return mex[mask];
	};
	int8_t ans = 0;
	for (auto [fodase, v] : primes) {
		int mask = 0;
		for (auto x : v) mask |= (1 << x);
		ans ^= rec(rec, mask);
	}
	cout << (ans ? "Mojtaba" : "Arpa") << endl;

}
