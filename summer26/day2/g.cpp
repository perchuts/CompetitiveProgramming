#include <bits/stdc++.h>
#define int ll
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define pb push_back

using namespace std;

using ll = long long;

template<class T = int>
struct bit2d{
	vector<T> X;
	vector<vector<T>> Y, t;

	int ub(vector<T> &v, T x){
		return upper_bound(v.begin(), v.end(), x) - v.begin();
	}

	bit2d(vector<pair<T,T>> &v){
		for (auto [x,y] : v) X.pb(x);
		sort(X.begin(), X.end());
		X.erase(unique(X.begin(), X.end()), X.end());

		t.resize(X.size()+1);
		Y.resize(X.size()+1);
		
		sort(v.begin(),v.end(), [](auto a, auto b){
			return a.second < b.second;
		});

		for (auto[x,y] : v) for (int i = ub(X,x); i < t.size(); i += i&-i)
			if (!Y[i].size() or Y[i].back() != y) Y[i].pb(y);

		for (int i = 0; i < t.size(); ++i) t[i].resize(Y[i].size()+1);
	}

	T query(T x, T y){
		T ans = 0;
		for (int i = ub(X,x); i; i -= i&-i)
			for (int j = ub(Y[i], y); j; j -= j&-j) ans += t[i][j];
		return ans;
	}	

	void update(T x, T y, T v){
		for (int i = ub(X,x); i < t.size(); i += i&-i)
			for (int j = ub(Y[i], y); j < t[i].size(); j += j&-j) t[i][j] += v;
	}
};

vector<vector<int>> solve(int n, int m, vector<array<int,3>> &gas){
	vector<vector<int>> diags(n+m);
	vector<pair<int,int>> vec;
	for (auto [x, y,w] : gas) vec.pb({x, y});

	bit2d bt(vec);
	bit2d freq(vec);

	int id = 0;
	for (auto [x, y ,w] : gas){
		bt.update(x,y,w+x+y);
		freq.update(x,y,1);
		if (w+x+y < diags.size()) diags[x+y+w].pb(id);
		id++;
	}
	
	vector<vector<int>> resp(n, vector<int>(m));
	for (int d = 0; d <= n+m-2; ++d){
		for (auto e : diags[d]){
			auto [x, y, w] = gas[e];
			bt.update(x,y,-w-x-y);
			freq.update(x,y,-1);
		}

		for (int x = 0; x <= d; ++x){
			int y = d-x;
			if (x >= n or y >= m) continue;
			
			int v1 = bt.query(x,y);
			int v2 = freq.query(x,y);

			resp[x][y] = v1 - v2*d;
		}
	}

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j) cout << resp[i][j] << " ";
		cout << endl;
	}

	return resp;
}

int32_t main() {_
	int n, m; cin >> n >> m;
	int g; cin >> g;
	vector<array<int,3>> vec;
	for (int i = 0; i < g; ++i){
		int x, y, cc; cin >> x >> y >> cc;
		vec.pb({x,m-1-y,cc});
	}

	solve(n,m,vec);

	// quero ir transformando, fazendo solves e voltando.

	vector grid(n, vector<int>(m));
}
