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
void solve() {
    int n; cin >> n;
    // 1 1
    // 2 1
    // 3 4
    // 8 = 6 * (1 * 1 * 1 / 6 + 1/2 + 4/6)
    // 8 = 1 + 3 + 4 -> ac
    // 2^ncr(n, 2) = soma_k grafos em n vertices com k componentes
    // g(n, k) = \sum_{i=1}^n ncr(n-1, i-1) * g(n-i, k-1) * g(i, 1)
    // g(xi, 1) * (n - (x1+x2+..+x{i-1})-1)! / (xi-1)! * (n - (x1+x2+...+xi))!
    // g(xi, 1) / (xi-1)! * (n-1)! * (n - (x1+x2+..+xi))
    // alternativamente:
    // k >= 2:
    // g(n, k) = (1/k) \sum_{i=1}^n ncr(n, i) * g(n-i, k-1) * g(i, 1)
    // g(n, k) = (1/k!) \sum_{x1+...+xk} \prod g(xi, 1) * (n-pref[i-1])!/(xi)!(n-pref[i])!
    //         = (n!/k!) \sum_{x1+...+xk} \prod g(xi, 1) / xi!
    // g(n, 1) = 2^ncr(n, 2) - \sum_{k=2} g(n, k)
    // g(n, 1) = 2^ncr(n, 2) - n! \sum_{k=2} 1/k! \sum_{x1+...+xk} \prod g(xi, 1) / xi!
    // f(n)    = 2^ncr(n, 2) - n! \sum_{k=2} 1/k! \sum_{x1+...+xk} \prod f(xi) / xi!
    // sanity check:
    // f(1) = f(2) = 1
    // f(3)    = 8           - 6 * (1/2 * (1/2 + 1/2) + 1/6) = 8 - 3 - 1 OK
    // [x^k] P(x) = f(k) / k!
    // [x^n] exp(P(x))    = 2^ncr(n, 2)/n!
    // 2f(n)/n! = 2^ncr(n, 2)/n! - [x^n] exp(P(x))
    // 2P(x)    = Q(x) - exp(P(x))
    // 2P(x) + exp(P(x)) = Q(x)
    // 2 f(n) / n! + \sum_k P^k(x)/k! = 2f(n)/n! + \sum_k 1/k! \sum_{x1+...+xk=n} f(xi)/xi! = # labeled graphs with n nodes / n!
    // 2 f(n) / n! + \sum_k P^k(x)/k! = 2f(n) + n! \sum_k \sum_{x1+...+xk=n} f(xi)/xi! = # labeled graphs with n nodes
    // [x^n] Q(x) = 2^{n*(n-1)/2} / n!
    vector<mint> fat(n+1, 1), ifat(n+1);
    for (int i = 1; i <= n; ++i) fat[i] = fat[i-1] * i;
    ifat[n] = mint(1)/fat[n];
    for (int i = n-1; ~i; --i) ifat[i] = ifat[i+1] * (i + 1);
    vector<mint> expP(n+1);
    vector<mint> pw(n+1, 1);
    for (int i = 1; i <= n; ++i) pw[i] = 2 * pw[i-1];
    for (int i = 2; i <= n; ++i) pw[i] *= pw[i-1];
    expP[0] = 1;
    for (int i = 1; i <= n; ++i) expP[i] = ifat[i] * pw[i-1];
    auto P = log(expP);
    cout << P[n] * fat[n] << endl;
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
