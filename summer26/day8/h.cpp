#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

int32_t main() {_
	int n; cin >> n;


	vector<int> c(n);
	for (int i = 0; i < n; ++i) cin >> c[i];


	vector<vector<int>> g(n);
	for (int i = 1; i < n; ++i){
		int p; cin >> p;
		p--; g[p].pb(i);
	}
	map<int,int> v1, v2;

	vector<int> dep(n);
	int b = 0;
	auto dfs = [&](int x, int d, auto &&self)->void{
		dep[x] = d;
		for (auto y : g[x]) self(y,d+1,self);
		if (g[x].empty()) b = d&1;
	};
	dfs(0,0,dfs);

	int xo = 0;
	int x1 = 0, x2 = 0;
	for (int i = 0; i < n; ++i) {
		if ((dep[i]&1) == b) v1[c[i]]++, xo ^= c[i], x1++;
		else v2[c[i]]++, x2++;
	}

	auto c2 = [&](int x){
		if (x <= 1) return 0ll;
		return x*(x-1)/2;
	};

	if (xo == 0){
		int ans = 0;
		ans += c2(x1);
		ans += c2(x2);
		for (auto [v,f] : v1) ans += f*v2[v];
		cout << ans << endl; 
	} else{
		int ans = 0;
		for (auto [v,f] : v1) {
			ans += f*v2[xo^v];
		}
		cout << ans << endl;
	}

}
