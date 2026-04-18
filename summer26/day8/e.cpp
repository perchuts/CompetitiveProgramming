#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;

void solve(int n, int c){
	vector<vector<int>> vecs(n);
	vector<bool> rel(c);
	for (int i = 0; i < c; ++i){
		int k; cin >> k;
		while (k--){
			rel[i] = true;
			int a; cin >> a;
			vecs[a].pb(i);
		}
	}

	vector<vector<int>> eds(c);
	vector<vector<int>> g(c);
	for (int i = 0; i < n; ++i){
		if (vecs[i].size() == 1){
			int v = vecs[i][0];
			eds[v].pb(i);
			eds[v].pb(i);
		} else{
			int v = vecs[i][1], u = vecs[i][0];
			g[v].pb(u);
			g[u].pb(v);
			eds[v].pb(i);
			eds[u].pb(i);
		}
	}	

	vector<bool> vis(c);
	function<void(int)> dfs = [&](int x){
		vis[x] = true;
		for (auto y : g[x]) if (!vis[y]) dfs(y);
	};

	int v0 = -1;
	for (int i = 0; i< c; ++i) if (rel[i]) v0 = i;
	dfs(v0);
	
	bool conn = true;
	for (int i = 0; i < c; ++i) if (rel[i] and !vis[i]) conn = false;

	if (!conn){
		cout << -1 << endl;
		return;
	}

	vector<int> ods;
	for (int i = 0; i < c; ++i) if (rel[i]){
		int x = eds[i].size();
		if (x&1) ods.pb(i);
	}

	if (ods.size() == 2){

	vector<int> pos;
	for (int p = 0; p < 2; ++p){
		int a = ods[p], b = ods[!p];

		int cnt = 0;
		for (int i = 0; i < n; ++i) if (vecs[i].size() == 2){
			if ((vecs[i][0] == a and vecs[i][1] == b) or (vecs[i][0] == b and vecs[i][1] == a)) cnt++;
		}		

		if (cnt == 1){
		if (eds[a].size() == 1) pos.pb(eds[a][0]);
		else{
			for (auto e : eds[a]){
				if (vecs[e].size() == 2 and vecs[e][0] != vecs[e][1] and (vecs[e][0] == b or vecs[e][1] == b)) continue;
				pos.pb(e);
			}
		}
		} else{
			vector<int> sloops;
			vector<int> vv;
			map<int,int> freq;
			for (auto e : eds[a]) freq[e]++;

			for (auto [e,f] : freq) {
				if (f == 2) sloops.pb(e);
				else vv.pb(e);
			}

			if (vv.size() == 1){
				if (sloops.empty()){
				for (auto e : eds[a]) pos.pb(e);
					} else{
				for (auto e : sloops) pos.pb(e);
			}
			} else{
				for (auto e : eds[a]) pos.pb(e);
			}
		}
	}
	sort(pos.begin(), pos.end());
	cout << pos[0] << endl;

	} else if (ods.size() == 0){
	
	cout << 0 << endl;	

	} else{
	cout << -1 << endl;
	}	
}	

int32_t main() {_
	while (1){
		int n, c; cin >> n >> c;
		if (n == 0 and c == 0) break;
		solve(n,c);
	}
}
