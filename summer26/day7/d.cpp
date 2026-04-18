#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
using namespace std;

using ll = long long;

#define P 1000000007
const int inf= 1e18;
int32_t main() {_

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		int a, b, c, x1, x2;
		cin >> a >> b >> c >> x1 >> x2;
		int dp1ult = x1, dp1penult = 0;
		int dp2ult = x2, dp2penult = -inf;

		int ant = x2;
		int penant = x1;
		int soma = x1 + x2;
		for(int i=2;i<n;i++){
			int xi = (a*penant%P*penant + b*ant + c)%P;
			penant = ant;
			ant = xi;
			//cout << xi << endl;
			soma += xi;

			if(i != n-1){
				int novo = max(dp1ult, xi + dp1penult);
				dp1penult =  dp1ult;
				dp1ult = novo;
			}

			int novo = max(dp2ult, xi + dp2penult);
			dp2penult = dp2ult;
			dp2ult = novo;
		}

		int ans = max(dp1ult, dp2ult);
		if(2*ans >= soma){
			cout << ans << ".000" << endl;
		}
		else{
			cout << soma/2;
			if(soma%2 == 0) cout << ".000" << endl;
			else cout << ".500" << endl;
		}
	}
}
