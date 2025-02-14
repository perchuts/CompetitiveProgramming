#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;
	map<string, int> qt;
	vector<int> onde(300);
	for (int i = 0; i < n; ++i) {
		string s; cin >> s;
		string s2 = s;
		sort(begin(s2), end(s2));
		s2.erase(unique(begin(s2), end(s2)), end(s2));
		for (int j = 0; j < 26; ++j) onde['A'+j] = -1;
		int qnt = 0;
		for (auto& x : s) {
			if (onde[x] == -1) onde[x] = qnt++;
			x = char('A'+onde[x]);
		}
		qt[s]++;
	}
	int ans = 0;
	for (auto [x, y] : qt) ans += y * (y-1) / 2;
	cout << ans << endl;
}
