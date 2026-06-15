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

mint fat[2*maxn], ifat[2*maxn];

void solve() {
    int n, k; cin >> n >> k;
    vector<int> b(n);
    for (auto& x : b) cin >> x;
    if (n == 1) {
        cout << b[0] << endl;
        return;
    }
    --k;
    vector<vector<mint>> cf;
    vector<mint> falling_fat(20, 1);
    vector<int> h(n+1);
    for (int i = 0; (1 << i) <= n; ++i) {
        if (i) falling_fat[i] = falling_fat[i-1] * (k + i);
        vector<mint> v(1 << i);
        v.back() = h[(1<<i)] = 1;
        for (int j = (1 << i)-1; j >= 1; --j) {
            h[j] = 1 + h[j + (j & (-j))];
            v[j-1] = falling_fat[h[j]-1] * ifat[h[j]-1];
        }
        cf.pb(v);
    }
    vector<mint> a(n+1);
    for (int i = 1; i <= n; ++i) {
        int tipo = 0;
        while ((i >> tipo & 1) == 0) tipo++;
        a[i] = b[i-1];
        for (int j = 0; j < (1 << tipo) - 1; ++j) {
            a[i] -= cf[tipo][j] * a[i-(1<<tipo)+j+1];
        }
        a[i] /= cf[tipo].back();
        cout << a[i] << " ";
    }
    cout << endl;
    // m2 = [1 1]
    //      [0 1]
    //
    // 1 1 0 1
    // 0 1 0 1
    // 0 0 1 1
    // 0 0 0 1
    //
    // [M_n  E_n ]
    // [ 0   M_n ]
    // = M_{n+1}
    //
    // lets say we know M_n^k
    // what is M_{n+1}^k?
    //
    // [
    // [M_n^k  P_n ] [M_n E_n] = [ M_n^{k+1}     E_n M_n^k + P_n M_n]
    // [ 0   M_n^k ] [ 0  M_n] = [   0         M_n^{k+1}            ]
    // 1 1 0 1 0 0 0 1
    // 0 1 0 1 0 0 0 1
    // 0 0 1 1 0 0 0 1
    // 0 0 0 1 0 0 0 1
    // 0 0 0 0 1 1 0 1
    // 0 0 0 0 0 1 0 1
    // 0 0 0 0 0 0 1 1
    // 0 0 0 0 0 0 0 1
}

int32_t main() {_
    fat[0] = 1;
    for (int i = 1; i < 2*maxn; ++i) fat[i] = i * fat[i-1];
    ifat[2*maxn-1] = mint(1)/fat[2*maxn-1];
    for (int i = 2*maxn-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1];
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
