#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define pb push_back
#define PI pair<int,int>
#define endl '\n'
#define f first
#define s second

using namespace std;

using ll = long long;

int32_t main() {_
	int n, k, m; cin >> n >> k >> m;

	vector<vector<PI>> evs;
	for (int i = 0; i < k; ++i){
		int c; cin >> c;
		vector<PI> cc;
		while (c--){
			int a, b; cin >> a >> b;
			cc.pb({a,b});
		}
		evs.pb(cc);
	}

	int ans = 0;
	for (int i = 0; i < (1<<k); ++i){
		for (int a = 1; a <= n; ++a){
			for (int u = 0;
		}
	}



	sort(evs.begin(), evs.end());

	vector<int> dp(1<<k);

	int cur = 1, act = 0;
	auto add = [&](int l, int r){
		if (l > r) return;
		int le = r-l+1;
		if (__builtin_popcountll(act) >= 2) dp[act] += le;
	};

	auto upd = [&](int ev){
		act ^= (1<<ev);
	};

	for (int i = 0, j; i < evs.size(); i = j+1){
		add(cur, evs[i].f-1);

		j = i;
		while (j+1 < evs.size() and evs[i].f == evs[j+1].f) j++;

		for (int a = i; a <= j; ++a) upd(evs[a].s);
		cur = evs[i].f;
	}


	int tot = 0;
	for (auto v : dp) tot += v;
	
	vector<vector<int>> vecs(n, vector<int>(1<<n));

	for (int v = 0; v < k; ++v)
		for (int i = 0; i < (1<<k); ++i) if (i>>v&1) vecs[v][i] = dp[i];

	for (int v = 0; v < k; ++v)
	for (int u = 0; u < k; ++u)
		for (int i = 0; i < (1<<k); ++i)if(i>>u&1){
			int j = i^(1<<u);
			vecs[v][i] += vecs[v][j];
		}



	for (int u = 0; u < k; ++u)
		for (int i = 0; i < (1<<k); ++i)if(i>>u&1){
			int j = i^(1<<u);
			dp[i] += dp[j];
		}

	vector<int> resp(1<<k);
	for (int i = 0; i < (1<<k); ++i){
		if (__builtin_popcountll(i) < 2) continue;
		int rev = (1<<k)-1;
		rev ^= i;
		resp[i] = tot - dp[rev];
		for (int u = 0; u < k; ++u) if (i>>u&1){
			resp[i] -= vecs[u][rev|(1<<u)];
		}
	}

	int ans = 0;
	for (auto v : resp) if (v >= m) ans++;

	cout << ans << endl;
	
}
