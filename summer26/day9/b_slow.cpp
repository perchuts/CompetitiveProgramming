#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
using namespace std;

using ll = long long;

int b1[1000], b2[1000], val[1000];

int32_t main() {_ 
	const int m1 = 998244353, m2 = 998244853; 
	int B = rand() % 256 + 350;
	b1[0] = b2[0] = 1;
	for (int i = 1; i < 1000; ++i) b1[i] = B * b1[i-1] % m1, b2[i] = B * b2[i-1] % m2;
	while (true) {
		int n; cin >> n;
		if (n == 0) break;
		vector<string> ss(n);
		for (auto& x : ss) cin >> x;
		vector<int> ids(n); iota(begin(ids), end(ids), 0);
		sort(begin(ids), end(ids), [&] (int x, int y) {
				return ss[x].size() < ss[y].size();
				});
		unordered_map<int, int> s1, s2;
		int ans = 0;
		for (int l = 0, r = 0; l != n; l = r) {
			vector<int> current; 
			vector<tuple<int, int, int>> upds;
			while (r != n and ss[ids[r]].size() == ss[ids[l]].size()) current.push_back(ids[r++]);
			for (auto i : current) { 
				int t1 = 0, t2 = 0;
				for (int j = 0; j < ss[i].size(); ++j) {
					val[j] = ss[i][j] - 'a' + 1;
					t1 = (t1 * B + val[j]) % m1;
					t2 = (t2 * B + val[j]) % m2;
				}
				int opt = 1;
				for (int j = 0; j < ss[i].size(); ++j) {
					int h1 = 0, h2 = 0;
					for (int k = j; k < ss[i].size(); ++k) {
						h1 = (h1 * B + val[k]) % m1;
						h2 = (h2 * B + val[k]) % m2;
						opt = max(opt, 1 + min(s1[h1], s2[h2]));
					}
				}
				upds.pb({t1, t2, opt});
			}
			for (int i = 0; i < upds.size(); ++i) {
				int h1 = get<0>(upds[i]);
				int h2 = get<1>(upds[i]);
				int opt = get<2>(upds[i]);
				s1[h1] = max(s1[h1], opt);
				s2[h2] = max(s2[h2], opt);
				ans = max(ans, opt);
			}
		}
		cout << ans << endl;
	}
}
