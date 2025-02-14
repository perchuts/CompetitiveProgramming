#include <bits/stdc++.h>
using namespace std;

#define int ll
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
typedef long long ll;

template<int p> struct mod_int {
	ll expo(ll b, ll e) {
		ll ret = 1;
		while (e) {
			if (e % 2) ret = ret * b % p;
			e /= 2, b = b * b % p;
		}
		return ret;
	}
	ll inv(ll b) { return expo(b, p-2); }
	using m = mod_int;
	int v;
	mod_int() : v(0) {}
	mod_int(ll v_) {
		if (v_ >= p or v_ <= -p) v_ %= p;
		if (v_ < 0) v_ += p;
		v = v_;
	}
	m& operator +=(const m& a) {
		v += a.v;
		if (v >= p) v -= p;
		return *this;
	}
	m& operator -=(const m& a) {
		v -= a.v;
		if (v < 0) v += p;
		return *this;
	}
	m& operator *=(const m& a) {
		v = v * ll(a.v) % p;
		return *this;
	}
	m& operator /=(const m& a) {
		v = v * inv(a.v) % p;
		return *this;
	}
	m operator -() { return m(-v); }
	m& operator ^=(ll e) {
		if (e < 0) {
			v = inv(v);
			e = -e;
		}
		v = expo(v, e);
		return *this;
	}
	bool operator ==(const m& a) { return v == a.v; }
	bool operator !=(const m& a) { return v != a.v; }

	friend m operator +(m a, m b) { return a += b; }
	friend m operator -(m a, m b) { return a -= b; }
	friend m operator *(m a, m b) { return a *= b; }
	friend m operator /(m a, m b) { return a /= b; }
	friend m operator ^(m a, ll e) { return a ^= e; }
};
const int MOD = 998244353;
using mint = mod_int<MOD>;

void ntt(vector<mint>& a, bool rev) {
	int n = a.size(); auto b = a;
	assert(!(n&(n-1)));
	mint g = 1;
	while ((g^(MOD/2)) == 1) g += 1;
	if (rev) g = 1 / g;

	for (int step = n/2; step; step /= 2) {
		mint w = g^(MOD / (n/step)), wn = 1;
		for (int i = 0; i < n/2; i+= step) {
			for (int j = 0; j < step; j++) {
				auto u = a[2*i + j], v = wn*a[2*i + j + step];
				b[i+j] = u + v; b[i+n/2+j] = u - v;
			}
			wn = wn * w;
		}
		swap(a, b);
	}
	if (rev) {
		auto n1 = mint(1) / n;
		for (auto &x : a) x *= n1;
	}
}

using poly = vector<mint>;
poly conv(const poly& a, const poly& b) {
	poly l(a.begin(), a.end()), r(b.begin(), b.end());
	int N = l.size()+r.size()-1, n = 1;
	while (n <= N) n <<= 1;
	l.resize(n);
	r.resize(n);
	ntt(l, false);
	ntt(r, false);
	for (int i = 0; i < n; i++) l[i] *= r[i];
	ntt(l, true);
	l.resize(N);
	return l;
}

int32_t main() {
	fast_io;

	int n; cin >> n;
	int m; cin >> m;
	vector<vector<int>> g(n);
	vector<pair<int, int>> edges(m);
	for (int i = 0; i < m; i++) {
		cin >> edges[i].first;
	}
	for (int i = 0; i < m; i++) {
		cin >> edges[i].second;
	}
	for (auto &[a, b] : edges) {
		g[a].push_back(b);
		g[b].push_back(a);
	}

	vector<int> vis(n, false);
	auto dfs = [&] (auto&& self, int u) -> pair<int, int> {
		vis[u] = true;
		int vt = 1, ed = 0;
		for (int v : g[u]) {
			ed++;
			if (!vis[v]) {
				auto [a, b] = self(self, v);
				vt += a, ed += b;
			}
		}
		return pair(vt, ed);
	};

	int extra = 0;

	vector<int> comps;
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			auto [a, b] = dfs(dfs, i);
			extra += b / 2;
			comps.push_back(a);
		}
	}

	int sz = comps.size();
	auto go = [&] (auto&& self, int l, int r) -> poly {
		if (l == r) {
			poly ret(comps[l] + 1);
			ret.back() = ret.front() = 1;
			return ret;
		}
		int mid = (l + r) / 2;
		auto a = self(self, l, mid);
		auto b = self(self, mid + 1, r);
		return conv(a, b);
	};

	auto a = go(go, 0, sz - 1);
	mint ans = 0;
	for (int i = 0; i < a.size(); i++) {
		ans += a[i] * (mint(2) ^ (n*(n-1)/2 - m - i * (n-i)));
	}

	cout << ans.v << endl;
}
