#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	string s; cin >> s;
	int N = stoi(s);
	int real = 0;
	const int mod = 1e9+7;
	for (int i = 1; i <= N; ++i) {
		string z = to_string(i);
		sort(begin(z), end(z));
		reverse(begin(z), end(z));
		while (z.back() == '0') z.pop_back();
		reverse(begin(z), end(z));
		real += stoi(z);
		real %= mod;
	}
	cout << real << endl;
	int n = s.size();
	vector<int> pot(n+1, 1), id_pot(n);
	for (int i = 1; i <= n; ++i) pot[i] = 10 * pot[i-1] % mod;
	for (int i = 0; i < n; ++i) id_pot[i] = pot[n-1-i];
	auto add = [&] (int& x, int y) {
		x += y;
		if (x >= mod) x -= mod;
	};
	int tira = 0;
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < k; ++i) {
			for (int j = i + 1; j < k; ++j) {
				if (s[i] > s[j]) {
					int ways = id_pot[j] * 9 * (s[i] - s[j]) % mod * pot[n-k-1] % mod * (s[k] - '0') % mod; 
					add(tira, ways);
				}
			}
		}
		cout << tira << " ";
		for (int d = 0; d < s[k] - '0'; ++d) {
			for (int z = 0; z < n; ++z) {
				if (z < k and s[z]-'0' > d) {
					int ways = id_pot[k] * 9 * (s[z] - '0' - d) % mod * pot[n-k-1] % mod;
					add(tira, ways);
				}
				if (k < z) {
					int ways = id_pot[z] * 9 * (d*d - d*(d-1)/2) % mod * pot[n-k-2] % mod;
					add(tira, ways);
				}
			}
		}
		//cout << tira << " ";
		// agora um cara daqui vs um cara dali
		for (int i = 0; i < k; ++i) {
			int d = s[i] - '0';
			for (int j = k+1; j < n; ++j) {
				int ways = id_pot[j] * 9 * (d*d - d*(d-1)/2) % mod * pot[n-k-2] % mod * (s[k]-'0') % mod;
				add(tira, ways);
			}
		}
		//cout << tira << " ";
		// agora dois caras daqui
		for (int i = k + 1; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				int ways = id_pot[j] * 9 * 165 % mod * (s[k] - '0') % mod * pot[n-k-3] % mod;
				add(tira, ways);
			}
		}
		//cout << tira << endl;
	}
	cout << endl;
	int x_mod = 0;
	for (int i = 0; i < n; ++i) {
		x_mod = (x_mod + id_pot[i] * (s[i] - '0')) % mod;
		for (int j = i + 1; j < n; ++j) {
			if (s[i] > s[j]) {
				int ways = id_pot[j] * 9 * (s[i] - s[j]) % mod;
				add(tira, ways);
			}
		}
	}
	int sx = (x_mod+1) * (x_mod) % mod * ((mod+1)/2) % mod;
	cout << (sx-tira+mod)%mod << endl;
}
