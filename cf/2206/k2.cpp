#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	int l = 0, r = n/4, ans = 0;
	vector<int> cnt(10), temp(10);
	for (auto x : s) cnt[x-'0']++;
	auto possible = [&] (int x) {
		for (int i = 0; i < 10; ++i) temp[i] = cnt[i];
		if (cnt[0] >= x) {
			temp[0] -= x;
			int need = x;
			for (int i = 0; i <= 5; ++i) {
				int quero = min(need, temp[i]);
				need -= quero, temp[i] -= need;
			}
			if (need) return false;
			return true;
		}
		x -= temp[0], temp[0] = 0;
		if (temp[1] < 2 * x) return false;
		temp[1] -= 2 * x;
		int need = x + cnt[0];
		for (int i = 0; i <= 5; ++i) {
			int quero = min(need, temp[i]);
			need -= quero, temp[i] -= need;
		}
		if (need) return false;
		return true;
	};
	while (l <= r) {
		int md = l + (r-l+1)/2;
		if (possible(md)) ans = md, l = md + 1;
		else r = md-1;
	}
	cout << ans << endl;
}

int32_t main() {_
	int t; cin >> t;
	while (t--) solve();
}
