#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using ll = long long;
using namespace std;

int32_t main() {_
	int q; cin >> q;
	while (q--){
		int l, r; cin >> l >> r;
		if (l <= 5 and r >= 5) cout << 1 << endl;
		else cout << 0 << endl;
	}
}
