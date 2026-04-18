#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

int32_t main() {_

	int n; cin >> n;
	vector<int> flin(n+1), fcol(n+1);
	{
		int cnt = 1;
		for(int i=0;i<n-1;i++){
			char c; cin >> c;
			if(c == '0'){
				cnt++;
			}
			else{
				flin[cnt]++;
				cnt = 1;
			}
		}
		flin[cnt]++;
	}
	{
		int cnt = 1;
		for(int i=0;i<n-1;i++){
			char c; cin >> c;
			if(c == '0'){
				cnt++;
			}
			else{
				fcol[cnt]++;
				cnt = 1;
			}
		}
		fcol[cnt]++;
	}
	vector<int> r, s;
	for(int i=1;i<=n;i++){
		if(flin[i]&1) r.push_back(i);
		if(fcol[i]&1) s.push_back(i);
	}

	int ans = 0;
	for(auto x : r) for(auto y : s) ans ^= (x*y);
	cout << ans << endl;
	
}
