#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define pb push_back
#define int long long

using namespace std;

using ll = long long;
using ii = pair<int, int>;

bool attack(int x, int y, int a, int b) {
	return (x == a || y == b || abs(x-a) == abs(y-b));
}

void solve() {
	int n; cin >> n;
	vector<ii> pos(n);
	for (auto& [x, y] : pos) cin >> x >> y;
	for (int rodar = 0; rodar < 2; ++rodar) {
		for (int rodar2 = 0; rodar2 < 4; ++rodar2) {
			vector<ii> test;
			bool ok = 1;
			for (auto [x, y] : pos) ok &= (x == pos[0].first);
			auto printAns = [&] (int a, int b) {
				for (int i = rodar2; i < 4; ++i) {
					int novoa = -b, novob = a;
					a = novoa, b = novob;
				}
				if (rodar) {
					int novoa = (a + b) / 2, novob = (a - b) / 2;
					a = novoa, b = novob;
				}
				cout << "YES" << endl;
				cout << a << ' ' << b << endl;
				return;
			};
			if (!ok) {
				int xx, yy;
				for (auto [x, y] : pos) if (x != pos[0].first) xx = x, yy = y;
				if (rodar == 0 || ((pos[0].first&1) == (yy&1))) test.push_back({pos[0].first, yy});
				test.push_back({pos[0].first, yy + (pos[0].first - xx)});
				test.push_back({pos[0].first, yy - (pos[0].first - xx)});
				for (auto [a, b] : test) {
					bool ataca = 1;
					for (auto [x, y] : pos) ataca &= attack(x, y, a, b);
					if (ataca) { printAns(a, b); return; }
				}
			} else { printAns(pos[0].first, pos[0].second); return; }
			for (auto& [x, y] : pos) {
				int novox = -y, novoy = x;
				x = novox, y = novoy;
			}
		}	
		for (auto& [x, y] : pos) {
			int novox = x + y, novoy = x - y;
			x = novox, y = novoy;
		}
	}
	cout << "NO" << endl;
}

mt19937 rng(time(0));


int32_t main() {_
	int t; cin >> t;
	while (t--) solve();
 }
