#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
using namespace std;

using ll = long long;

int32_t main() {_

	while(1){
		string ss;
		cin >> ss;
		if(ss[0] == '*') break;
		vector<int> v;
	
		for(int i=0;i<ss.size()-1;i++){
			int x = ((((int)ss[i+1]) - ss[i])%26+26)%26;
			if(x != 0) v.push_back(x);
		}
		{
			int x = ((((int)ss[0])- 'a')%26+26)%26;
			if(x != 0) v.push_back(x);
		}
		{
			int x = ((((int)'a') - ss[ss.size()-1])%26+26)%26;
			if(x != 0) v.push_back(x);
		}

		sort(v.begin(), v.end());
		int n = v.size();
		int C = 0;
		for(auto x : v) C += x;
		int ans = 10000000000000, s=0;
		for(int i=0;i<n-C/26;i++){
			s += v[i];
		}
		ans = min(ans, s);
		s = 0;
		for(int i=n-1;i>=n-C/26;i--) s += (26-v[i]);
		ans = min(ans, s);
		cout << ans << endl;
	}
}
