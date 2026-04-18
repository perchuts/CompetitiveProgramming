#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

int32_t main() {_
	int n, k; cin >> n >> k;
	vector<int> win(n+1), allow(k);
	for (auto& x : allow) cin >> x;
	win[0] = 0;
	sort(begin(allow), end(allow));
	for (int i = 1; i <= n; ++i) {
		bool nice = 0;
		for (int j = 0; j < k and allow[j] <= i; ++j) {
			if (win[i-allow[j]] == 0) {
				nice = 1;
				break;
			}
		}
		win[i] = nice;
		cout << "LW"[win[i]];
	}
	cout << endl;
}
