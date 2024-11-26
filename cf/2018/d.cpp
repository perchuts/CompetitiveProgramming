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
	vector<int> a(n), ord(n), par(n), lvl(n), lx(n), rx(n), good(n, -inf), mark(n);
	vector<int> vals;
	vector<vector<int>> freq, freq_mx(2);
	int mx = 0;
	for (auto& x : a) cin >> x, vals.pb(x), ckmax(mx, x);
	sort(all(vals)), vals.erase(unique(all(vals)), end(vals));
	freq.resize(sz(vals));
	for (int i = 0; i < n; ++i) {
		freq[lower_bound(all(vals), a[i]) - begin(vals)].pb(i);
		par[i] = lx[i] = rx[i] = i;
	}
	auto findp = [&] (auto&& self, int u) -> int {
		return par[u] = (u == par[u] ? u : self(self, par[u]));	
	};
	int ans = 2*mx + 1, cur_sum = 0;
	multiset<int> trocar;
	auto unite = [&] (int u, int v) {
		//cout << "unindo " << u << ' ' << v << endl;
		u = findp(findp, u), v = findp(findp, v);
		cur_sum -= (rx[u] - lx[u] + 2) / 2;
		cur_sum -= (rx[v] - lx[v] + 2) / 2;
		//cout << "reduzi pra " << cur_sum << endl;
		if (lvl[u] < lvl[v]) swap(u, v);
		ckmin(lx[u], lx[v]), ckmax(rx[u], rx[v]);
		int tam = rx[u] - lx[u] + 1;
		if (good[u] != -inf) trocar.extract(good[u]), good[u] = -inf;
		if (good[v] != -inf) trocar.extract(good[v]), good[u] = -inf;
		if (tam&1) {
			int my_p = (lx[u]&1);	
			for (int j = 0; j < 2; ++j) {
				int p = lower_bound(all(freq_mx[j]), lx[u]) - begin(freq_mx[j]);
				if (p != sz(freq_mx[j]) and freq_mx[j][p] <= rx[u]) {
					if (my_p == j) ckmax(good[u], (tam)/2 - (tam+1)/2 + 1); 
					else ckmax(good[u], tam/2-1 - (tam+1)/2 + 1);
				}
			}
		} else {
			int p = lower_bound(all(freq.back()), lx[u]) - begin(freq.back());
			if (p != sz(freq.back()) and freq.back()[p] <= rx[u]) good[u] = (tam-1)/2 - (tam+1)/2 + 1; 
		}
		cur_sum += (rx[u] - lx[u] + 2) / 2;
		if (good[u] != -inf) trocar.insert(good[u]);
		par[v] = u;
	};
	auto activate = [&] (int i) {
		// vou ativar esse numero!
		//cout << "Ativando " << i << endl;
		mark[i] = 1;
		cur_sum++;
		if (a[i] == mx) good[i] = 0, trocar.insert(good[i]); 
		if (i and mark[i-1]) unite(i-1, i);
		//cout << "cursum atual: " << cur_sum << endl;
		if (i != n-1 and mark[i+1]) unite(i, i+1);
		//cout << "cursum atual: " << cur_sum << endl;
	};
	// eh possivel q a resposta basicamente so pegue eu mesmo!
	for (int i = 0; i < n; ++i) {
		if (a[i] == mx) freq_mx[(i%2)].pb(i);
	}
	for (int i = sz(freq) - 1; i >= 0; --i) {
		int v1 = freq[i][0], v2;
		for (auto x : freq[i]) {
			v2 = x;
			activate(x);
			if (i == sz(freq)-1 and v1 == v2) continue;
			int big = *prev(end(trocar));
			if (i == sz(freq)-1 and abs(v1-v2) <= 1) {
				ckmax(ans, cur_sum + vals[i] + big);
			} else {
				ckmax(ans, cur_sum + mx + vals[i] + big);
			}
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int t; cin >> t;
  while(t--) solve();
}
