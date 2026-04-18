#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define endl '\n'

using namespace std;

using ll = long long;

const int lim = 2e5+10;
vector<int> divs[lim];

int32_t main() {_ 
	int n; cin >> n; 
	vector<int> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = n-2; i >= 0; --i) a[i] = min(a[i], a[i+1]);


	vector<int> dp(n); 

	//vectir<int> vec(lim);
	//int ans = 0;
	//for (int i = 1; i <= as.back(); ++i){
	//	int id = lower_bound(as.begin(), as.end(), i) - as.begin();
	//	if (id == 0){
	//		vec[i]++;
	//	}
	//	for (auto d : divs[i]){
	//		
	//	}
	//	ans += vec[i];
	//}
}
