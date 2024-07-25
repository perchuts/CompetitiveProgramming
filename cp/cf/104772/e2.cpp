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

ii solve(int n, vector<ii> pos) {
	for (int rodar = 0; rodar < 2; ++rodar) {
		for (int rodar2 = 0; rodar2 < 4; ++rodar2) {
			vector<ii> test;
			bool ok = 1;
			for (auto [x, y] : pos) ok &= (x == pos[0].first);
			auto printAns = [&] (int& a, int& b) {
				for (int i = rodar2; i < 4; ++i) {
					int novoa = -b, novob = a;
					a = novoa, b = novob;
				}
				if (rodar) {
					int novoa = (a + b) / 2, novob = (a - b) / 2;
					a = novoa, b = novob;
				}
			};
			if (!ok) {
				int xx, yy;
				for (auto [x, y] : pos) if (x != pos[0].first) xx = x, yy = y;
				if (rodar == 0 || (((pos[0].first)&1) == (yy&1))) test.push_back({pos[0].first, yy});
				test.push_back({pos[0].first, yy + (pos[0].first - xx)});
				test.push_back({pos[0].first, yy - (pos[0].first - xx)});
				for (auto [a, b] : test) {
					bool ataca = 1;
					for (auto [x, y] : pos) ataca &= attack(x, y, a, b);
					if (ataca) { printAns(a, b); return make_pair(a, b); }
				}
			} else { printAns(pos[0].first, pos[0].second); return pos[0]; }
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
	return make_pair(-1e18, 0);
}

mt19937 rng(time(0));

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

int32_t main() {_
	int tt = 1;
	while (true) {
		int n = 3;
		vector<ii> pos(n);
		int limit = 5;
		for (auto& [x, y] : pos) x = rnd(0, limit), y = rnd(0, limit);
		bool consegue = 0;
		int aa = 0, bb = 0;
		for (int i = -5*limit; i <= 5*limit; ++i) {
			for (int j = -5*limit; j <= 5*limit; ++j) {
				bool ok = 1;
				for (auto& [x, y] : pos) ok &= attack(x, y, i, j);
				consegue |= ok;
				if (ok) aa = i, bb = j;
			}
		}
		ii ret = solve(n, pos);
		if ((consegue && ret.first == -1e18) || (!consegue && ret.first != -1e18)) {
			cout << "Wrong answer on test " << tt << endl;
			cout << n << endl;
			for (auto [x, y] : pos) cout << x << ' ' << y << endl;
			cout << "Correct answer: ";
			if (consegue == 0) cout << "No solution" << endl;
			else cout << aa << ' ' << bb << endl;
			cout << "Your output: ";
			if (ret.first == -1e18) cout << "No solution" << endl;
			else cout << ret.first << ' ' << ret.second << endl;
			exit(0);
		}
		++tt;
	}
 }
