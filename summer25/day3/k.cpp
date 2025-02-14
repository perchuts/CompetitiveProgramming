#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<int> a(n), ans;
	int sum = 0;
	for (auto& x : a) {
		cin >> x, sum += x;
		if (sum < 0) continue;
		auto it = upper_bound(begin(ans), end(ans), sum);
		if (it == end(ans))  ans.push_back(sum);
		else  *it = sum;
	}
	if(sum < 0) {
		cout << -1 << endl;
		return 0;
	}
	cout << n - (int)(upper_bound(begin(ans), end(ans), sum) - begin(ans)) << endl;
}
