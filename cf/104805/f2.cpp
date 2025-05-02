#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(false);cin.tie(0);
#define endl '\n'
#define int long long

using ld = long double;

const ld INF = 1e18;

int32_t main(){_
	int n; cin >> n;
	vector<int> d(n);
	for (auto& x : d) cin >> x;
	int T; cin >> T;
	vector<array<ld, 2>> p(n);
	for (int i = 0; i < n; ++i) p[i][0] = p[i][1] = INF;
	auto get_prox = [&] (ld tempo_atual) {
		ld prox = INF;
		for (int i = 0; i < n; ++i) {
			if (p[i][0] == INF) continue;
			
			ld dif = min(tempo_atual, p[i][1]) - p[i][0];
			
			if (dif >= d[i]) continue;
		
			if (p[i][1] == INF) {
				ld sobra = d[i] - dif;	
				prox = min(prox, sobra);
			} else {
				dif += 2 * (tempo_atual - min(tempo_atual, p[i][1]));
				ld sobra = d[i] - dif;
				if (sobra > 0) prox = min(prox, sobra/2.0);
			}
		}
		return tempo_atual+prox;
	};
	vector<ld> queimou;
	vector<array<int, 2>> ans(n);
	for (int i = 0; i < n; ++i) ans[i][0] = ans[i][1] = -1;
	int intr = 0;
	auto backtrack = [&] (auto&& self, ld tt, int i = 0) -> void {
		intr++;
		if (intr % 1000000 == 0) {
			cout << intr/1e6 << endl;
			cout.flush();
		}
		if (tt > T) return;
		if (i == 0) queimou.push_back(tt);
		if (tt == T) {
			vector<ld> morte(n, INF);

			for (int j = 0; j < n; ++j) {
				if (p[j][0] == INF) continue;
				if (p[j][1] == INF) {
					morte[j] = d[j]+p[j][0];
					continue;
				}

				ld dif = p[j][1] - p[j][0];
				//if (dif >= d[i]) assert(false);
				ld sobe = d[j] - dif;
				morte[j] = p[j][1] + sobe/2.0;
			}
			vector<tuple<ld, int, int, int>> resp;
			for (int j = 0; j < n; ++j) {
				if (morte[j] <= T) {
					resp.push_back({morte[j], j+1, ans[j][0], ans[j][1]});
				}
			}
			sort(begin(resp), end(resp));
			cout << resp.size() << endl;
			for (auto [a, b, c, e] : resp) cout << fixed << setprecision(69) << a << ' ' << b << ' ' << c << ' ' << e << endl;
			exit(0);
		}
		if (i == n) self(self, get_prox(tt), 0);
		else {
			self(self, tt, i+1);
			int x = (int)queimou.size()-1;
			if (p[i][1] == INF and p[i][0] != INF) {
				p[i][1] = tt;
				ans[i][1] = x;
				self(self, tt, i+1);
				p[i][1] = INF;
				ans[i][1] = -1;
			}
			if (p[i][0] == INF) {
				p[i][0] = tt;
				ans[i][0] = x;
				self(self, tt, i+1);
				p[i][1] = tt;
				ans[i][1] = x;
				self(self, tt, i+1);
				p[i][0] = p[i][1] = INF;
				ans[i][0] = ans[i][1] = -1;
			}
		}
		if (i == 0) queimou.pop_back();
	};
	backtrack(backtrack, 0);
	cout << -1 << endl;
}

