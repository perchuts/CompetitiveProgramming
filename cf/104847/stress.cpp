
#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define int ll
#define endl '\n'
#define pb push_back
#define fast_io cin.tie(0)->sync_with_stdio(0);
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int maxn = 3e5 + 100;

vector<int> g[maxn];
set<pair<int, int>> ss[maxn];
pair<int, int> resp[maxn];
int tam[maxn], n, ans;

void dfs(int u) {
	tam[u] = 1;
	for (auto v : g[u]) {
		dfs(v);
		tam[u] += tam[v];
	}
	int big = -1;
	for (auto v : g[u]) {
		if (big == -1 || tam[v] > tam[big]) big = v;
	}
	if (big == -1) {
		ss[u].insert({u, u});
		// contendo segmento, nao contendo segmento
		resp[u] = {0, (n-u) * (n-u)};
		ans += (n-u) * (n-u) - resp[u].first - resp[u].second;
		return;
	}
	resp[u] = resp[big];
	swap(ss[u], ss[big]);
	auto [lb, rb] = *begin(ss[u]);
	assert(lb == big);
	resp[u].second += (big-u) * (big-u+1) / 2;
	auto add = [&] (int i) {
		auto nxt = ss[u].lower_bound(make_pair(i, i));
		if (nxt == end(ss[u])) {
			assert(nxt != begin(ss[u]));
			auto prv = prev(nxt);
			auto [lx, rx] = *prv;
			if (rx+1 == i) {
				resp[u].first += rx-lx+2;
				resp[u].second -= n-i+1;
				ss[u].erase(make_pair(lx, rx));
				ss[u].insert(make_pair(lx, rx+1));
			} else {
				resp[u].first++;
				resp[u].second -= (i-rx)*(n-i+1);
				ss[u].insert(make_pair(i, i));
			}
		} else {
			if (nxt == begin(ss[u])) {
				auto [lx, rx] = *nxt;
				if (lx-1 == i) {
					resp[u].first += rx-lx+2;
					resp[u].second -= i-u;
					ss[u].erase(make_pair(lx, rx));
					ss[u].insert(make_pair(lx-1, rx));
				} else {
					resp[u].first++;
					resp[u].second -= (i-u)*(lx-i);
					ss[u].insert(make_pair(i, i));
				}
			} else {
				auto prv = prev(nxt);
				auto [lx, rx] = *nxt;
				auto [lx2, rx2] = *prv;
				if (rx2+1 == i && i + 1 == lx) {
					resp[u].first += (i-lx2+1) * (rx-i+1);
					resp[u].second--;
					ss[u].erase(make_pair(lx2, rx2));
					ss[u].erase(make_pair(lx, rx));
					ss[u].insert(make_pair(lx2, rx));
				} else if (rx2+1 == i) {
					resp[u].first += (rx2-lx2+2);
					resp[u].second -= (lx-i);
					ss[u].erase(make_pair(lx2, rx2));
					ss[u].insert(make_pair(lx2, rx2+1));
				} else if (i + 1 == lx) {
					resp[u].first += (rx-lx+2);
					resp[u].second -= (i-rx2);
					ss[u].erase(make_pair(lx, rx));
					ss[u].insert(make_pair(lx-1, rx));
				} else {
					resp[u].first++;
					resp[u].second -= (i-rx2)*(lx-i);
					ss[u].insert(make_pair(i, i));
				}
			}
		}
	};
	for (auto v : g[u]) {
		if (v == big) continue;
		for (auto [l, r] : ss[v]) {
			for (int i = l; i <= r; ++i) add(i);	
		}
	}
	ans += (n-u) * (n-u) - resp[u].first - resp[u].second;
	add(u);
}

int solve(int n, vector<int> x) {
	for (int i = 1; i <= n; ++i) {
		g[i].clear();
		ss[i].clear();
		resp[i] = {0, 0};
	}
	 ans = 0;
	 for (int i = 2; i <= n; ++i) {
		g[x[i-2]].push_back(i);
	 }
	 for (int i = 1; i <= n; ++i) ans += i * (n-i+1);
	 cout << ans << endl;
	 dfs(1);
	 return ans;
}
mt19937 rng(time(0));
int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
vector<int> gg[maxn];
int lv[maxn], mark[maxn], par[maxn];
void pre(int u) {
	for (auto v : gg[u]) {
		lv[v] = lv[u] + 1;
		pre(v);
	}
}
void path(int a, int b) {
	while (a != b) {
		mark[a] = mark[b] = 1;
		if (lv[a] > lv[b]) a = par[a];
		else if (lv[b] > lv[a]) b = par[b];
		else a = par[a], b = par[b];
	}
	mark[a] = mark[b] = 1;
}
int f(int l, int r) {
	for (int i = l; i <= r; ++i) mark[i] = 1;
	for (int a = l; a <= r; ++a) {
		for (int b = a + 1; b <= r; ++b) {
			path(a, b);
		}
	}
	int res = 0;
	for (int i = 1; i <= n; ++i) res += (mark[i]);
	return res;
}
int32_t main() {
  fast_io;
  int n = 5, ttt = 1;
  while (true) {
	  vector<int> x;
	  for (int i = 1; i <= n; ++i) gg[i].clear();
	for (int i = 2; i <= n; ++i) {
		x.push_back(rnd(1, i-1));
		gg[x.back()].pb(i);
		par[i] = x.back();
	}
	int my = solve(n, x), res = 0;

	for (int l = 1; l <= n; ++l) {
		for (int r = l; r <= n; ++r) {
			res += f(l, r);	
		}
	}
	if (res != my) {
		cout << "Wrong answer on test " << ttt << endl;
		cout << n << endl;
		for (auto y : x) cout << y << ' ';
		cout << endl;
		cout << "Answer: " << res << endl;
		cout << "Your solution: " << my << endl;
		exit(0);
	}
	ttt++;
  }
}

