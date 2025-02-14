#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	vector<int> v(3);
	for (auto& x : v) cin >> x;
	sort(begin(v), end(v));
	if (v[0] == v[2] or (v[0] == v[1] and v[2] == 2 * v[1])) cout << "YES" << endl;
	else cout << "NO" << endl;
}
