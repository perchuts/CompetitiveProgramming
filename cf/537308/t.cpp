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

typedef mod_int<(int)998244353> mint;
// Operacoes em Polinomios e Series de Potencias
//
// Precisa do NTT
// O exp nao foi bem testado
//
// Fonte: github.com/celiopassos/competitive-programming/blob/master/algorithms/mathematics/formal_power_series.hpp
//
// D, I: O(n)
// inv, divmod, log e exp: O(n log(n))
// NTT
//
// Precisa do mint (primitivas de aritmetica modular)
//
// O(n log (n))

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

using poly = vector<mint>;

const int MAGIC = 512;

poly D(poly p) {
	if (p.empty()) return p;
	for (int i = 0; i + 1 < p.size(); i++)
		p[i] = (i + 1) * p[i + 1];
	p.pop_back();
	return p;
}

poly I(poly p) {
	int n = p.size();
	p.push_back(0);
	for (int i = n - 1; i >= 0; i--)
		p[i + 1] = p[i] / (i + 1);
	p[0] = 0;
	return p;
}

poly inv(poly p) {
	assert(!p.empty() && p[0] == 1);
	poly q = {mint(1) / p[0]};
	int n = p.size(), k = 1;
	while (k < n) {
		k *= 2;
		q.resize(2 * k);
		ntt(q, false);
		poly p0(2 * k);
		copy_n(p.begin(), min(k, n), p0.begin());
		ntt(p0, false);
		for (int i = 0; i < 2 * k; i++)
			q[i] *= 2 - p0[i] * q[i];
		ntt(q, true);
		q.resize(k);
	}
	q.resize(n);
	return q;
}

pair<poly, poly> divslow(const poly& a, const poly& b) {
	poly q, r = a;
	while (r.size() >= b.size()) {
		q.push_back(r.back() / b.back());
		if (q.back() != 0)
			for (int i = 0; i < b.size(); i++)
				r.end()[-i-1] -= q.back() * b.end()[-i-1];
		r.pop_back();
	}
	reverse(q.begin(), q.end());
	return {q, r};
}

// retorna (q, r) : a(x) = b(x) * q(x) + r(x)
pair<poly, poly> divmod(const poly& a, const poly& b) {
	if (a.size() < b.size()) return {{}, a};
	if (max(b.size(), a.size() - b.size()) < MAGIC) return divslow(a, b);
	poly ra = poly(a.rbegin(), a.rend());
	poly rb = poly(b.rbegin(), b.rend());
	int k = a.size() - b.size() + 1;
	rb.resize(k);
	poly irb = inv(move(rb)), q = convolution(ra, irb);
	q = poly(q.rend() - k, q.rend());
	poly r = convolution(move(q), b);
	for (int i = 0; i < r.size(); i++) r[i] = a[i] - r[i];
	while (r.size() > 1 && r.back() == 0) r.pop_back();
	return {q, r};
}

poly log(poly p) {
	assert(!p.empty() && p[0] == 1);
	int n = p.size();
	auto d = D(p), i = inv(p);
	auto r = convolution(d, i);
	r.resize(n - 1);
	return I(move(r));
}

poly exp(poly p) {
	assert(p.empty() || p[0] == 0);
	poly q = {1};
	int n = p.size(), k = 1;
	while (k < n) {
		k *= 2;
		q.resize(k);
		poly b = log(q);
		for (int i = 0; i < k; i++) b[i] *= -1;
		b[0] += 1;
		for (int i = 0; i < min(n, k); i++) b[i] += p[i];
		q = convolution(q, b);
		q.resize(k);
	}
	q.resize(n);
	return q;
}

poly fexp(poly p, int e, int n) {
	poly pot = p;
	poly ans = {1};
	while (e) {
		if (e&1) ans = convolution(ans, pot);
		pot = convolution(pot, pot);
		pot.resize(n), ans.resize(n);
		e /= 2;
	}
	return ans;
}

void solve(){
	int n, m, k; cin >> n >> m >> k;
	vector<ii> a(n);
	for (auto& [x, y] : a) cin >> x >> y;
	poly P(k+m+1);
	for (auto [x, y] : a) P[y] += x;
	poly P_m = fexp(P, m+1, k+m+1);
	P_m[m+1] = P_m[m+1] - 1;
	mint c0 = mint(1)/P[0];
	P[1] = P[1] - 1;
	for (auto& x : P) x *= c0;
	poly inv_p = inv(P);
	poly ans = convolution(P_m, inv_p);
	mint tot = 0;
	for (int i = 0; i <= k + m; ++i) tot += ans[i];
	cout << (tot * c0) << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
