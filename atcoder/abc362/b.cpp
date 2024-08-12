#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

void solve() {
	vector<ii> p(3);
	for (auto& [x, y] : p) cin >> x >> y;
	auto length = [] (int a, int b, int c, int d) {
			return (a-c)*(a-c) + (b-d)*(b-d);
	};
	for (int i = 0; i < 3; ++i) {
		auto [x1, y1] = p[i];
		auto [x2, y2] = p[(i+1)%3];
		auto [x3, y3] = p[(i+2)%3];
		if (length(x1, y1, x2, y2) + length(x1, y1, x3, y3) == length(x2, y2, x3, y3)) {
			cout << "Yes" << endl;
			exit(0);
		}
	}
	cout << "No" << endl;
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}
