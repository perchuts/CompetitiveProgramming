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

int lazy[4*maxn];
ii seg[4*maxn];

void push(int i, int l, int r) {
	seg[i].first += lazy[i];
	if (l != r) lazy[2*i] += lazy[i], lazy[2*i+1] += lazy[i];
	lazy[i] = 0;
}

void build(int i, int l, int r) {
	if (l == r) {
		seg[i] = {1e18, l};
		return;
	}
	int md = (l + r) / 2;
	build(2*i, l, md), build(2*i+1, md+1, r);
	seg[i] = min(seg[2*i], seg[2*i+1]);
}	

void upd(int i, int l, int r, int x, int y, int k) {
	push(i, l, r);
	if (r < x || y < l) return;
	if (x <= l && r <= y) {
		lazy[i] += k;
		push(i, l, r);
		return;
	}
	int md = (l + r) / 2;
	upd(2*i, l, md, x, y, k), upd(2*i+1, md+1, r, x, y, k);
	seg[i] = min(seg[2*i], seg[2*i+1]);
}

void upd2(int i, int l, int r, int x, int k) {
	push(i, l, r);
	if (l == r) {
		seg[i].first = k;
		return;
	}
	int md = (l + r) / 2;
	if (x <= md) upd2(2*i, l, md, x, k);
	else upd2(2*i+1, md+1, r, x, k);
	seg[i] = min(seg[2*i], seg[2*i+1]);
}

ii query(int i, int l, int r, int x, int y) {
	push(i, l, r);
	if (r < x || y < l) return {1e18, -1};
	if (x <= l && r <= y) return seg[i];
	int md = (l + r) / 2;
	return min(query(2*i, l, md, x, y), query(2*i+1, md+1, r, x, y));
}

void solve(){
	int n; cin >> n;
	vector<ii> points(n);
	vector<int> coords;
	for (auto& [x, y] : points) cin >> x >> y, coords.pb(x), coords.pb(y), coords.pb(x+1), coords.pb(y+1);
	sort(all(coords));
	coords.pb(0);
	coords.erase(unique(all(coords)), end(coords));
	vector<iii> events;
	const int QUERY = 1;
	const int UPD = 0;
	const int TERMINO = -1;
	//events.pb({0, QUERY, 0});
	vector<ii> start_after(n);
	vector<iii> events2;
	int aux = 0;
	for (auto [x, y] : points) {
		events.pb({x+1, QUERY, 0});
		events.pb({x+1, UPD, y});
		events.pb({y, TERMINO, 0});
		events2.pb({x,inf ,1});
		events2.pb({y+1,inf, -1});
		events2.pb({x+1, aux, 0});
		events2.pb({y+1, aux++, 1});
	}
	sort(all(events)), sort(all(events2));
	int have_started = 0;
	for (auto [x, y, z] : events2) {
		if (y == inf) {
			if (z == 1) have_started++;
		} else {
			if (z == 0) start_after[y].first = n - have_started;
			else start_after[y].second = n - have_started;
		}
	}
	int M = sz(coords) + 100;
	map<int, int> jah_foi;
	build(1, 0, M);
	for (int i = 0; i < n; ++i) {
		auto [x, y] = points[i];
		x = lower_bound(all(coords), x + 1) - begin(coords);
		y = lower_bound(all(coords), y + 1) - begin(coords);
		if (!jah_foi[x]) upd2(1, 0, M, x, start_after[i].first), jah_foi[x] = 1;
		if (!jah_foi[y]) upd2(1, 0, M, y, start_after[i].second), jah_foi[y] = 1;
	}
	for (int i = 0; i < n; ++i) {
		auto [x, y] = points[i];
		y = lower_bound(all(coords), y) - begin(coords);
		upd(1, 0, M, y, M, 1);
		cout << y << ' ' << 1 << endl;
	}
	int terminou = 0;
	iii answer = {n, 0, 1};
	for (auto [x, type, auxiliar] : events) {
		if (type == TERMINO) terminou++;
		else if (type == UPD) {
			cout << "tirando o intervalo do ar: " << x-1 << ' ' << auxiliar << endl;
			int y = lower_bound(all(coords), auxiliar) - begin(coords);
			upd(1, 0, M, y+1, M, -1);
		} else {
			int xx = lower_bound(all(coords), x) - begin(coords);
			ii melhor = query(1, 0, M, xx+1, M);
			int a = melhor.first + terminou, b = x, c = coords[melhor.second];
			iii temp = {a, b, c};
			ckmin(answer, temp);
			cout << terminou << endl;
			cout << x << ", " << melhor.second << ": " << melhor.first << endl;
		}
	}
	auto [a, b, c] = answer;
	cout << b << ' ' << c << endl;
}	

int32_t main(){_

  int t = 1; //cin >> t;
  while(t--) solve();
}
