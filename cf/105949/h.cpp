#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;


void solve(){
	int x, y, xx, yy;
	cin >> x >> y >> xx >> yy;
	x -= xx, y -= yy;
	x = abs(x), y = abs(y);
	if(max(x, y) >= 3){
		cout << (max(x, y) + 1) / 2 << endl;
		return;
	}
	if(max(x, y) == 0){
		cout << 0 << endl;
		return;
	}
	if(min(x, y) == 0){
		cout << 2 << endl;
		return;
	}
	cout << 1 << endl;
}


int32_t main() {
	fast_io;
	int t; cin >> t; while(t--) solve();
}
