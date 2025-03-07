#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<int> a(n);
	for(auto& x : a) cin >> x;
	vector<array<int,2>> ans;
	for(int i=1;i<=n;i++){
		int p = 0;
		for(int j=0;j<n;j++){
			if(a[j] == i){
				p = j;
				break;
			}
		}
		for(int j=p+1;j<n;j++){
			ans.push_back({a[j], i});
		}
		for(int j=n-1;j>p;j--){
			ans.push_back({i, a[j]});
		}
		for(int j=p-1;j>=i-1;j--){
			ans.push_back({i, a[j]});
			swap(a[j], a[j+1]);
		}
	}
	reverse(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for(auto [x, y] : ans) cout << y << " " << x << endl;



}
