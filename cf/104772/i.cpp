#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define pb push_back
#define int long long

using namespace std;

using ll = long long;

int n;

int query(int i, int j) {
	cout << i + 1 << " " << j + 1 << endl;
	int ans; cin >> ans;
	if (ans == n) exit(0);
	return ans;
}

vector<int> gray(int x) {
	vector<int> code;
	for (int i = 0; i < (1<<x); i++)
		code.push_back(i^(i>>1));
	code.push_back(code[0]);

	vector<int> v;
	for (int i = 1; i <= (1<<x); i++) {
		int change = code[i] ^ code[i - 1];
		v.push_back(__lg(change));
	}
	return v;
}

int32_t main() {
	cin >> n;

	int k; cin >> k;
	if (k == n) return 0;

	for (int i = 0; i < n; i++) {
		int nxt = query(i, i);
		if (nxt == k - 1) {
			k = query(i, i);
			continue;
		}
		auto changes = gray(n - i - 1);
		for (auto c : changes) {
			k = query(i, i + c + 1);
			int nxt = query(i, i);
			if (nxt != k) {
				if (nxt < k) k = query(i, i);
				break;
			}
		}
	}

	assert(false);
}
