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
int solve(int n, int m){
    if (m < n-1) return 0;
    int N = n+m+1;
    vector<mint> fat(N, 1), ifat(N);
    for (int i = 1; i < N; ++i) fat[i] = i * fat[i-1];
	ifat.back() = mint(1)/fat.back();
    for (int i = N-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1];
    auto C = [&] (int a, int b) {
        if (min(a, b) < 0 or a < b) return mint(0);
        return fat[a] * ifat[b] * ifat[a-b];
    };
    mint ans = 0;
    for (int p1 = 0; p1 < 3; ++p1) {
        for (int p2 = 0; p2 < 3; ++p2) {
            for (int i = 0; i < n; ++i) {
                int j = n-1-i;
                int sobra = m - p1 - p2 - i - 2*j;
                if (sobra < 0 or sobra % 3) continue;
                sobra /= 3;
                ans += C(n-1, i) * C(n+sobra, n);
            }
        }
    }
    return ans.v;
}
// (1/(1-x))^2 * (1/(1-x) - (1/(1-x^3))^(n-1) [x^m]
// 1/(1-x)^2 * ( (1-x^3)-1+x)/((1-x)(1-x^3)))
// 1/(1-x)^2 * ( (x-x^3)/(1-x)^2(1-x-x^2) ) ^ (n-1)
// 1/(1-x)^2n * 1/(1-x-x^2)^(n-1) * (1-x)^(n-1) * (1+x)^(n-1) [x^(m-n+1)]
// 1/(1-x)^(n+1) * 1/(1-x-x^2)^(n-1) * (1+x)^(n-1) [x^(m-n+1)]
// [(x+1)/(1-x^3)]^(n-1) * 1/(1-x)^2 [x^(m-n+1)]
// 1/(1-x)^2: prefix sum da prefix sum!
// [x^k] [(x+1)/(1-x^3)]^(n-1) ?
// [x^3k] (x+1)/(1-x^3) = 1
// [x^3k+1] (x+1)/(1-x^3) = 1
// [x^3k+2] (x+1)/(1-x^3) = 0
// [x^k] [(x+1)/(1-x^3)]^(n-1) = # de jeitos de escrever
// k = a_1 + ... + a_{n-1}
// a_i >= 0, a_i === 0, 1 mod 3
// dp2[3k] = C(n-2+k, k)
// dp[k] = \sum dp2[k-i] * C(n-1, i)

int dpzinha(int n, int m) {
    vector<vector<int>> f(2, vector<int>(m+1));
    for (int i = 0; i <= m; ++i) f[1][i] = i/3+1;
    int ans = 0;
    for (int i = 2; i <= n; ++i) {
        f[i&1][0] = 0;
        for (int j = 1; j <= m; ++j) {
            f[i&1][j] = f[(i-1)&1][j-1];
            if (j >= 3) f[i&1][j] += f[i&1][j-3];
            if (j >= 2) f[i&1][j] += f[(i-1)&1][j-2];
            f[i&1][j] %= mod;
            if (i == n and j >= m-2) ans += f[i&1][j];
        }
    }
    ans %= mod;
    return ans;
}

int32_t main(){_
    int n, m; cin >> n >> m;
    cout << solve(n, m) << endl;
}
