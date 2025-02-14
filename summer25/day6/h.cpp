#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	string s; cin >> s;
	int n = s.size();

	array<string, 3> keyboard = {
		"qwertyuiop[]",
		"asdfghjkl;'",
		"zxcvbnm,./"
	};

	vector<pair<int, int>> pos(n);
	for (int i = 0; i < n; i++) {
		char x = s[i];

		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < keyboard[j].size(); k++) {
				if (keyboard[j][k] == x) {
					pos[i] = {j, k};
				}
			}
		}
	}

	vector<string> ans;
	for (int d : {-1, 0, 1}) {
		bool ok = true;
		string t;
		for (int i = 0; i < n; i++) {
			auto [j, k] = pos[i];
			k += d;
			if (k < 0 || k >= keyboard[j].size()) {
				ok = false;
				break;
			}
			t += keyboard[j][k];
			if (!('a' <= t.back() && t.back() <= 'z')) {
				ok = false;
				break;
			}
		}
		if (ok) ans.push_back(t);
	}

	cout << ans.size() << endl;
	sort(ans.begin(), ans.end());
	for (auto x : ans) cout << x << endl;

}
