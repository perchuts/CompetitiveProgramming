#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_
	while (1){
		int n; cin >> n;
		if (n == -1) break;
		vector<int> vec(n+1);
		for (int i = 1; i <= n; ++i) cin >> vec[i];
	
		int op = 0;
		bool wks = true;
		for (int i = n; i >= 1; --i){
			int v = vec[i]+op;
			if (v%i){
				wks = false;
				break;
			}
			op += v/i;
		}

		if (wks) cout << "S" << endl;
		else cout << "N" << endl;
	}
	

}
