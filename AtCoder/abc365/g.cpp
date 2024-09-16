#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int long long
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

void solve() {
	int n, m; cin >> n >> m;
	vector<ii> ops(m);
	for (auto& [x, y] : ops) cin >> x >> y;
	int q; cin >> q;
	vector<vector<ii>> qq(n+1);
	vector<vector<iii>> intr(n+1);
	vector<ii> queries;
	for (int i = 0, x, y; i < q; ++i) {
		cin >> x >> y, qq[x].emplace_back(y, i), qq[y].emplace_back(x, i);
		queries.pb({x, y});
	}
	vector<int> last(n+1), state(n+1), tot(n+1), ans(q);
	vector<array<int, 5>> events;
	const int magic = 330;
	for (auto [x, y] : ops) {
		if (sz(qq[y]) <= magic) {
			for (auto [z, id_q] : qq[y]) {
				if (sz(qq[z]) <= magic && state[y] && state[z]) ans[id_q] += x - max(last[y], last[z]);
			}
		}
		if (state[y]) intr[y].emplace_back(last[y], x-1, tot[y]), events.pb({y, last[y], x-1, tot[y], 1}), tot[y] += x - last[y];
		else events.pb({y, 0, 0, 0, 0});
		state[y] ^= 1, last[y] = x;
	}
	for (int i = 1; i <= n; ++i) {
		if (sz(qq[i]) <= magic) continue;	
		vector<int> id_q(n+1, -1), onde(n+1);
		for (auto [v, val] : qq[i]) {
			int t1 = sz(qq[i]), t2 = sz(qq[v]);
			if (t1 > t2 || (t1 == t2 && i < v)) id_q[v] = val;
			else id_q[v] = -1;
		}
		int id_i = -1;	
		for (auto e : events) {
			int label = e[0], r = e[2], l = e[1], type = e[4];
			if (label == i) {
				if (type == 0) id_i++;
				continue;
			}
			if (id_q[label] == -1) continue;
			if (type == 0) {
				onde[label] = id_i;
				continue;
			}
			int i2 = id_i, i1 = onde[label]; 
			if (i1 == -1 || get<1>(intr[i][i1]) < l) i1++;
			if (i1 > i2) continue;
			auto [l1, r1, pr1] = intr[i][i1];
			assert(r1 >= l);
			auto [l2, r2, pr2] = intr[i][i2];
			if (i1 == i2) {
				ans[id_q[label]] += min(r1, r) - max(l1, l) + 1;
				continue;
			}
			ans[id_q[label]] += pr2 - pr1 - (r1 - l1 + 1);
			ans[id_q[label]] += min(r1, r) - max(l1, l) + 1;
			ans[id_q[label]] += min(r2, r) - max(l2, l) + 1;
		}
	}
	map<ii, int> true_resp;
	for (int i = 0; i < q; ++i) {
		if (ans[i] != 0) true_resp[{min(queries[i].first, queries[i].second), max(queries[i].first, queries[i].second)}] = ans[i];
	}
	for (int i = 0; i < q; ++i) {
		cout << true_resp[queries[i]] << endl;
	}
}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}


