#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<int> divs;
	for(int i=1;i*i<=n;i++){
		if(n % i) continue;
		if(i*i < n) divs.push_back(n / i);
		divs.push_back(i);
	}
	int ans = 0;
	for(auto a : divs){
		int x = n / a - 1;
		vector<int> divx;
		for(int i=1;i*i<=x;i++){
			if(x % i) continue;
			if(i*i < x && x / i >= 2) divx.push_back(x / i);
			if(i >= 2) divx.push_back(i);
		}
		for(auto k : divx){
			int l = x / k - 1;
			if( l >= 2 ) ans++;
		}
	}
	cout << ans << endl;






}
