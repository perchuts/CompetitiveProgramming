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
// Matriz

#define MODULAR false
template<typename T> struct matrix : vector<vector<T>> {
	int n, m;

	void print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) cout << (*this)[i][j] << " ";
			cout << endl;
		}
	}

	matrix(int n_, int m_, bool ident = false) :
			vector<vector<T>>(n_, vector<T>(m_, 0)), n(n_), m(m_) {
		if (ident) {
			assert(n == m);
			for (int i = 0; i < n; i++) (*this)[i][i] = 1;
		}
	}
	matrix(const vector<vector<T>>& c) : vector<vector<T>>(c),
		n(c.size()), m(c[0].size()) {}
	matrix(const initializer_list<initializer_list<T>>& c) {
		vector<vector<T>> val;
		for (auto& i : c) val.push_back(i);
		*this = matrix(val);
	}

	matrix<T> operator*(matrix<T>& r) {
		assert(m == r.n);
		matrix<T> M(n, r.m);
		for (int i = 0; i < n; i++) for (int k = 0; k < m; k++)
			for (int j = 0; j < r.m; j++) {
				T add = (*this)[i][k] * r[k][j];
#if MODULAR
#warning Usar matrix<ll> e soh colocar valores em [0, MOD) na matriz!
				M[i][j] += add%MOD;
				if (M[i][j] >= MOD) M[i][j] -= MOD;
#else
				M[i][j] += add;
#endif
			}
		return M;
	}
	matrix<T> operator^(ll e){
		matrix<T> M(n, n, true), at = *this;
		while (e) {
			if (e&1) M = M*at;
			e >>= 1;
			at = at*at;
		}
		return M;
	}
	void apply_transform(matrix M, ll e){
		auto& v = *this;
		while (e) {
			if (e&1) v = M*v;
			e >>= 1;
			M = M*M;
		}
	}
};

void solve() {
    mint a, b, fn, fm;
    int n, m;
    cin >> a >> b >> n >> m >> fn >> fm;
    matrix<mint> M(2, 2);
    M[0][0] = a;
    M[0][1] = b;
    M[1][0] = 1;
    auto get_coeff = [&] (int k) {
        matrix<mint> Mk = M;
        Mk = Mk ^ k;
        return Mk[0];
    };
    // sistema:
    matrix<mint> S(2, 2);
    S[0] = get_coeff(n-1);
    S[1] = get_coeff(m-1);
    matrix<mint> invS(2, 2);
    mint A = S[0][0], B = S[0][1], C = S[1][0], D = S[1][1];
    mint Z = A*D-B*C;
    if (Z != 0) {
        invS[0][0] = D/Z;
        invS[0][1] = -B/Z;
        invS[1][0] = -C/Z;
        invS[1][1] = A/Z;
        mint f1 = invS[0][0] * fn + invS[0][1] * fm;
        mint f0 = invS[1][0] * fn + invS[1][1] * fm;
        cout << f0 << " " << f1 << endl;
    } else {
        assert(false);
    }
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
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
