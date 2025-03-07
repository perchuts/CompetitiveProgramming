#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int a, n, m, e, t, b, k;
	cin >> a >> n >> m >> e >> t >> b;
	vector<int> bad(b);
	for (auto& x : bad) cin >> x;	
	cin >> k;
	vector<ii> edges(t);
	for (auto& [x, y] : edges) cin >> x >> y, --x, --y;
	vector<int> par(n), lvl(n), bad(n);
}
