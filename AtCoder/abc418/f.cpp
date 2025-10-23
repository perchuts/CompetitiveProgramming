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

typedef mod_int<(int)mod> mint;

void solve() {

    int n, q; cin >> n >> q;

    vector<mint> fat(n+1, 1), ifat(n+1), fib(n+2); 

    // init
    {
        fib[0] = fib[1] = 1;
        for (int i = 2; i <= n+1; ++i) fib[i] = fib[i-1] + fib[i-2];
        for (int i = 1; i <= n; ++i) fat[i] = fat[i-1] * i;
        ifat.back() = mint(1) / fat.back();
        for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1];
    }

    auto ncr = [&] (int a, int b) { if (a < b or b < 0) return mint(0); return fat[a] * ifat[b] * ifat[a-b]; };

    vector<int> a(n, -1);

    const int RESET = 1e18 + 69;

    vector<matrix<mint>> seg(4*n, matrix<mint>(2, 2, 1));

    auto upd = [&] (auto&& self, int i, int l, int r, int x, int N, int K) -> void {
        if (l == r) {
            if (K == RESET) {
                seg[i][0][0] = seg[i][1][1] = 1;
                seg[i][0][1] = seg[i][1][0] = 0;
            } else {
                for (int esq = 0; esq < 2; ++esq) 
                    for (int dir = 0; dir < 2; ++dir) {
                        if (min(esq, dir) == 1 and N == 1) seg[i][esq][dir] = 0;
                        else seg[i][esq][dir] = ncr(N-K+1-min(N, esq+dir+1)+dir, K-dir);
                    }
            }
            return;
        }
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, N, K);
        else self(self, 2*i+1, md+1, r, x, N, K);
        seg[i] = seg[2*i] * seg[2*i+1];
    };

    set<ii> val;
    val.insert({-1, 0});

    while (q--) {
        auto add = [&] (int x, int y) {
            if (y == -1) return;
            // ajustar quem vem depois
            {
                auto it = val.lower_bound({x+1, 0});
                if (it != end(val)) {
                    auto [pos, v] = *it;
                    upd(upd, 1, 0, n-1, pos, pos-x, v-y);
                }
            }
            // me ajustar
            auto it = val.lower_bound({x, 0});
            it = prev(it);
            auto [pos, v] = *it;
            upd(upd, 1, 0, n-1, x, x-pos, y-v);
            val.insert({x, y});
        };
        auto rem = [&] (int x) {
            if (a[x] == -1) return;
            val.erase({x, a[x]});
            // ajustar quem vem depois
            {
                auto it = val.lower_bound({x+1, 0});
                if (it != end(val)) {
                    auto [pos, v] = *it;
                    auto prv = prev(it);
                    auto [pos2, v2] = *prv;
                    upd(upd, 1, 0, n-1, pos, pos-pos2, v-v2);
                }
            }
            // me ajustar
            upd(upd, 1, 0, n-1, x, RESET, RESET);
        };
        int x, y; cin >> x >> y; --x;
        rem(x), add(x, y);
        a[x] = y;
        auto [pos, ___] = *prev(end(val));
        int sobra = n-1-pos;
        mint ans = seg[1][0][0] * fib[sobra+1] + seg[1][0][1] * fib[sobra];
        cout << ans << endl;
    }
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
