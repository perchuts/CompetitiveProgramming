#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

int msb(int x){
	return  (63 - __builtin_clzll(x));
}

int32_t main() {_
	

	int n; cin >> n;
	int q; cin >> q;
	vector<int> v(n);
	for(auto& x : v) cin >> x;

	vector<vector<int>> pref(40, vector<int>(n+1));
	vector<int> sum(n+1);

	for(int i=1;i<=n;i++){
		sum[i] = sum[i-1] ^ v[i-1];
	}
	for(int k=0;k<40;k++){
		for(int i=1;i<=n;i++){
			pref[k][i] = pref[k][i-1];
			if(v[i-1] > 0 && msb(v[i-1]) == k) pref[k][i]++;
		}
	}

	while(q--){
		int l, r; cin >> l >> r;
		l--;

		int base = sum[r] ^ sum[l];
		for(int k=39;k>=0;k--){
			if(base>>k&1) continue;
			if(pref[k][r] == pref[k][l]) continue;
			base ^= (1LL << (k+1))-1;
		}

		cout << base << endl;
	}

}
