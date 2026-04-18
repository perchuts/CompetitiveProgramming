#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define endl '\n'
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

using namespace std;

using ll = long long;

void solve(){
	int n; cin >> n;
	int k; cin >> k;
	vector<vector<int>> g(n);
	for (int i = 0; i < n-1; ++i){
		int a, b; cin >> a >> b;
		a--; b--;
		g[a].pb(b); g[b].pb(a);
	}
	vector<int> c(k);
	for (int i = 0; i < k; ++i) cin >> c[i];
	int a = *min_element(c.begin(), c.end());
	int b = *max_element(c.begin(), c.end());
	int va = 0, vb = 0;
	for (auto v : c){
		if (v == a) va++;
		else vb++;
	}

	vector<vector<int>> dp(n, vector<int>(2));

	auto solve = [&](int x, int p, auto &&self)->void{
		int ch = 0;
		for (auto nex : g[x]) if (nex != p){
			ch++;
			self(nex,x,self);
		}

		if (ch == 0){
			dp[x][0] = a;
			dp[x][1] = b;
			return;
		}

		int sum = 0;
		vector<int> vals;
		for (auto nex : g[x]) if (nex != p){ 
			sum += dp[nex][0];
			vals.pb(dp[nex][1]-dp[nex][0]);
		}
		sort(vals.begin(), vals.end());

		//sou 0
		int ca = min(ch,va-1), cb = ch-ca;
		int v = sum+a;
		for (int i = 0; i < cb; ++i) v += vals[i];
		dp[x][0] = v;
			
		//sou 1
		ca = min(ch,va), cb = ch-ca;
		v = sum+b;
		for (int i = 0; i < cb; ++i) v += vals[i];
		dp[x][1] = v;
	};

	solve(0,-1,solve);
	cout << min(dp[0][0],dp[0][1]) << endl;
}

int32_t main() {_
	int t; cin >> t;
	while (t--){
		solve();
	}
}
