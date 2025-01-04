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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// 0 -> 1 <- 2 <- 3 -> 4
// 		v		  v
//      6         5
//
// S - S - F - S - F
//     F       F

//i = 0
//12 18
//0 12
//
//i = 1
//9 3
//6 9
//
//i = 2
//3 0
//3 3
//
// F -> S tem 3 formas
//i = 3
//1 2
//0 1
//
//i = 4
//1 0
//0 1
//
//i = 5
//1 0
//0 1
//
//i = 6
//1 0
//0 1



int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
// Aritmetica Modular
//
// O mod tem q ser primo

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
	m operator -(){ return m(-v); }
	m& operator ^=(ll e) {
		if (e < 0) {
			v = inv(v);
			e = -e;
		}
		v = expo(v, e);
		// possivel otimizacao:
		// cuidado com 0^0
		// v = expo(v, e%(p-1)); 
		return *this;
	}
	bool operator ==(const m& a) { return v == a.v; }
	bool operator !=(const m& a) { return v != a.v; }

	friend istream& operator >>(istream& in, m& a) {
		ll val; in >> val;
		a = m(val);
		return in;
	}
	friend ostream& operator <<(ostream& out, m a) {
		return out << a.v;
	}
	friend m operator +(m a, m b) { return a += b; }
	friend m operator -(m a, m b) { return a -= b; }
	friend m operator *(m a, m b) { return a *= b; }
	friend m operator /(m a, m b) { return a /= b; }
	friend m operator ^(m a, ll e) { return a ^= e; }
};

const int MOD = 998244353;
typedef mod_int<MOD> mint;

void ntt(vector<mint>& a, bool rev) {
	int n = a.size(); auto b = a;
	assert(!(n&(n-1)));
	mint g = 1; 
	while ((g^(MOD / 2)) == 1) g += 1;
	if (rev) g = 1 / g;

	for (int step = n / 2; step; step /= 2) {
		mint w = g^(MOD / (n / step)), wn = 1;
		for (int i = 0; i < n/2; i += step) {
			for (int j = 0; j < step; j++) {
				auto u = a[2 * i + j], v = wn * a[2 * i + j + step];
				b[i+j] = u + v; b[i + n/2 + j] = u - v;
			}
			wn = wn * w;
		}
		swap(a, b);
	}
	if (rev) {
		auto n1 = mint(1) / n;
		for (auto& x : a) x *= n1;
	}
}

vector<mint> convolution(const vector<mint>& a, const vector<mint>& b) {
	vector<mint> l(a.begin(), a.end()), r(b.begin(), b.end());
	int N = l.size()+r.size()-1, n = 1;
	while (n <= N) n *= 2;
	l.resize(n);
	r.resize(n);
	ntt(l, false);
	ntt(r, false);
	for (int i = 0; i < n; i++) l[i] *= r[i];
	ntt(l, true);
	l.resize(N);
	return l;
}

void solve(){
	int n; cin >> n;
	string s; cin >> s;
	vector<vector<ii>> g(n);
	vector<int> val(n);
	for (int i = 0; i < n; ++i) val[i] = (s[i] == 'F');
	for (int i = 0; i < n-1; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].pb({v, 1});
		g[v].pb({u, 0});
	}

	vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(2)));

	auto mult = [&] (vector<ii> v) {
		if (v.empty()) return vector<mint>(1, 1);
		queue<vector<mint>> q;
		for (auto [x, y] : v) {
			vector<mint> k = {mint(x), mint(y)};
			q.push(k);
		}
		while (sz(q) > 1) {
			auto x = q.front(); q.pop();
			auto y = q.front(); q.pop();
			q.push(convolution(x, y));
		}
		return q.front();
	};

	auto dfs = [&] (auto&& self, int u, int ini, int p) -> void {
		vector<int> indo, voltando;
		for (auto [v, dir] : g[u]) {
			if (v == p or ini) continue;
			self(self, v, 0, u), self(self, v, 1, u);
		}
		for (auto [v, dir] : g[u]) {
			if (v == p) continue;
			if (dir == 1) indo.pb(v);
			else voltando.pb(v);
		}
		vector<ii> vp, vq;
		// dp[u][x][y]
		// estado inicial de u = x, estado final de u = y
		// 0 -> S
		// 1 -> F
		// indo sao as operacoes impares, voltando sao as operacoes pares
		if (ini) swap(indo, voltando);
		for (auto v : indo) {
			vp.pb({dp[v][val[v]][0] + dp[v][val[v]][1], dp[v][ini^1][0] + dp[v][ini^1][1]});
			if (val[v] != (ini^1)) vp.back().second += dp[v][val[v]][ini^1];
			// preciso tirar as configuracoes que da pra atingir usando dp[v][x][0], dp[v][x^1][1], vou flipar essa aresta e eles vao ficar iguais :(
			vp.back().first %= mod;
			vp.back().second %= mod;
		}
		for (auto v : voltando) {
			vq.pb({dp[v][val[v]][0] + dp[v][val[v]][1], dp[v][ini][0] + dp[v][ini][1]});
			if (val[v] != ini) vp.back().second += dp[v][val[v]][ini];
			vq.back().first %= mod;
			vq.back().second %= mod;
		}
		auto P = mult(vp);
		auto Q = mult(vq);
		if (u == 2 and ini == 1) {
			for (auto x : P) cout << x << ' '; 
			cout << endl;
			for (auto x : Q) cout << x << ' '; 
			cout << endl;
		}
		for (int i = 0; (i+1)/2 < sz(P) and i/2 < sz(Q); ++i) {
			// quantas operacoes to fazendo
			auto& DP = dp[u][ini][ini^(i&1)];
			DP = (DP + (P[(i+1)/2] * Q[i/2]).v) % mod;
		}
	};

	dfs(dfs, 0, 0, 0), dfs(dfs, 0, 1, 0);

	for (int i = 0; i < n; ++i) {
		cout << "i = " << i << endl;
		cout << dp[i][0][0] << ' ' << dp[i][0][1] << endl;
		cout << dp[i][1][0] << ' ' << dp[i][1][1] << endl;
		cout << endl;
	}

	cout << "ans: ";
	cout << (dp[0][val[0]][0] + dp[0][val[0]][1]) % mod << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
