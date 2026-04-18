#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

void solve(){
	int n; cin >> n;
	vector<int> f(10);
	for(int i=0;i<n;i++){
		char x; cin >> x;
		f[x - '0']++;
	}
	int ans = 0;
	for(int q11 = 0; 2*q11 <= f[1]; q11++){
		int q0 = f[0], q15 = 0, q69 = 0;
		for(int i=1;i<=5;i++) q15 += f[i];
		for(int i=6;i<=9;i++) q69 += f[i];
		// fazer q11 caras 11:xx
		q15 -= 2*q11;
		if(q0+q15 < q11 || q0+q15+q69 < 2*q11) break;
		int falta = 2*q11;
		int tiro =  min(q69, falta);
		falta -= tiro;
		q69 -= tiro;
		tiro = min(q15, falta);
		falta -= tiro;
		q15 -= tiro;
		tiro = min(q0, falta);
		falta -= tiro;
		q0 -= tiro;
		assert(falta == 0);


		ans = max(ans, q11 + min({q0, (q0+q15)/2, (q0+q15+q69)/4}));

	
	}

	cout << ans << endl;
}


int32_t main() {_
	int t; cin >> t;
	while(t--) solve();
}
