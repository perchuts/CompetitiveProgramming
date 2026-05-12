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
vector<mint> fat, ifat;

mint ncr(int a, int b) {
    if (min(a, b) < 0 or b > a) return 0;
    return fat[a] * ifat[a-b] * ifat[b];
}
void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    // considere S(l, r) = |qt(1, l, r) - qt(0, l, r)| = x
    // score: x/2 * (x+1)/2
    // nao importa ordem de porra nenhuma, apenas a frequencia dos caracteres. eh isto? eh isto pra kct.
    // \sum_{a=0}^qt0 \sum{b=0}^qt1 ncr(qt0, a) * ncr(qt0, b) * f(|a-b|)
    vector<int> qt(2);
    vector<mint> f(n+1);
    for (int i = 0; i <= n; ++i) f[i] = (i/2) * ((i+1)/2);
    for (int i = 0; i < n; ++i) {
        qt[s[i]-'0']++;
    }
    while (q--) {
        int i; cin >> i; --i;
        if (s[i] == '0') {
            qt[0]--;
            qt[1]++;
            s[i] = '1';
        } else {
            qt[1]--;
            qt[0]++;
            s[i] = '0';
        }
        //if (n == 10) {
        //    for (int j = 0; j < (1 << n); ++j) {
        //        int a = 0, b = 0;
        //        vector<int> v;
        //        for (int k = 0; k < n; ++k) {
        //            if (j >> k & 1) {
        //                if (s[k] == '0') a++, v.pb(-1);
        //                else b++, v.pb(1);
        //            }
        //        }
        //        int my = f[abs(a-b)].v, opt = 0, S = b - a, cur = 0;
        //        for (auto x : v) cur += x, ckmax(opt, cur * (S - cur));
        //        if (my != opt) {
        //            for (auto x : v) cout << x << " ";
        //            cout << endl;
        //            cout << "My: " << my << endl;
        //            cout << "Opt: " << opt << endl;
        //            exit(0);
        //        }
        //    }
        //}
        mint ans = 0;
        for (int a = 0; a <= qt[0]; ++a) for (int b = 0; b <= qt[1]; ++b) {
            mint ways = ncr(qt[0], a) * ncr(qt[1], b) * f[abs(a-b)];
            ans += ways;
        }
        cout << ans << endl;
    }
}

int32_t main() {_
    const int N = 3e5 + 10;
    fat.resize(N), ifat.resize(N);
    fat[0] = 1;
    for (int i = 1; i < N; ++i) fat[i] = i * fat[i-1];
    ifat[N-1] = mint(1) / fat[N-1];
    for (int i = N-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1];
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
