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

// NTT
//
// Precisa do mint (primitivas de aritmetica modular)
//
// O(n log (n))

const int MOD = 998244353;
typedef mod_int<MOD> mint;
// NTT
//
// Precisa do mint (primitivas de aritmetica modular)
//
// O(n log (n))

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
	int N = l.size()+r.size()-1, n = 1 << __lg(2*N - 1);
	l.resize(n);
	r.resize(n);
	ntt(l, false);
	ntt(r, false);
	for (int i = 0; i < n; i++) l[i] *= r[i];
	ntt(l, true);
	l.resize(N);
	return l;
}
// Operacoes em Polinomios e Series de Potencias
//
// Precisa do NTT
// O exp nao foi bem testado
//
// Fonte: github.com/celiopassos/competitive-programming/blob/master/algorithms/mathematics/formal_power_series.hpp
//
// D, I: O(n)
// inv, divmod, log e exp: O(n log(n))

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

void solve_1(int U) {
    vector<mint> P(U+1), Q(U+1), E(U+1), fat(U+1, 1), ifat(U+1, 1), D(U+1);
    for (int i = 1; i <= U; ++i) fat[i] = fat[i-1] * i, ifat[i] = mint(1) / fat[i];
    E[0] = 1, P[1] = 1, Q[1] = 0;
    auto solve = [&] (auto&& self, int l, int r) -> void {
        if (l == r) {
            if (l == 0) return;
            E[l] /= mint(l);
            P[l+1] = E[l] * fat[l];
            mint k = l+1; k ^= (l-1);
            Q[l+1] = k - P[l+1]; Q[l+1] *= ifat[l];
            D[l] = (l+1) * Q[l+1];
            cout << P[l+1] << endl;
            return;
        }
        int md = (l+r)/2;
        self(self, l, md);
        {
            vector<mint> p_E(md-l+1), p_Q(min(r-l+1, md+1));
            for (int i = l; i <= md; ++i) p_E[i-l] = E[i];
            for (int i = 0; i < sz(p_Q); ++i) p_Q[i] = D[i];
            auto p_C = convolution(p_E, p_Q);
            for (int i = md+1-l; i <= min(r-l, sz(p_C)); ++i) E[i+l] += p_C[i-1];
        }
       if (l) {
            vector<mint> p_E(min(l, r-l+1)), p_Q(md-l+1);
            for (int i = l; i <= md; ++i) p_Q[i-l] = D[i];
            for (int i = 0; i < sz(p_E); ++i) p_E[i] = E[i];
            auto p_C = convolution(p_E, p_Q);
            for (int i = md+1-l; i <= min(r-l, sz(p_C)); ++i) E[i+l] += p_C[i-1];
        }
        self(self, md+1, r);
    };
    solve(solve, 0, U-1);
}

void sholve(int U) {
    vector<mint> P = {0, 1}, fat(U+1, 1), Q = {0, 0};
            // already revealed E[l]. now reveal P[l+1], Q[l+1].
            // base cases? we already know node 1. (E[0]!)
            // need to reveal up to e_{U-1}. then it is enough to have sizes up to U+1.
            // want to reveal coefficient of P one by one.
            // define Q[n] = (n^{n-2} - P[n]) / fat[n-1] -> can be computed after recovering P[n]
            // P[n+1] = [x^n/fat[n]] exp(Q)
            // E = exp(Q)
            // E' = E * Q'
            // as each of those polynomials are EGFs, we have
            // e_{n+1} = \sum{i+j=n} e_i * Q_{j+1} * n! / (i! j!)
            // contribution of [l, md] to [md+1, r]
    for (int i = 1; i <= U; ++i) fat[i] = i * fat[i-1];
    for (int n = 2; n <= U; ++n) {
        auto Z = exp(Q);
        mint ans = Z[n-1] * fat[n-1];
        cout << ans << endl;
        P.pb(ans);
        mint zz = n; zz ^= (n-2);
        Q.pb((zz-ans)/fat[n-1]);
    }
}

// trivial
void solve_2(int U) {
    vector<mint> fat(U+1, 1), pw(U+1, 1);
    pw[1] = 2;
    for (int i = 2; i <= U; ++i) {
        fat[i] = i * fat[i-1];
        pw[i] = 2 * pw[i-1];
        mint tot = i;
        tot ^= (i-2);
        if (i % 2 == 0) {
            mint ways = fat[i] / (fat[i/2] * pw[i/2]);
            mint z = (i/2);
            if (i != 2) {
                z ^= ((i/2)-2);
                ways *= z;
                ways *= pw[(i/2)-1] * pw[(i/2)-1];
            }
            tot -= ways;
        }
        cout << tot << endl;
    }
}

void solve() {
    int U, type; cin >> U >> type;
    if (type == 1) solve_1(U);
    else solve_2(U);
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
    while(t--) solve();
#else
    int t = 1;
    while (true) {
        int my = solve(), ans = brute();
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
