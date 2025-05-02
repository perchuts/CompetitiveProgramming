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
// Avaliacao de Interpolacao
//
// Dado 'n' pontos (i, y[i]), i \in [0, n),
// avalia o polinomio de grau n-1 que passa
// por esses pontos em 'x'
// Tudo modular, precisa do mint
//
// O(n)
using mint = mod_int<mod>;

mint evaluate_interpolation(int x, vector<mint> y) {
	int n = y.size();
	
	vector<mint> sulf(n+1, 1), fat(n, 1), ifat(n);
	for (int i = n-1; i >= 0; i--) sulf[i] = sulf[i+1] * (x - i);
	for (int i = 1; i < n; i++) fat[i] = fat[i-1] * i;
	ifat[n-1] = 1/fat[n-1];
	for (int i = n-2; i >= 0; i--) ifat[i] = ifat[i+1] * (i + 1);

	mint pref = 1, ans = 0;
	for (int i = 0; i < n; pref *= (x - i++)) {
		mint num = pref * sulf[i+1];

		mint den = ifat[i] * ifat[n-1 - i];
		if ((n-1 - i)%2) den *= -1;

		ans += y[i] * num * den;
	}
	return ans;
}
template<typename T> T evaluate(vector<T> c, vector<T> s, ll k) {
	int n = c.size();
	assert(c.size() <= s.size());

	auto mul = [&](const vector<T> &a, const vector<T> &b) {
		vector<T> ret(a.size() + b.size() - 1);
		for (int i = 0; i < a.size(); i++) for (int j = 0; j < b.size(); j++)
			ret[i+j] += a[i] * b[j];
		for (int i = ret.size()-1; i >= n; i--) for (int j = n-1; j >= 0; j--)
			ret[i-j-1] += ret[i] * c[j];
		ret.resize(min<int>(ret.size(), n));
		return ret;
	};

	vector<T> a = n == 1 ? vector<T>({c[0]}) : vector<T>({0, 1}), x = {1};
	while (k) {
		if (k&1) x = mul(x, a);
		a = mul(a, a), k >>= 1;
	}
	x.resize(n);

	T ret = 0;
	for (int i = 0; i < n; i++) ret += x[i] * s[i];
	return ret;
}
template<typename T> vector<T> berlekamp_massey(vector<T> s) {
	int n = s.size(), l = 0, m = 1;
	vector<T> b(n), c(n);
	T ld = b[0] = c[0] = 1;
	for (int i = 0; i < n; i++, m++) {
		T d = s[i];
		for (int j = 1; j <= l; j++) d += c[j] * s[i-j];
		if (d == 0) continue;
		vector<T> temp = c;
		T coef = d / ld;
		for (int j = m; j < n; j++) c[j] -= coef * b[j-m];
		if (2 * l <= i) l = i + 1 - l, b = temp, ld = d, m = 0;
	}
	c.resize(l + 1);
	c.erase(c.begin());
	for (T& x : c) x = -x;
	return c;
}
template<typename T> T guess_kth(const vector<T>& s, ll k) {
    if (k < sz(s)) return s[k];
	auto c = berlekamp_massey(s);
	return evaluate(c, s, k);
}
void solve(){
    // CCW
    vector<vector<int>> adj = {
        {2, 3, 4, 1},
        {2, 0, 4, 5},
        {0, 1, 5, 3},
        {0, 2, 5, 4},
        {0, 3, 5, 1},
        {3, 2, 1, 4}
    };
    auto count_distinct = [&] (vector<int> caras) {
        set<int> dt;
        vector<int> p(6); iota(all(p), 0);
        vector<int> vals(6);
        do {
            for (int i = 0; i < 6; ++i) vals[i] = caras[p[i]], assert(1 <= vals[i] and vals[i] <= 6);
            int repr = inf;
            for (int i = 0; i < 6; ++i) {
                for (int shift = 0; shift < 4; ++shift) {
                    int tmp = vals[i];
                    for (int k = 0; k < 4; ++k) tmp = 7 * tmp + vals[adj[i][(shift+k)%4]];
                    ckmin(repr, tmp);
                }
            }
            dt.insert(repr);
        } while (next_permutation(all(p)));
        return mint(sz(dt));
    };
    int S; cin >> S;
    vector<vector<int>> test;
    for (int i = 0; i < (1<<5); ++i) {
        int ct = 1;
        vector<int> v;
        for (int j = 0; j < 5; ++j) {
            if (i >> j & 1) v.pb(ct), ct = 1;
            else ct++;
        }
        v.pb(ct);
        sort(all(v));
        test.pb(v);
    }
    sort(all(test)), test.erase(unique(all(test)), end(test));
    int lim = 50;
    vector<vector<mint>> pre_dp(sz(test), vector<mint>(lim+1));
    auto go = [&] (auto&& self, int idt, int sx, int lst_val, int mask) -> void {
        if (mask == (1<<sz(test[idt]))-1) {
            pre_dp[idt][sx] += 1;
            return;
        }
        for (int j = 0; j < sz(test[idt]); ++j) {
            if (mask>>j&1) continue;
            for (int i = lst_val+1; test[idt][j] * i + sx <= lim; ++i) self(self, idt, test[idt][j] * i + sx, i, mask+(1<<j));
        }
    };
    vector<mint> qnt(sz(test));
    mint ans = 0;
    for (int i = 0; i < sz(test); ++i) {
        go(go, i, 0, 0, 0);
        qnt[i] = guess_kth(pre_dp[i], S);
        vector<int> freqs(7);
        for (auto x : test[i]) freqs[x]++;
        for (int j = 1; j <= 6; ++j) {
            for (int k = 2; k <= freqs[j]; ++k) qnt[i] /= mint(k);
        }
        vector<int> bicho;
        for (int j = 0; j < sz(test[i]); ++j) for (int k = 0; k < test[i][j]; ++k) bicho.pb(j+1);
        mint ways = count_distinct(bicho);
        ans += ways * qnt[i];
    }
    cout << ans << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
