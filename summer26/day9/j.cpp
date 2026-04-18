#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define pb push_back
#define int ll
#define PI pair<int,int>
using namespace std;

using ll = long long;

const int maxn = 1e6+10;
int tr[maxn];
const int INF = 1e9;

int32_t main() {_ 
	int n; cin >> n;
	vector<int> as(n), bs(n);
	for (int i = 0; i < n; ++i) cin >> as[i];
	for (int i = 0; i < n; ++i) cin >> bs[i];
	reverse(as.begin(), as.end());
	reverse(bs.begin(), bs.end());
	as.pb(0);
	bs.pb(0);
	n++;

	vector<int> par(2*n, -1);
	vector<queue<PI>> q(2);
	vector<bool> vis(2*n, false);
	int b = 0;
	q[0].push({0,-1});

	set<int> unvis;
	for (int i = 1; i < n; ++i) unvis.insert(i);

	while (!q[0].empty() or !q[1].empty()){
		if (q[b].empty()){
			b = !b;
			continue;
		}

		auto [x,pr] = q[b].front(); q[b].pop();
		if (vis[x]) continue;
		vis[x] = true;
		par[x] = pr;

		if (x >= n){
			int p = x-n;
			int y = p-bs[p];
			if (vis[y]) continue;
			q[b].push({y,x});

		} else{
			while (!unvis.empty()){
				auto ptr = unvis.lower_bound(x);
				if (ptr == unvis.end() or *ptr > x+as[x]) break;
				int y = *ptr;
				unvis.erase(ptr);
				q[!b].push({y+n,x});
			}
		}
	}

	if (!vis[n-1]){
		cout << -1 << endl;
		return 0;
	}

	vector<int> resp;
	int x = n-1;
	while (1){
		if (x == -1) break;
		if (x >= n) resp.pb(x-n);
		x = par[x];
	}

	reverse(resp.begin(), resp.end());
	if (resp.back() == 0) resp.pop_back();

	cout << resp.size() << endl;
	for (auto v : resp) cout << n-v-1 << " ";
	cout << endl;
}
