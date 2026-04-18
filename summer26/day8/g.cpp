#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll

using namespace std;

using ll = long long;
const int INF = 1e17;
struct dinitz {
	int lim;
	struct edge {
		int to, cap, rev, flow;
		edge(int to_, int cap_, int rev_) : to(to_), cap(cap_), rev(rev_), flow(0) {}
	};
	vector<vector<edge>> g;
	vector<int> lev, beg;
	ll F;
	dinitz(int n) : g(n), F(0) {}
	void add(int a, int b, int c){
		g[a].emplace_back(b, c, g[b].size());
		g[b].emplace_back(a, 0, g[a].size()-1);
	}

	bool bfs(int s, int t){
		lev = vector<int>(g.size(), -1); lev[s] = 0;
		beg = vector<int>(g.size(), 0);
		queue<int> q; q.push(s);
		while(q.size()){
			int u = q.front(); q.pop();
			for(auto& i : g[u]){
				if(lev[i.to] != -1 or (i.flow == i.cap)) continue;
				lev[i.to] = lev[u] + 1;
				q.push(i.to);
			}
		}
		return lev[t] != -1;
	}
	int dfs(int v, int s, int f = INF){
		if(!f or v == s) return f;
		for(int& i = beg[v]; i<g[v].size(); i++){
			auto& e = g[v][i];
			if(lev[e.to] != lev[v] + 1) continue;
			int foi = dfs(e.to, s, min(f, e.cap - e.flow));
			if(!foi) continue;
			e.flow += foi, g[e.to][e.rev].flow -= foi;
			return foi;
		}
		return 0;
	}
	ll max_flow(int s, int t){
		while(bfs(s, t)) while(int ff = dfs(s, t)) F += ff;
		return F;
	}
};

int32_t main() {_

	int tc = 0;
	while(1){
	int n, m, g;
	cin >> n >> m >> g;
	if(n+m+g == 0) break;
	vector<vector<int>> qt(41, vector<int>(41, m));
	vector<int> score(n);
	for(int i=0;i<g;i++){
		int x, y; char c;
		cin >> x >> c >> y;
		int r = 0;
		if(c == '=') r = 1;
		score[x] += r;
		score[y] += 2-r;
		qt[x][y]--, qt[y][x]--;
	}

	int mx = 0;
	dinitz ztinid(n*n + n + 2);
	int S = n*n;
	int src = S+n, snk = src+1;
	for(int i=1;i<n;i++) for(int j=i+1;j<n;j++){
		ztinid.add(src, i*n+j, 2*qt[i][j]);
		ztinid.add(i*n+j, S+i, 100000);
		ztinid.add(i*n+j, S+j, 100000);
		mx += 2*qt[i][j];
	}
	
	for(int j=1;j<n;j++){
		score[0] += 2*qt[0][j];
	}

	int ok = 1;
	for(int i=1;i<n;i++){
		int c = score[0] - score[i] - 1;
		if(c < 0){
			ok = 0;
			break;
		}
		ztinid.add(S+i, snk, c);
	}
	if(!ok){
		cout << "N" << endl;
		continue;
	}
	int f = ztinid.max_flow(src, snk);
	if(f == mx){
		cout << "Y" << endl;
	}
	else{
		cout << "N" << endl;
	}
}
}
