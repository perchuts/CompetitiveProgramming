#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
#define gato

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
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> fib(n+1);
    fib[1] = 1;
    for (int i = 2; i <= n; ++i) fib[i] = (fib[i-1] + fib[i-2]) % mod;
    for (int i = 2; i <= n; ++i) fib[i] = (fib[i] + fib[i-1]) % mod;
    for (int i = 2; i <= n; ++i) fib[i] = (fib[i] + fib[i-1]) % mod;
    for (int i = 1; i <= n; ++i) cout << fib[i] << ' ';
    cout << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; cin >> t;
    while(t--) solve();
#else
    int n; cin >> n;
    set<vector<int>> sexo;
    auto apply = [&] (vector<int> p, int x) {
        vector<int> np(n);
        for (int i = 0; i < n; ++i) {
            if (p[i] < x) np[i] = p[i]+1;
            if (p[i] > x) np[i] = p[i]-1;
            if (p[i] == x) np[i] = p[i];
        }
        sort(all(np));
        return np;
    };
    vector<int> cnt(n);
    vector<int> fib(n+1);
    fib[1] = 1;
    for (int i = 2; i <= n; ++i) fib[i] = (fib[i-1] + fib[i-2]) % mod;
    for (int i = 2; i <= n; ++i) fib[i] = (fib[i] + fib[i-1]) % mod;
    for (int i = 2; i <= n; ++i) fib[i] = (fib[i] + fib[i-1]) % mod;
    for (int i = 2; i <= n; ++i) fib[i] = (fib[i] + fib[i-1]) % mod;
    for (int i = 1; i <= n; ++i) cout << fib[i] << ' ';
    cout << endl;
    auto go = [&] (auto&& self, vector<int> p) -> void{
        if (sexo.find(p) != end(sexo)) return;
        sexo.insert(p);
        for (auto x : p) cnt[x]++;
        for (int i = 0; i < n; ++i) {
            self(self, apply(p, i));
        }
    };
    vector<int> p(n); iota(all(p), 0);
    go(go, p);
    for (int i = 0; i < n; ++i) cout << "i -> " << cnt[i] << endl;
#endif
}
