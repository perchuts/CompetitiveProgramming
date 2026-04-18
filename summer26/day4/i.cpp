#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define int ll
#define endl '\n'
#define pb push_back
#define PI pair<int,int>
#define f first
#define s second

using namespace std;

using ll = long long;
const int INF = 1e18;

int32_t main() {_
	int n, m; cin >> n >> m;
	int star, t; cin >> star >> t;
	star--; t--;
	vector<pair<PI,PI>> eds;
	
	vector<set<int>> terms(n);

	for (int i = 0; i < m; ++i){
		int a, ta, b, tb; cin >> a >> ta >> b >> tb;
		a--; ta--; b--; tb--;
		terms[a].insert(ta);
		terms[b].insert(tb);
		eds.pb({{a,ta},{b,tb}});
	}

	vector<vector<PI>> g(n);
	map<PI,int> mp;
	for (int i = 0; i < n; ++i) if (!terms[i].empty()){
		int ad = terms[i].size();
		int sz = g.size();
		g.resize(sz+ad);

		int id = sz;
		for (auto v : terms[i]){
			PI cur = {i,v};
			mp[cur] = id;
			g[id].pb({i,1});
			g[i].pb({id,1});
			id++;
		}
	}

	for (auto [e,f] : eds){
		int a = mp[e];
		int b = mp[f];
		g[a].pb({b,0});
		g[b].pb({a,0});
	}

	int sz = g.size();
	vector<int> dists(sz,INF);
	dists[star] = 0;
	priority_queue<pair<PI,PI>, vector<pair<PI,PI>>, greater<pair<PI,PI>>> pq;
	pq.push({{0,star},{-1,-1}});
	
	vector<vector<PI>> g2(sz);
	vector<bool> vis(sz);
	while (!pq.empty()){
		auto [val, pval] = pq.top(); pq.pop();
		auto [p, b] = pval;
		auto [d,v] = val;

		if (d == dists[v] and p != -1){
			g2[p].pb({v,!b});
		}
		if (vis[v]){
			continue;
		}
		vis[v] = true;

		for (auto [nex,w] : g[v]) if (dists[nex] >= dists[v]+w){
			dists[nex] = dists[v]+w;
			pq.push({{dists[nex],nex},{v,w}});
		}
	}

	int ans1 = (dists[t]-2)/2;
	dists = vector<int>(sz,INF);
	dists[star] = 0;
	priority_queue<PI,vector<PI>,greater<PI>> pq2;
	pq2.push({0,star});
	vis = vector<bool>(sz);

	while (!pq2.empty()){
		auto [d,v] = pq2.top(); pq2.pop();

		if (vis[v]){
			continue;
		}
		vis[v] = true;

		for (auto [nex,w] : g2[v]) if (dists[nex] > dists[v]+w){
			dists[nex] = dists[v]+w;
			pq2.push({dists[nex],nex});
		}
	}
	
	int ans2 = dists[t];
	cout << ans1 << " " << ans2 << endl;
}
