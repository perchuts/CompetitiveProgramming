#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define sz(x) (int) x.size()
#define endl '\n'
//#define gato

using namespace std;

using ll = long long;

const int mod = 1e9+7;

int solve(int n, string s) {
	if (n == 1) {
		cout << s << endl;
		exit(0);
	}
	vector<int> tot(n+1), y(n+1), pot(n+1, 1);
	for (int i = 1; i <= n; ++i) pot[i] = 3 * pot[i-1] % mod;
	int inv3 = (mod+1)/3;
	int ans = 0;
	int cf = 0;
	int atras = pot[n-2];
	for (int i = 1; i <= n; ++i) {
		int val = s[i-1]-'0';
		if (i == 1 or i == n) {
			tot[i] = (pot[n-2] * val + tot[i-1] * val + 10 * tot[i-1] + val * y[i-1]) % mod;
			if (n == i) tot[i] = (tot[i] + (cf+1) * val) % mod;
		} else {
			atras = atras * inv3 % mod;
			y[i] = (tot[i-1] * inv3 + y[i-1] * inv3) % mod;
			tot[i] = (pot[n-3] * val + (tot[i-1] * val) % mod * inv3 + (10 * tot[i-1]) % mod * inv3 % mod + y[i-1] * val * inv3) % mod;
			tot[i] = (tot[i] + (1+cf) * val % mod * atras) % mod;
			cf = (cf * 3 + 1) % mod;
		}
		ans = (ans + tot[i]) % mod;
	}
	return ans;
}
int brute(int n, string s) {
	int ans = 0;
	auto go = [&] (auto&& self, int i, int cur_num, vector<int> v) -> void {
		if (i == n) {
			// testar ambos!
			if (v.empty()) {
				ans += cur_num;
				return;
			}
			v.pb(-1), v.pb(cur_num);
			int cur = v[0];
			for (int i = 2; i < sz(v); i += 2) {
				if (v[i-1] == -2) cur *= v[i];
				else ans += cur, cur = v[i];
			}
			ans += cur;
			v.pop_back(), v.pop_back();
			v.pb(-2), v.pb(cur_num);
			cur = v[0];
			for (int i = 2; i < sz(v); i += 2) {
				if (v[i-1] == -2) cur *= v[i];
				else ans += cur, cur = v[i];
			}
			ans += cur;
			return;
		}
		int val = s[i] - '0';
		if (i == 0) {
			self(self, 1, val, v);
		} else {
			self(self, i+1, 10*cur_num+val, v);
			if (!v.empty()) {
				v.pb(-1);
				v.pb(cur_num);
				self(self, i+1, val, v);
				v.pop_back(), v.pop_back();
				v.pb(-2);
				v.pb(cur_num);
				self(self, i+1, val, v);
			} else {
				v.pb(cur_num);
				self(self, i+1, val, v);
			}
		}
	};
	ans %= mod;
	go(go, 0, 0, {});
	return ans;
}

mt19937 rng(time(0));
int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

int32_t main() {_
#ifndef gato
	int n; cin >> n;
	string s; cin >> s;
	cout << solve(n, s) << endl;
#else
	int t = 1;
	while (true) {
		int n = 6;
		string s(n, '1');
		for (auto& x : s) x = char(x + rnd(0, 8));
		int my = solve(n, s);
		int ans = brute(n, s);
		if (my != ans) {
			cout << "Wrong answer on test " << t << endl;
			cout << n << endl << s << endl;
			cout << my << " " << ans << endl;
			exit(0);
		}
		cout << "Accepted on test " << t++ << endl;
	}
#endif

}
