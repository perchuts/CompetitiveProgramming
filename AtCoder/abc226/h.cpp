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

typedef mod_int<(int)((119<<23)+1)> mint;
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

poly slowmult(poly a, poly b) {
    poly ret(sz(a)+sz(b)-1);
    for (int i = 0; i < sz(a); ++i) for (int j = 0; j < sz(b); ++j) {
        ret[i+j] += a[i] * b[j];
    }
    return ret;
}

poly sum(poly a, poly b) {
    poly ret(max(sz(a), sz(b)));
    for (int i = 0; i < sz(a); ++i) ret[i] += a[i];
    for (int i = 0; i < sz(b); ++i) ret[i] += b[i];
    return ret;
}
void solve(){
    int n, k; cin >> n >> k;
    vector<ii> intr(n);
    vector<int> vals;
    for (auto& [l, r] : intr) cin >> l >> r, vals.pb(l), vals.pb(r);
    sort(all(vals));
    vals.erase(unique(all(vals)), end(vals));
    auto eval = [&] (int A, int B) {
        vector<poly> dp(n+1, {0});
        dp[0][0] = 1;
        for (auto [l, r] : intr) {
            if (r <= A) continue;
            vector<poly> ndp(n+1, {0});
            if (B <= l) {
                for (int i = 1; i <= n; ++i) ndp[i] = dp[i-1];
                swap(dp, ndp);
                continue;
            }
            mint P = mint(1) / mint(r-l);
            poly nao_usar = {mint(-l)*P, P};
            poly usar = {mint(r)*P, -P};
            for (int i = 1; i <= n; ++i) ndp[i] = slowmult(dp[i-1], usar); 
            for (int i = 0; i <= n; ++i) ndp[i] = sum(ndp[i], slowmult(dp[i], nao_usar));
            swap(dp, ndp);
        }
        poly P;
        for (int i = k; i <= n; ++i) P = sum(P, dp[i]);
        P = I(P);
        mint tot = 0, pA = 1, pB = 1;
        for (int i = 0; i < sz(P); ++i) {
            tot += P[i] * (pB - pA);
            pB = pB * B;
            pA = pA * A;
        }
        return tot;
    };
    mint ans = vals[0];
    for (int i = 0; i < sz(vals)-1; ++i) ans += eval(vals[i], vals[i+1]);
    cout << ans.v << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
