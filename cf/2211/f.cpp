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
const int mod = 676767677;
const int maxn = 3e6+100;

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
mint fat[maxn], ifat[maxn];
int ids[200];
mint ncr(int a, int b) {
    if (min(a, b) < 0 or a < b) return 0;
    return fat[a] * ifat[b] * ifat[a-b];
}
void solve() {
    int n, m; cin >> n >> m;
    // se o array tem K elementos distintos,
    // x1 + x2 + ... + xK = n
    // ncr(n+K-1, n)
    // inc1 + inc2 + inc3 + ... + incK+1 = m-K (first K increases must be non zero)
    // ncr(m, k)
    // total: ncr(n+K-1, n) * ncr(m, k)
    // a smaller, b equal, c larger:
    // if a <= c/2 < a+b, answer = 1
    // else if c/2 < a: answer = 1 + f(a-c/2, b, c)
    // else answer = 1 + f(a, b, c/2)
    mint ans = 0;
    int qt = 0;
    // x1+x2+...+x{n+1} = m, x1 >= 1
    mint tudo = ncr(n+m-1, m-1);
    auto g = [&] (int lx, int rx, int i) {
        // elements from 0 to lx are smaller, elements from rx to n-1 are greater, element i is equal to target
        int esq = i - lx, dir = rx - i;
        mint tot = tudo;
        if (lx != -1) {
            // lx elementos iguais
            // x1 + x2 + ... + x{n+1-esq} = m, x1 >= 1
            mint tira = ncr(n-esq+m-1, m-1);
            tot -= tira;
        }
        if (rx != n) {
            mint tira = ncr(n-dir+m-1, m-1);
            tot -= tira;
        }
        if (lx != -1 and rx != n) {
            mint tira = ncr(n-esq-dir+m-1, m-1);
            tot += tira;
        }
        return tot;
    };
    auto f = [&] (auto&& self, int l, int r) -> void {
        if (l > r) return;
        // remember to add 1, as qt is zero indexed
        int md = (l+r)/2;
        int mn = -1, mx = n;
        for (int i = 0; i < qt; ++i) {
            if (ids[i] < md) ckmax(mn, ids[i]);
            else ckmin(mx, ids[i]);
        }
        ans += g(mn, mx, md) * (qt+1);
        if (l == r) return;
        ids[qt++] = md;
        self(self, md+1, r);
        self(self, l, md-1);
        qt--;
    };
    f(f, 0, n-1);
    cout << ans << endl;
}

int32_t main() {_
    fat[0] = 1;
    for (int i = 1; i < maxn; ++i) fat[i] = fat[i-1] * i;
    ifat[maxn-1] = mint(1)/fat[maxn-1];
    for (int i = maxn-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1];
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
