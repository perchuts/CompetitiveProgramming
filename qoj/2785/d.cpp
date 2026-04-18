#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	int n; cin >> n;
	vector<int> l(n), r(n);
	vector<vector<int>> blocks(n);
	vector<tuple<int,int,int>> ev;
	for (int i = 0; i < n; ++i) {
		int k; cin >> k;
		blocks[i].resize(k);
		cin >> l[i] >> r[i];
		int tudo = 0;
		for (auto& x : blocks[i]) cin >> x, tudo += x;
		int a = 0;
		for (int j = 0; j <= k; ++j) {
			ev.pb({l[i] + a, i, r[i] - (tudo - a)});
			if (j != k) a += blocks[i][j];
		}
	}
	sort(begin(ev), end(ev));
	multiset<int> sexo;
	vector<int> cur(n, -1);
	int ans = 0;
	for (int lx = 0, rx = 0; lx != ev.size(); lx = rx) {
		while (rx != ev.size() and get<0>(ev[lx]) == get<0>(ev[rx])) rx++;
		int coord = get<0>(ev[lx]);
		for (int i = lx; i < rx; ++i) {
			auto [fds, id, upd] = ev[i];
			//cout << fds << " " << id << " " << upd << endl;
			if (cur[id] != -1) sexo.erase(sexo.find(cur[id]));
			sexo.insert(upd), cur[id] = upd;
		}
		if (sexo.size() == n) {
			ans = max(ans, (*begin(sexo)) - coord);
		}
	}
	cout << ans << endl;
}
