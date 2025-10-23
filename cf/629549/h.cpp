#include <bits/stdc++.h>
using namespace std;

#define int ll
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

int32_t main() {
	fast_io;
	int n, l, t; cin >> n >> l >> t;
	t = min(t, l*n+1069);
	vector<array<int,3>> edg(l);
	vector<vector<array<int,2>>> g(n);
	for(int i=0;i<l;i++){
		int a, b; cin >> a >> b;
		a--, b--;
		g[b].push_back({a,i});
	}

	vector<int> q(n);
	for(auto& x : q) cin >> x;

	vector<int> ans(n);

	for(int k=0;k<8;k++){
		vector<int> st(n);
		priority_queue<array<int,2>> pq;

		for(int i=0;i<n;i++){
			if(q[i]>>k&1){
				pq.push({0, i});
			}
		}

		while(pq.size()){
			auto [x, v] = pq.top(); pq.pop();
			x = -x;
			if(st[v] == 1) continue;
			st[v] = 1;
			for(auto [w, id] : g[v]){
				int y = (x/l - 1)*l + id;
				while(y < x) y += l;
				if(y < t) pq.push({-y, w});
			}
		}

		for(int i=0;i<n;i++){
			if(st[i]){
				ans[i] |= (1 << k);
			}
		}
	}
	for(auto x : ans) cout << x << " ";
	cout << endl;
}
