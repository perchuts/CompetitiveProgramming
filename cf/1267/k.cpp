#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

void solve(){

	int n; cin >> n;
	vector<int> v;
	for(int i=2;n;i++){
		v.push_back(n%i);
		n /= i;
	}

	sort(v.begin(), v.end());

	vector<int> fat(20); fat[0] = 1;
	for(int i=1;i<20;i++) fat[i] = fat[i-1]*i;

	vector<int> freq(20);
	for(auto x : v) freq[x]++;

	int r1 = 1, r2=1;
	int s = v.size();
	for(int i=s-1;i>=0;i--){
		if(v[i]>0){
			r2 *= (i+1-v[i]);
			r1 *= (i+2-v[i]);
		}
	}
	
	for(int i=1;i<20;i++) r1 /= fat[freq[i]];
	for(int i=1;i<20;i++) r2 /= fat[freq[i]];
	cout << r1 - r2 - 1 << endl;

}

int32_t main() {
	fast_io;
	int t; cin >> t;
	while(t--) solve();
}
