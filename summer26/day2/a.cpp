#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	int t; cin >> t;
	while (t--) {
		auto win = [] (vector<pair<char, int>> v) {
			vector<int> impar, par;
			for (int i = 0; i < 3; ++i) {
				if (v[i].second % 2) impar.pb(v[i].second);
				else par.pb(v[i].second);
			}
			if (impar.empty()) return false;
			if (impar.size() + par.size() == 3) {
				if (impar.size() >= 2) return true;
				int a = impar[0], b = par[0], c = par[1];
				return (a/2 < (b+c)/2);
			}
			if (par.empty()) return (impar.size() > 1);
			return (impar[0]/2 < par[0]/2);
		};
		vector<pair<char, int>> v(3);
		for (auto& [x, y] : v) cin >> x >> y;
		sort(begin(v), end(v));
		if (v[0].first == v[2].first) cout << win(v) << endl;
		else {
			v[1].second--;
			if (v[0].first == v[1].first) v[0].second--;
			else v[2].second--;
			cout << (win(v)^1) << endl;
		}
	}
}
