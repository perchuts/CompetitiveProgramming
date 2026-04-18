#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
using namespace std;

using ll = long long;

void solve(){
	int n; cin >> n;

	int le = n;
	int c = 0;

	auto ans = [&](int x){
		cout << "! " << x << endl;
	};

	while (le > 1){
		if (le&1){
			cout << "? 1 2 1 1" << endl;
			int x; cin >> x;
			if (x == n) ans(1);
			else ans(c&1);
			return;
		}

		cout << "? 1 1 " << 1 << " " << le/2 + 1 << endl;
		int lcp; cin >> lcp;
		if (lcp < le/2){
			if (le > 2){
				cout << "? 1 2 1 1" << endl;
				int x; cin >> x;
				if (x == n) ans(1);
				else ans(c&1);
			} else ans(c&1);
			return;
		}

		le /= 2;
		c++;
	}

	ans(1);
}	

int32_t main() {_
	int t; cin >> t;
	while (t--) solve();
}
