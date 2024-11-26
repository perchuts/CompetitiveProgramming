#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

void solve(){
	int n, k; cin >> n >> k;
	vector<vector<int>> v(n*2, vector<int>(n*2));
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
		cin >> v[i][j];
		v[i+n][j] = v[i][j+n] = v[i+n][j+n] = v[i][j];
	}	
	vector<vector<int>> dist;
	for (int s = 0; s < n*2; ++s) {
		queue<int> q; q.push(s);
		vector<int> dd(2*n, inf);
		dd[s] = 0;
		while (!q.empty()) {
			auto u = q.front(); q.pop();
			for (int i = 0; i < 2*n; ++i) {
				if (v[u][i] and dd[i] > dd[u]+1) dd[i] = dd[u]+1, q.push(i);
			}
		}
		dist.pb(dd);
	}
	int q; cin >> q;
	while (q--) {
		int u, w; cin >> u >> w;
		if (u == w) {
			cout << 0 << endl;
			continue;
		}
		--u, --w;
		int uu = u % n, vv = w % n;
		if (uu == vv) {
			cout << (dist[uu][vv+n] == inf ? -1 : dist[uu][vv+n]) << endl; 
		} else {
			cout << (dist[uu][vv] == inf ? -1 : dist[uu][vv]) << endl;
		}

	}	
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
