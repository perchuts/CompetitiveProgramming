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

vector<int> g[maxn];
int n, k;

ii seg[4*maxn];
int lz[4*maxn], id[maxn];

void push(int i, int l, int r) {
	seg[i].first += lz[i];
	if (l != r) lz[2*i] += lz[i], lz[2*i+1] += lz[i];
	lz[i] = 0;
}

void upd(int i, int l, int r, int x, int y, int val) {
	push(i, l, r);
	if (r < x || y < l) return;
	if (x <= l && r <= y) {
		lz[i] += val;
		push(i, l, r);
		return;
	}
	int md = (l + r) / 2;
	upd(2*i, l, md, x, y, val), upd(2*i+1, md+1, r, x, y, val);
	seg[i] = max(seg[2*i], seg[2*i+1]);
}

void build(int i, int l, int r) {
	if (l == r) {
		seg[i].second = id[l];
		return;
	}
	int md = (l + r) / 2;
	build(2*i, l, md), build(2*i+1, md+1, r);
	seg[i] = max(seg[2*i], seg[2*i+1]);
}

int t = 0, tt[maxn], tout[maxn], height[maxn];

void dfs(int u, int h) {
	id[++t] = u, tt[u] = t, height[u] = h;
	for (auto v : g[u]) dfs(v, h+1);
	tout[u] = t;
	
}
int par[maxn], vis[maxn];
void solve(){
	cin >> n >> k;
	for (int i = 2; i <= n; ++i) {
		int x; cin >> x;
		par[i] = x;
		g[x].pb(i);
	}
	dfs(1, 1);
	build(1, 1, n);
	for (int i = 1; i <= n; ++i) {
		if (g[i].empty()) upd(1, 1, n, tt[i], tt[i], height[i]); 
	}
	int ans = 0;
	par[1] = 1;
	while (k--) {
		auto [x, u] = seg[1];
		ans += x;
		while (vis[u] == 0) {
			vis[u] = 1;
			upd(1, 1, n, tt[u], tout[u], -1);
			u = par[u]; 
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int tc = 1; //cin >> t;
  while(tc--) solve();
}
