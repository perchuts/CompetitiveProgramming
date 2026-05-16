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
mint fat[maxn], ifat[maxn];
mint ncr(int a, int b) {
    if (a < b or min(a, b) < 0) return 0;
    return fat[a] * ifat[b] * ifat[a-b];
}
void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    vector<mint> dp(k+1);
    vector tr(k+1, vector(k+1, vector(2, mint(0))));
    for (int aqui = 0; aqui <= k; ++aqui) {
        for (int i = 0; i + aqui <= k; ++i) {
            if (i >= aqui-1) {
                int k = (i-aqui+1)/2;
                tr[aqui][i][0] = ncr(k+aqui, aqui);
            }
            if (i >= aqui) {
                int k = (i - aqui) / 2;
                tr[aqui][i][1] = ncr(k+aqui, aqui);
            }
        }
    }
    // aq X aq X aq X X X
    // caso par: x0 + x1 + ... + x_{aqui-1} <= i
    // x0 precisa ser par, resto precisa ser impar
    // => x0 + x1 + ... + x_{aqui-1} <= (i-aqui+1)/2, xj >= 0
    // then let k = (i-aqui+1)/2
    // ncr(k+aqui, aqui)
    //
    // caso impar: x0 + x1 + ... + x_{aqui-1} <= i
    // x0 precisa ser impar, resto precisa ser impar
    // => x0 + x1 + ... + x_{aqui-1} <= (i - aqui) / 2, xj >= 0
    dp[0] = 1;
    for (int i = n-1; ~i; --i) {
        vector<mint> ndp(k+1);
        for (int use = 0; use <= k; ++use) {
            for (int j = 0; j + use <= k; ++j) {
                ndp[use+j] += dp[j] * tr[use][j][s[i]-'0'];
            }
        }
        swap(dp, ndp);
    }
    cout << dp[k] << endl;
}

int32_t main() {_
    fat[0] = 1;
    for (int i = 1; i < maxn; ++i) fat[i] = i * fat[i-1];
    ifat[maxn-1] = mint(1) / fat[maxn-1];
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
