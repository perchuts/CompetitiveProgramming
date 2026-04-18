#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

#define endl '\n'
#define int ll
#define pb push_back
using namespace std;

using ll = long long;

const int maxn = 1e7+1;
int vec[maxn];

void solve(){
	int n, m, x; cin >> n >> m >> x;

	vector<int> divs;
	for (int i = 1; i*i <= x; ++i){
		int j = x/i;
		if (j*i == x){
			divs.pb(i);
			if (i != j) divs.pb(j);
		}
	}

	vector<int> as(n);
	vector<int> bs(m);
	for (int i = 0; i < n; ++i) cin >> as[i];
	for (int i = 0; i < m; ++i) cin >> bs[i];
	sort(bs.begin(), bs.end());
	bs.erase(unique(bs.begin(), bs.end()), bs.end());

	int ma = 0;
	for (auto v : as) ma = max(v, ma);
	for (int i = 0; i <= ma; ++i) vec[i] = 0;

	for (auto b : bs){
		for (int k = b; k <= ma; k += b) vec[k] = b;
		vec[0] = b;
	}
	
	sort(divs.begin(), divs.end());

	vector<vector<int>> vpos(n);
	for (int i = 0; i < n; ++i){
		int c = 0;
		for (auto d : divs){
			if (d > as[i]) break;
			int v = as[i]-d;
			if (vec[v] > d) vpos[i].pb(c);
			c++;
		}
	}

	int sz = divs.size();
	vector<vector<pair<int,int>>> cand(sz);
	map<int,int> rf;
	for (int i = 0; i < sz; ++i) rf[divs[i]] = i;

	for (int u = 0; u < sz; ++u)
		for (int v = 0; v < sz; ++v) if (x%(divs[u]*divs[v]) == 0){
			int z = divs[u]*divs[v];
			cand[u].pb({v,rf[z]});
		}

	vector<vector<bool>> dp(2, vector<bool>(sz));
	dp[0][0] = 1;
	int t = 0;
	vector<bool> ans(n);

	for (int a = 0; a < n; ++a){
		vector<bool> dp1(sz);
		bool f = false;
		t = !t;
		for (int z = 0; z < sz; ++z) dp[t][z] = false;

		for (auto d : vpos[a]){
			for (auto [n1,n2] : cand[d]) if (dp[!t][n1]) dp[t][n2] = true, f = true;
		}

		if (!f) break;

		if (dp[t].back()) ans[a] = 1;
	}


	for (auto v : ans){
		if (!v) cout << "No" << endl;
		else cout << "Yes" << endl;
	}
}

int32_t main() {_
	int t; cin >> t;
	while (t--) solve();
}
