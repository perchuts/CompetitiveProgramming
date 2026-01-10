#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = 1e9+7;
const int maxn = 3e5+100;
//
// 1/(x-1) + 1/(2x-1) + 1/(3x-1)
// (3x-2)/(2x^2-3x+1) + 1/(3x-1)
// (9x^2-9x+2  + 2x^2-3x+1) = 11x^2 - 12x + 3
// (6x^3 -9x^2 + 3x -2x^2 +3x -1) = 6x^3 -11x^2 +6x -1

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
mint fast_evaluate(poly c, poly s, ll k) {
	if (k < s.size()) return s[k];
	int n = c.size();

	poly f(n + 1, 1);
	for (int i = 0; i < n; i++) f[i] = -c[n-i-1];

	poly a = {0, 1}, x = {1};
	while (k) {
		if (k&1) x = divmod(convolution(x, a), f).second;
		a = divmod(convolution(a, a), f).second, k >>= 1;
	}

	mint ret = 0;
	for (int i = 0; i < x.size(); i++) ret += x[i] * s[i];
	return ret;
}
mint solve(int n, int t, vector<mint> a) {
    mint sum_all = 0;
    for (auto& x : a)  sum_all += x;
    if (t == 1 or n == 1) return 0;
    if (t == 2) return (sum_all - a[0]);
    auto solve = [&] (auto&& self, int l, int r) -> pair<vector<mint>, vector<mint>> {
        if (l == r) return {{0, a[l]}, {-1, a[l]}};
        int md = (l+r)/2;
        auto [N1, D1] = self(self, l, md);
        auto [N2, D2] = self(self, md+1, r);
        auto x1 = convolution(N1, D2);
        auto x2 = convolution(N2, D1);
        auto D = convolution(D1, D2);
        vector<mint> N(max(sz(x1), sz(x2)));
        for (int i = 0; i < sz(x1); ++i) N[i] += x1[i];
        for (int i = 0; i < sz(x2); ++i) N[i] += x2[i];
        return {N, D};
    };
    auto [N_q, D_q] = solve(solve, 0, n-1);
    //{
    //    auto DD = D_q; DD.resize(t);
    //    DD = inv(DD);
    //    auto P = convolution(N_q, DD);
    //    P.resize(t);
    //    cout << "P = ";
    //    for (auto x : P) cout << x << " ";
    //    cout << endl;
    //}
    //{
    //    auto DD = D_q;
    //    for (int i = 0; i < sz(D_q); ++i) DD[i] -= N_q[i];
    //    DD = convolution(DD, {1, -2*a[0], a[0]*a[0]});
    //    DD.resize(t);
    //    DD = inv(DD);
    //    auto Z = convolution(DD, D_q);
    //    Z.resize(t);
    //    cout << "Z = ";
    //    for (auto x : Z) cout << x << " ";
    //    cout << endl;
    //}
    // 1/(1-n_q/d_q) (xa[0]-1)(xa[0]-1)
    // d_q/(d_q-n_q) (xa[0]-1)^2

    auto N = D_q;
    auto D = D_q;
    for (int i = 0; i < sz(D_q); ++i) D[i] -= N_q[i];
    D = convolution(D, {1, -2*a[0], a[0]*a[0]});

    int d = sz(D)-1;
    auto [lixo, R] = divmod(N, D);
    auto G = inv(D); G.resize(d);
    auto S = convolution(R, G);
    S.resize(d);
    vector<mint> C(d);
    for (int i = 0; i < d; ++i) C[i] = -D[i+1] / D[0];
    mint ans = a[0]; ans ^= (t-1); ans *= -1;
    ans += fast_evaluate(C, S, t-1);
    if (t % 2 == 0) ans *= -1;
    return ans;
}

mint brute(int n, int t, vector<mint> a) {
    vector<mint> dp(n); dp[0] = 1;
    for (int i = 0; i < t-1; ++i) {
        vector<mint> ndp(n);
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                if (x == y) continue;
                ndp[x] += dp[y] * a[x];
            }
        }
        swap(dp, ndp);
    }
    mint ans = 0;
    for (int i = 1; i < n; ++i) ans += dp[i];
    return ans;
}

mint solve_slow(int n, int t, vector<mint> a) {
    mint sum_all = 0;
    for (auto& x : a)  sum_all += x;
    if (t == 1 or n == 1) return 0;
    if (t == 2) return (sum_all - a[0]);
	vector<mint> P(t), P2(t);
	for (int i = 1; i < t; ++i) {
		for (int j = 0; j < n; ++j) {
			mint z = a[j];
			z ^= i;
			if (j == 0) P2[i] += z;
			P[i] += z;
		}
		P[i] *= -1;
		P2[i] *= -1;
	}
    //cout << "P = ";
    //for (auto x : P) cout << x << " ";
    //cout << endl;
    auto Q = P; for (auto& x : Q) x *= -1;
    P2[0] -= 1;
    Q[0] = 1; Q = inv(Q);
   // cout << "Q = ";
   // for (auto x : Q) cout << x << " ";
   // cout << endl;
    auto Z = convolution(Q, convolution(P2, P2));
    //Z.resize(t);
    //cout << "Z = ";
    //for (auto x : Z) cout << x << " ";
    //cout << endl;
    mint ans = Z[t-1] + P2[t-1];
    if (t % 2 == 0) ans *= -1;
    return ans;
}
int32_t main() {_
#ifndef gato
    int n, t; cin >> n >> t;
    vector<mint> a(n);
    for (auto& x : a) cin >> x;
    //cout << "Slow: " << endl;
    //cout << solve_slow(n, t, a) << endl;
    //cout << "Fast: " << endl;
    cout << solve(n, t, a) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 30), T = rnd(1, 150);
        vector<mint> a(n);
        for (auto& x : a) x = rnd(1, mod);
        auto my = solve(n, T, a);
        auto ans = brute(n, T, a);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << T << endl;
            for (auto x : a) cout << x << " ";
            cout << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
