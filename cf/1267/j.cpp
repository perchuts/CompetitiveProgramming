#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;

	int t; cin >> t;
	while(t--){
	int n; cin >> n;
	vector<int> v(n + 1);
	int mn = 1e9;
	for(int i=0;i<n;i++){
		int x; cin >> x; v[x]++;
	}

	for(auto x : v) if(x) mn = min(mn, x);

	vector<pair<int,int>> tem;
	for(int i=0;i<=n;i++){
		if(v[i]) tem.push_back({i, v[i]});
	}


	for(int s=mn+1;s>=1;s--){
		int ok = 1, ans = 0;
		for(auto [i, f] : tem){
			if(f/s < f%s) ok = 0;
			else ans += (f+s)/(s+1);
		}
		if(ok){
			//cout << s << " " ;
			cout << ans << endl;
			break;
		}
	}
	}

}
