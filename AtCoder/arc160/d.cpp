#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
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
void solve(){
	int k, n, m; cin >> n >> m >> k;
	if (m % k) {
		cout << 0 << endl;
		return;
	}
	vector<int> fat(n*k+n, 1), ifat = fat;
	for (int i = 1; i < n*k+n; ++i) fat[i] = i * fat[i-1] % mod;
	auto fexp = [&] (int b, int e) {
		b %= mod;
		int ans = 1;
		while (e) {
			if (e&1) ans = ans * b % mod;
			e /= 2, b = b * b % mod;
		}
		return ans;
	};
	ifat.back() = fexp(fat.back(), mod-2);
	for (int i = n*k+n-2; i >= 0; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
	auto ncr = [&] (int a, int b) {
		if (b > a) return 0ll;
		return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
	};
	int mx = (n-k+1)*(k-1);
	vector<int> p1(mx+1), p2(mx+1);
	for (int i = 0; i <= mx; ++i) {
		p1[i] = ncr(n-k+i, i); 
		if (i % k == 0) p2[i] = (((i/k) % 2 ? -1 : 1) * ncr(n-k+1, i/k) + mod) % mod; 
	}
	int ans = 0;
	vector<mint> P(mx+1), Q(mx+1);
	for (int i = 0; i <= mx; ++i) P[i] = p1[i], Q[i] = p2[i];
	auto dp = convolution(P, Q);
	int val = 1;
	int ptr = m/k+n-1;
	for (int i = ptr; i > m/k; --i) {
		int j = i % mod;
		val = val * j % mod;
	}
	for (int i = 0; i <= min(mx, m/k); ++i) {
		int val2 = dp[i].v * ifat[n-1] % mod;
		val2 = val2 * val % mod;
		ans = (ans + val2) % mod;
		if (ptr % mod) {
			val = val * fexp(ptr, mod-2) % mod;
			int j = ptr - n + 1; j %= mod;
			val = val * j % mod;
			ptr--;
		} else {
			val = 1;
			ptr--;
			for (int j = ptr; j > ptr-n+1; --j) {
				int w = j % mod;
				val = val * w % mod;
			}
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
