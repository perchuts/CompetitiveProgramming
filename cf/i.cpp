#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int n, m; cin >> n >> m;
	int eu = 0;
	vector<int> score(n);
	for (int i = 0; i < m; ++i) {
		int x, y; cin >> x >> y;
		vector<int> sexo(n);
		int opt = 0;
		for (auto& z : sexo) cin >> z, opt += (z == 1);
		int ganha = x / (opt + 1);
		eu += max(ganha, y);
		if (ganha >= y) opt++;
		for (int j = 0; j < n; ++j) {
			if (sexo[j] == 1) score[j] += x / opt;
			else score[j] += y;
		}
	}
	for (auto x : score) cout << x << ' ';
	cout << eu << endl;
}
