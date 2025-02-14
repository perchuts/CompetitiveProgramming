#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;
const int M = 1000000;
int32_t main() {
	fast_io;
	int n; cin >> n;
	using T = array<int,3>;
	vector<T> v(n);
	for(auto& [a, b, c] : v) cin >> a >> b >> c;
//	sort(v.begin(), v.end());
//	v.erase(unique(v.begin(), v.end()), v.end());

	
	vector<int> f1(2*M+1), f2(2*M+1);
	for(auto [a, b, c] : v){
		if(a == 1) f1[M+b-c]++;
		else f2[M+b-c]++;
	}

	int ans = 0;
	for(int i=0;i<2*M+1;i++){
		ans += min(f1[i], f2[i]);
	}
	cout << ans << endl;


}
