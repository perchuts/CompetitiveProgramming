#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int long long

typedef long long ll;

const int INF = 1e9;
const ll LINF = 1e18;

void solve(){
	
	int n; cin >> n;
	vector<int> a(n);
	for(auto& x : a) cin >> x;
	a.push_back(0);
	vector<int> b(n+1);
	b[0] = a[0];
	for(int i=1;i<=n;i++){
		b[i] = a[i] - a[i-1];
	}
	//for(auto x : b) cout << x << " ";
	//cout << endl;
	// particionar b na maior quantidade de conjuntos que somam 0

	vector<int> c;
	int q0 = 0;
	for(auto x : b) {
		if(x == 0) q0++;
		else c.push_back(x);
	}

	int m = n;
	n = c.size();

	vector<int> soma(1<<n);
	vector<int> bons;
	for(int i=0;i<n;i++){
		for(int j=0;j<(1<<i);j++){
			int di = 1<<i;
			soma[j+di] = soma[j] + c[i];
			if(soma[j+di] == 0) bons.push_back(j+di);
		}
	}

	vector<int> dp(1<<n);

//	for(auto x : bons){
//		for(int i=0;i<n;i++) cout << ((x>>i)&1) << " ";
//		cout << endl;
//	}
	for(int i=0;i<bons.size();i++){
		dp[bons[i]] = 1;

		for(int j=0;j<i;j++){
			if((bons[j] & bons[i]) != bons[j]) continue;

			dp[bons[i]] = max(dp[bons[i]], dp[bons[j]] + dp[bons[i] & ~bons[j]]);
		}
	}

	
	//cout << dp[(1<<n) - 1] << endl;

	cout << m+1-q0-dp[(1<<n)-1] << endl;

	return;

}

int32_t main(){
	_
	int t = 1;
	while(t--) solve();
}
