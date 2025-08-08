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
    int n, m, k, l; cin >> n >> m >> k >> l;
    vector<int> a(k), b(l);
    vector<mint> sum_a(m), sum_b(m);
    for (auto& x : a) cin >> x, --x, sum_a[x] += 1;
    for (auto& x : b) cin >> x, --x, sum_b[x] += 1;
    vector<mint> N(2*m+2), pw = N; N[0] = 1;
    pw[0] = pw[1] = pw.back() = 1;
    int e = n-1;
    auto mult_circulante = [] (vector<mint> m1, vector<mint> m2) {
        int tam = sz(m1);
        vector<mint> ans(tam);
        for (int i = 0; i < tam; ++i) m2.pb(m2[i]);
        reverse(all(m2));
        auto P = convolution(m1, m2);
        for (int i = tam-1; i < tam-1+tam; ++i) ans[i-tam+1] = P[i];
        return ans;

    };
    while (e) {
        if (e&1) N = mult_circulante(N, pw);
        pw = mult_circulante(pw, pw), e /= 2;
    }
    // agora X * sum_a (2M+2)*1
    // sum_b^t * X^-1 1*(2M+2)
    // X * sum_a = [sum_a 0 rev(-sum_a) 0]^t
    // sum_b^t * X^-1 = [sum_b 0]
    // certo, entao queremos sum_b^T * M^(n-1) * sum_a
    // seja N matriz circulante com N[0] = (1, 1, ...., 0), de tamanho 2*m+2
    // existe X com dimensoes 2*m+2 por m tal quer XM = NX
    // X = (creditos a gustavocruz)
    // [1 0 0 0 .... 0]
    // [0 1 0 0 .... 0]
    // ...
    // [0 0 0 0 .... 1]
    // [0 0 0 0 .... 0]
    // [0 0 0 0 ....-1]
    // [0 0 0 ....-1 0]
    // [0 0 ....-1 0 0]
    // ...
    // [-1 .... 0 0 0 ]
    // [0 0 .... 0 0 0]
    //
    // se XM^k = N^kX, entao XM^(k+1) = XM^k * M = N^k XM = N^(k+1)X
    // note que a inversa a esquerda de X eh trivial de computar ([I 0])
    // entao computamos sum_b^t * M^(n-1) * sum_a = sum_b^t X^-1 N^(n-1) X * sum_a em O(mlog^2)
    // [sum_b 0] * N^(n-1) * [sum_a 0 rev(-sum_a) 0]^t
    // [e_(b_i) 0] * N^(n-1) * [e_(a_j) 0 -e(m-a_j) 0]^t
    // [b_i-th cyclic shift of N^(n-1)[0]] * [e_(a_j) 0 -e(m-1-a_j) 0]^t
    // N^(n-1)[0][a_j-b_i] - N^(n-1)[0][2*m-a_j-b_i]
    //matrix<mint> M(m, m), X(2*m+2, m), invX(m, 2*m+2), true_N(2*m+2, 2*m+2);
    //for (int i = 0; i < m; ++i) {
    //    for (int j = i-1; j <= i+1; ++j) {
    //        if (0 <= j and j <= m-1) M[i][j] = 1;
    //    }
    //}
    //for (int i = 0; i < m; ++i) X[i][i] = 1, X[m+1+i][m-1-i] = -1, invX[i][i] = 1;
    //for (int i = 0; i < 2*m+2; ++i) {
    //    for (int j = 0; j < 2*m+2; ++j) {
    //        true_N[i][j] = N[(j-i+2*m+2)%(2*m+2)];
    //    }
    //}
    //M = M ^ (n-1);
    //auto myM = invX * true_N * X;
    mint ans = 0;
    //for (auto ax : a) {
        //for (auto bx : b) {
            //ans += N[(ax-bx+sz(N))%sz(N)]; 
            //ans += N[2*m-ax-bx]; 
            //cout << (ax-bx+sz(N))%sz(N) << ' ';
        //}
    //}
    //cout << endl;
    // ans[k] = 0 <= i < m sum_a[i] * sum_b[i-k]
    // ans[k] = {0 <= i < k sum_a[i] * sum_b[i-k+2] } + {k <= i < m sum_a[i] * sum_b[i-k] }
    // # ax - bx === i mod tam
    // 0 ~ tam-1 tam
    // 1 ~ 0
    // 2 ~ 1
    auto revb = sum_b;
    revb.resize(2*m+2);
    for (int i = 0; i < 2*m+2; ++i) revb.pb(revb[i]);
    reverse(all(revb));
    auto P = convolution(sum_a, revb);
    for (int i = 2*m+1; i < 2*m+1+sz(N); ++i) ans += P[i] * N[i-2*m-1];
    auto Q = convolution(sum_a, sum_b);
    for (int i = 0; i < sz(Q); ++i) ans -= Q[i] * N[2*m-i];
    cout << ans << endl;
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
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
