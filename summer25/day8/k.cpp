#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;



void bruta(vector<int> a){

	int n = a.size();
	map<vector<int>, int> dist;
	map<vector<int>, string> path;
	dist[a] = 1;
	queue<vector<int>> fila;
	fila.push(a);
	while(fila.size()){
		auto b = fila.front(); fila.pop();
		for(int i=1;i<=n-2;i++){
			vector<int> c = b;
			c[i] = -(b[i-1] + b[i] + b[i+1]);
			if(dist[c] > 0) continue;
			path[c] = path[b] + ((char) ('0' + i));
			dist[c] = dist[b] + 1;
			fila.push(c);
		}
	}
	vector<pair<int, vector<int>>> coisos;
	for(auto [v, d] : dist) coisos.push_back({d, v});
	sort(coisos.begin(), coisos.end());
	for(auto [d, v] : coisos){
		cout << "dist " <<setw(2) <<  d-1 << ": ";
		for(auto x : v) cout << setw(10) <<  x << " ";
		cout << " (path: " << path[v] << ")" << endl;
		cout << endl;
	}
}

vector<int> op(vector<int> a) {
	int n = a.size();
	vector<int> ret(n - 1);
	for (int i = 0; i < n - 1; i++) {
		int sgn = ((i&1) ? 1 : -1);
		ret[i] = sgn * (a[i] + a[i + 1]);
	}

	return ret;
}

int32_t main() {
	fast_io;
	int n; cin >> n;
	vector<int> a(n);
	for(auto& x : a) cin >> x;
	vector<int> b(n);
	for(auto& x : b) cin >> x;

	if (a[0] != b[0] || a.back() != b.back()) {
		cout << -1 << endl;
		return 0;
	}


	a = op(a);
	b = op(b);
	n--;

	map<int, deque<int>> mp;
	for (int i = 0; i < n; i++) {
		mp[a[i]].push_back(i);
	}
 
	vector tree(n + 1, 0);
	auto upd = [&] (int i, int x) {
		for (++i; i <= n; i += i&(-i)) {
			tree[i] += x;
		}
	};
	auto pref = [&] (int i) {
		int ans = 0;
		for (++i; i; i -= i&(-i)) {
			ans += tree[i];
		}
		return ans;
	};
	for (int i = 0; i < n; i++)
		upd(i, 1);
	
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int x = b[i];
		auto& st = mp[x];
		if (st.empty()) {
			cout << -1 << endl;
			return 0;
		}
		int j = st[0];
		st.pop_front();

		ans += pref(j - 1);
		upd(j, -1);
	}


	cout << ans << endl;
}
