#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
using namespace std;

using ll = long long;

struct aho{
	vector<vector<int>> to;
	vector<vector<int>> go;
	vector<int> c;
	vector<int> suf;
	vector<string> st;
	vector<int> vals;
	vector<vector<int>> g;
	bool emp;
	int sz;

	aho() : emp(true) {}

	void insert(string &s, int v){
		int x = 0;
		for (int i = 0; i < s.size(); ++i){
			int ch = s[i]-'a';
			if (!to[x][ch]){
				to[x][ch] = sz++;
				to.pb(vector<int>(26));
				c.pb(0);
			}
			x = to[x][ch];
		}
		c[x] = max(c[x],v);
	}

	void make_suf(){
		go = vector<vector<int>>(sz, vector<int>(26));
		suf = vector<int>(sz);
		g = vector<vector<int>>(sz);
			
		queue<int> q;
		q.push(0);

		while (!q.empty()){
			int x = q.front(); q.pop();
			for (int i = 0; i < 26; ++i){
				if (to[x][i]){
					go[x][i] = to[x][i];
					suf[to[x][i]] = (x == 0) ? 0 : go[suf[x]][i];
					g[suf[to[x][i]]].pb(to[x][i]);
					q.push(to[x][i]);
				} else{
					go[x][i] = (x == 0) ? 0 : go[suf[x]][i];
				}
			}
		}
	}

	void dfs(int x, int ma){
		ma = max(ma, c[x]);
		c[x] = max(c[x],ma);
		for (auto y : g[x]) dfs(y,ma);	
	}

	void build(vector<string> &vec, vector<int> &vs){
		st = vec;
		vals = vs;
		emp = false;
		
		to.pb(vector<int>(26));
		c.pb(0);
		sz = 1;
		for (int i = 0; i < vec.size(); ++i) insert(vec[i], vs[i]);

		make_suf();
		dfs(0,0);
	}

	int query(string &s){
		if (emp) return 0;

		int ma = 0, x = 0;
		for (int i = 0; i < s.size(); ++i){
			int ch = s[i]-'a';
			x = go[x][ch];
			ma = max(ma, c[x]);
		}

		return ma;
	}
};

const int D = 15;
aho ahos[D];

int32_t main() {_ 
	while (1){
		int n; cin >> n;
		if (!n) break;
		for (int i = 0; i < D; ++i) ahos[i] = aho();
		
		vector<string> vec;
		for (int i = 0; i < n; ++i){
			string x; cin >> x;
			vec.pb(x);
		}

		vector<int> les(n);
		iota(les.begin(), les.end(), 0);
		sort(les.begin(), les.end(), [&](int a, int b){
			return vec[a].size() < vec[b].size();
			});

		int ans = 0;

		for (auto id : les){
			string x = vec[id];

			int v = 1;
			for (int a = 0; a < D; ++a) v = max(v, ahos[a].query(x)+1);
			ans = max(ans, v);

			vector<string> vvec = {x};
			vector<int> vals = {v};
			for (int a = 0; a < D; ++a){
				if (!ahos[a].emp){
						for (auto v : ahos[a].st) vvec.pb(v);
						for (auto v : ahos[a].vals) vals.pb(v);
						ahos[a] = aho();
						continue;
					}	
					ahos[a].build(vvec, vals);
					break;
			}
		}

		cout << ans << endl;
	}
}
