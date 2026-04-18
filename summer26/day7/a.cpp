#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
using namespace std;

using ll = long long;

int solve(int a, int b, int l, int r){
	if(r <= a || b <= l) return 0;
	if(a <= l && r <= b){
		if(r - l >= 4) return 0;
		int ans = 0;
		for(int i=l;i<r;i++) ans ^= i;
		return ans;
	}
	int m = (r+l)/2;
	return solve(a, b, l, m) ^ solve(a, b, m, r);

}

int32_t main() {_

	int n; cin >> n;
	int ans =0 ;
	for(int i=0;i<n;i++){
		int x, m; cin >> x >> m;
		int l = x, r = x+m;

		ans ^= solve(l, r, 0, (1LL<<62));
	}
	if(ans == 0) cout << "bolik" << endl;
	else cout << "tolik" << endl;
}
