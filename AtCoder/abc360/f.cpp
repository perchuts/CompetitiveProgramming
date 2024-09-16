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
const int maxn = 1e6+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

ii seg[4*maxn];

int lz[4*maxn];

void build(int i, int l, int r) {
	if (l == r) {
		seg[i] = {0, l};
		return;
	}
	int md = (l + r) / 2;
	build(2*i, l, md), build(2*i+1, md+1, r);
	seg[i] = min(seg[2*i], seg[2*i+1]);
}

void push(int i, int l, int r) {
	seg[i].first -= lz[i];
	if (l != r) lz[2*i] += lz[i], lz[2*i+1] += lz[i];
	lz[i] = 0;
}

void upd(int i, int l, int r, int x, int y, int k) {
	push(i, l, r);
	if (r < x || y < l) return;
	if (x <= l && r <= y) {
		lz[i] += k;
		push(i, l, r);
		return;
	}
	int md = (l + r) / 2;
	upd(2*i, l, md, x, y, k), upd(2*i+1, md+1, r, x, y, k);
	seg[i] = min(seg[2*i], seg[2*i+1]);
}

ii query(int i, int l, int r, int x, int y) {
	push(i, l, r);
	if (r < x || y < l) return {1e18, 0};
	if (x <= l && r <= y) return seg[i];
	int md = (l + r) / 2;
	return min(query(2*i, l, md, x, y), query(2*i+1, md+1, r, x, y));
}
void solve(){
	int n; cin >> n;
	vector<int> cc;
	vector<ii> points(n);
	for (auto& [x, y] : points) cin >> x >> y, cc.pb(x), cc.pb(y), cc.pb(x+1), cc.pb(y+1), cc.pb(y-1);
	cc.pb(0);
	sort(all(cc));
	cc.erase(unique(all(cc)), end(cc));
	auto coord = [&] (int x) { return lower_bound(all(cc), x) - begin(cc); };
	int M = sz(cc) + 10;
	build(1, 0, M);
	vector<iii> events;
	const int ADD = 0, REMOVE = 1, REMOVE2 = 2, QUERY = 3;
	for (auto [x, y] : points) {
		// precisa terminar exclusivamente entre x, y
		int dps = coord(x+1), antes = coord(y-1);
		upd(1, 0, M, dps, antes, 1);	
		events.pb({x, REMOVE, y});
		events.pb({x+1, ADD, y});
		events.pb({y, REMOVE2, 0});
		events.pb({x+1, QUERY, 0});
	}
	events.pb({coord(0), QUERY, 0});
	sort(all(events));
	iii ans = {0, 0, 1};
	for (auto [cx, type, cy] : events) {
		if (type == ADD) {
			int dps = coord(cy+1);
			upd(1, 0, M, dps, M, 1);
		} else if (type == REMOVE) {
			int lx = coord(cx+1), rx = coord(cy-1);
			upd(1, 0, M, lx, rx, -1);
		} else if (type == REMOVE2) {
			int dps = coord(cx+1);
			upd(1, 0, M, dps, M, -1);
		} else {
			int pos = coord(cx);
			auto [a, b] = query(1, 0, M, pos + 1, M);
			iii temp = {a, cx, cc[b]};
			ckmin(ans, temp);
		}
	}
	auto [lixo, l, r] = ans;
	cout << l << ' ' << r << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
