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

typedef mod_int<(int)mod> mint;
void solve(){
    int n;
    mint x, y; cin >> n >> x >> y;
    string s; cin >> s;
    using matrix = vector<vector<mint>>;
    auto mult = [] (matrix a, matrix b) {
        int n = sz(a);
        matrix c(n, vector<mint>(n));
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) for (int k = 0; k < n; ++k) c[i][j] += a[i][k] * b[k][j];
        return c;
    };
    mint cyc = 1;
    x = x / mint(100), y = y / mint(100);
    int m = 24;
    for (int i = 0; i < m; ++i) cyc *= (s[i] == 'T' ? mint(1-x) : mint(1-y));
    cyc = 1 / (1 - cyc);
    matrix p(m, vector<mint>(m)), ans = p;
    for (int i = 0; i < m; ++i) ans[i][i] = 1;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            int k = (i+1) % m;
            p[i][j] = (s[j] == 'T' ? x : y);
            while (k != j) p[i][j] *= (s[k] == 'T' ? mint(1-x) : mint(1-y)), k = (k+1)%m;
            p[i][j] *= cyc;
        }
    }
    while (n) {
        if (n&1) ans = mult(ans, p);
        p = mult(p, p), n /= 2;
    }
    mint tot = 0;
    for (int i = 0; i < m; ++i) if (s[i] == 'A') tot += ans[m-1][i];
    cout << tot << endl;
    
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
