#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;

	int n; cin >> n;
	vector<pair<int,int>> v(n);
	for(auto& [x, y] : v){
		cin >> x >> y;
	}

	set<int> ans;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			auto [xi, ci] = v[i];
			auto [xj, cj] = v[j];

			if(ci != cj){
				int d = abs(xi - xj);
				for(int i=1;i*i<=d;i++){
					if(d % i == 0) ans.insert(i);
					if(d % i == 0) ans.insert(d/i);
				}
			}
		}
	}

	for(int i=1;i<=50;i++){

		vector<int> cong(i);
		for(auto [x, c] : v){
			if(cong[(x%i+i)%i] == 0) cong[(x%i+i)%i] = c;
			else if(cong[(x%i+i)%i] != c) ans.insert(i);
		}
		int ok = 0;
		for(auto x : cong) if(x == 0) ok = 1;
		if(ok) continue;
		for(int j=1;j<i;j++){
			int ok = 1;
			for(int k=0;k<i;k++){
				if(cong[k] != cong[(k+j)%i]) ok = 0;
			}
			if(ok) ans.insert(i);
		}
	}

	int sm = 0;
	for(auto x : ans) sm += x;
	cout << ans.size() << " " << sm << endl;
}
