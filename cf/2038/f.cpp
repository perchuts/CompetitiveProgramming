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
	int n; cin >> n;
	vector<int> a(n), b(n);
	vector<vector<vector<int>>> coord(2, vector<vector<int>>(4*maxn));
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	vector<ii> pts;
	for (int i = 0; i < n; ++i) pts.pb({a[i], b[i]}), coord[0][a[i]].pb(b[i]), coord[1][b[i]].pb(a[i]);
	for (int i = 0; i < 4*maxn; ++i) sort(all(coord[0][i])), sort(all(coord[1][i]));
	vector<iii> coefs;
	// valor, quantos iguais, total de fodase
	for (int type = 0; type < 2; ++type) {
		sort(all(pts), [&] (ii x, ii y) { if (!type) return x < y; return make_pair(x.second, x.first) < make_pair(y.second, y.first); });
		for (int l = 0, r = 0; l < n; l = r) {
			while (r < n and pts[l] == pts[r]) r++;
			auto [x, y] = pts[l];
			int tot = n-r, k = max(x, y), k2 = min(x, y);
			if ((type == 0 and x < y) or (type == 1 and x >= y)) continue;
			if (x == y) {
				// sei que estou no type = 1
				// sei q sortei por x, entao vamos procurar agr por caras com ordenadas = X mas abcissas > X
				int lb = upper_bound(all(coord[1][x]), x) - begin(coord[1][x]);
				tot -= (sz(coord[1][x]) - lb);
			} else { 
				int lb = lower_bound(all(coord[type][k]), k2) - begin(coord[type][k]);
				// some todos com coordenada estritamente menor!
				cout << lb << ' ' << sz(coord[type][k]) << endl;
				tot += lb;
			}
			coefs.pb({k, r-l, tot});
		}
	}
	for (auto [x, y, z] : coefs) cout << x << ' ' << y << ' ' << z << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
