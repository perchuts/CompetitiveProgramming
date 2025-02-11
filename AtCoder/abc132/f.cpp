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

typedef mod_int<(int)1e9+7> mint;
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
void solve(){
    int n, k; cin >> n >> k;
    int K = k*2+10;
    vector<vector<vector<mint>>> dp(k+1, vector<vector<mint>>(K, vector<mint>(K)));
    for (int i = 1; i < K; ++i) dp[0][i][1] = 1;
    for (int i = 1; i <= k; ++i) {
        for (int a = 1; a < K; ++a) {
            for (int b = 1; b < K; ++b) {
                for (int c = 1; c * b <= a; ++c) {
                    dp[i][a][b] += dp[i-1][a][c];
                }
            }
        }
    }
    vector<mint> vals;
    for (int i = 0; i < K; ++i) {
        mint s = 0;
        for (int j = 0; j < K; ++j) s += dp[k][i][j];
        vals.pb(s);
    }
    cout << evaluate_interpolation(n, vals) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
