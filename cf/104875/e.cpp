#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
using namespace std;

using ll = long long;

const int mod = 998244353;
const int inf = 2e9 + 100;

int32_t main() {_
	char lixo;
	int a, b; cin >> a >> lixo >> b;
	int g = gcd(a, b);
	a /= g, b /= g;
	for (int n = b; n <= 1000000; n += b) {
		if (n - 1 <= (a*n)/b && (a*n)/b <= (n-1)*(n)/2) {
			int score = n - 1;
			for (int j = 2; j < n; ++j) {
				if (score + n - j <= (a*n)/b) {
					score += n - j; continue;
				}
				int need = (a*n)/b - score;
				vector<pair<int, int>> edges;
				for (int w = 1; w < j; ++w) edges.emplace_back(w, w+1);
				for (int w = 0; w < n - j; ++w) {
					if (w < need) edges.emplace_back(j, j + w + 1);
					else edges.emplace_back(j-1, j + w + 1);
				}
				assert(edges.size() == n - 1);
				cout << n << ' ' << n - 1 << endl;
				for (auto [x, y] : edges) cout << x << ' ' << y << endl;
				return 0;
			}
			assert(score == (a*n)/b && (n-1)*n/2 == score);
			cout << n << ' ' << n - 1 << endl;
			for (int i = 2; i <= n; ++i) cout << i << ' ' << i-1 << endl;
			return 0;

		}
	}
	cout << "impossible" << endl;
}
