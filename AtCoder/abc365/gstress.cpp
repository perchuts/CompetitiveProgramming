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

vector<ii> q[maxn];

vector<int> solve(int n, int m, int Q, vector<ii> ops, vector<ii> qq){
	for (int i = 1; i <= n; ++i) q[i].clear();
	vector<int> status(n+1);
	vector<int> ans(Q);
	for (int i = 0; i < Q; ++i) {
		auto [u, v] = qq[i];
		q[u].pb({v, i});
		q[v].pb({u, i});
	}
	int magic = 3;
	vector<int> last(n+1);
	for (auto [x, y] : ops) {
		if (sz(q[y]) <= magic) {
			for (auto [z, id] : q[y]) {
				if (status[z] && status[y]) ans[id] += x - max(last[y], last[z]);
			}
		}
		last[y] = x;
		status[y] ^= 1;
	}
	reverse(all(ops));	
	for (int i = 1; i <= n; ++i) assert(status[i] == 0);
	for (auto [x, y] : ops) {
		if (sz(q[y]) <= magic) {
			for (auto [z, id] : q[y]) {
				if (sz(q[z]) > magic && status[z] && status[y] && last[z] < last[y]) ans[id] += last[z] - x;
			}
		}
		last[y] = x;
		status[y] ^= 1;
	}
	reverse(all(ops));
	vector<int> val(n+1);
	for (int i = 1; i <= n; ++i) {
		if (sz(q[i]) <= magic) continue;
		for (int j = 1; j <= n; ++j) status[j] = 0, val[j] = -1, last[j] = 0;
		for (auto [id, id_q] : q[i]) val[id] = id_q;	
		for (auto [x, y] : ops) {
			if (y == i) {
				last[y] = x;
				status[y] ^= 1;
			}
			if (val[y] == -1 || sz(q[y]) <= magic) continue;
			if (status[i] == 1 && status[y] == 1) ans[val[y]] += x - max(last[i], last[y]);
			last[y] = x;
			status[y] ^= 1;
		}
	}
	return ans;
}

mt19937 rng(time(0));

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

int32_t main(){
	int ttt = 0;
	while (++ttt) { 
		int n = rnd(2, 5);
		int m = rnd(1, 5);
		vector<ii> ops;
		vector<int> xww(n+1);
		for (int i = 0; i < m; ++i) {
			int z = rnd(1, n);
			xww[z] ^= 1;
			ops.pb({0, z});
		}
		for (int i = 1; i <= n; ++i) if (xww[i]) ops.pb({0, i}); 
		shuffle(all(ops), rng);
		m = sz(ops);
		int tempo = 0;
		for (int i = 0; i < m; ++i) tempo += rnd(1, 5), ops[i].first = tempo;
		vector<ii> qu;
		for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) qu.pb({i, j});
		shuffle(all(qu), rng);
		int tira = rnd(0, sz(qu) - 1);
		while (tira) tira--, qu.pop_back();
		auto my = solve(n, m, sz(qu), ops, qu);
		vector<int> ans(sz(qu));
		for (int id = 0; id < sz(qu); ++id) {
			auto [i, j] = qu[id];
			vector<int> alive(n+1);
			int now = 0;
			for (int w = 0; w < m; ++w) {
				while (now != ops[w].first) ans[id] += (alive[i] && alive[j]), now++;
				alive[ops[w].second] ^= 1;
			}
		}	

		if (my != ans) {
			cout << "Wrong answer on test " << ttt << endl;
			cout << n << ' ' << m << endl;
			for (auto [x, y] : ops) cout << x << ' ' << y << endl;
			cout << sz(qu) << endl;
			for (int i = 0; i < sz(qu); ++i) {
				if (my[i] != ans[i]) cout << "-> ";
				cout << qu[i].first << ' ' << qu[i].second << ' ' << my[i] << ' ' << ans[i] << endl;
			}
			return 0;
		}
		cout << "Accepted on test " << ttt << endl;
	}
}
