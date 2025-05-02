#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);
#define int long long

int sq(int x){
	int l = 0, r = 100000;
	while(r - l > 1){
		int m = (l+r)/2;
		if(m*m <= x) l = m;
		else r = m;
	}
	if(l*l == x) return l;
}

int32_t main(){_
	int n; cin >> n;
	vector<int> w(n);
	for(auto& x : w) cin >> x;
	int k; cin >> k;
	using T = array<int,2>;
	vector<T> b(k);

	for(int i=0;i<k;i++){
		int x, y, r; cin >> x >> y >> r;
		b[i][0] = -r;
		int z = x*x + y*y;

}
