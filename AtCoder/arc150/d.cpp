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
const int mod = 998244353;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

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

// NTT
//
// Precisa do mint (primitivas de aritmetica modular)
//
// O(n log (n))

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
	int N = l.size()+r.size()-1, n = 1;
	while (n <= N) n *= 2;
	l.resize(n);
	r.resize(n);
	ntt(l, false);
	ntt(r, false);
	for (int i = 0; i < n; i++) l[i] *= r[i];
	ntt(l, true);
	l.resize(N);
	return l;
}
int fexp(int b, int e) {
	int ans = 1, p = b;
	while (e) {
		if (e&1) ans = ans * p % mod;
		p = p * p % mod, e /= 2;
	}
	return ans;
}

vector<int> g[maxn];
void solve(){
 	int n; cin >> n;
	vector<int> p(n), fat(n+1), ifat(n+1);
	fat[0] = 1;
	for (int i = 1; i <= n; ++i) fat[i] = fat[i-1] * i % mod;
	ifat[n] = fexp(fat[n], mod - 2);
	for (int i = n - 1; i >= 0; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
	for (int i = 1; i < n; ++i) {
		cin >> p[i];
		--p[i];
		g[p[i]].pb(i);
	}
	vector<int> h(n, 1);
	function<void(int)> dfs = [&] (int u) {
		for (auto v : g[u]) h[v] = h[u] + 1, dfs(v);
	};
	dfs(0);
//	auto c = [&] (int a, int b) {
//		return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
//	};
//	for (int k = 0; k < n; ++k) {
//		int tot = n * fexp(n - k, mod - 2) % mod;
//		int aux = 0;
//		for (int i = 0; i < n; ++i) {
//			if (h[i] > k) continue;
//			aux = (aux + c(n - h[i], k - h[i])) % mod;
//		}
//		aux = aux * fexp(c(n, k) * (n - k) % mod, mod - 2) % mod;
//		ans = (ans + tot - aux + mod) % mod;
//	}
	mint ans = 0;
	vector<mint> A(n+1), B(n-1);
	vector<int> freq(n+1);
	for (auto x : h) freq[x]++;

	for (int i = 1; i <= n; ++i) A[i] = freq[i] * fat[n-i];
	for (int i = 0; i <= n - 2; ++i) B[i] = ifat[i];

	auto C = convolution(A, B);
	for (int k = 0; k < n; ++k) {
		mint cf = C[k] * ifat[n] * fat[k];
		ans += (n - cf) / (n - k);
	}
	
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
