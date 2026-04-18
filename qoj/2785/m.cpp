#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back

using namespace std;

using ll = long long;

void solve(){
	string s, t; cin >> s >> t;
	int n = s.size();
	vector<int> v(n);
	for(int i=0;i<n;i++) v[i] ^= (s[i] == '1');
	for(int i=0;i<n-1;i++) v[i] ^= (t[i] == '1'), v[i+1] ^= (t[i] == '1');
	v[n-1] ^= (t[n-1] == '1');

	int ans = 0, bl = 0;
	for(int i=0;i<n;i++){
		if(v[i] == 1) bl++;
		else{
			ans += (bl+1)/2;
			bl = 0;
		}
	}
	ans += (bl+1)/2;

	cout << ans << endl;
}

int32_t main() {_
	int t; cin >> t;
	while(t--) solve();
}
