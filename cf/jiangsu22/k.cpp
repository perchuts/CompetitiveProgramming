#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
#define pb push_back

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;

int32_t main() {
	fast_io;
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		if (n == 0) {
			cout << "mvkaiogustavocruz" << endl; 
			continue;
		}
		int mx = 0, cur = n, bixo = 0;
		while (cur) cur /= 2, mx++;
		vector<string> answer;
		cur = (1 << mx) - 1;
		for (int i = 0; i < mx; ++i) {
			while (n >= cur) {
				if (bixo == 0) answer.pb("nunhehheh"), bixo = 1;
				else answer.pb("h");
				n -= cur;
			}
			answer.pb("a");
			cur /= 2;
		}
		for (auto x : answer) cout << x;
		cout << endl;
	}

	return 0;
}

