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
    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<mint> F(n+1), sum(n+1);
    //f[0] = 1, f[1] = a[1];
    //for (int i = 2; i <= n; ++i) {
    //    mint soma = f[i-1] / mint(a[i-1]);
    //    for (int j = 0; j <= i-1; ++j) soma += f[j] * f[i-1-j];
    //    f[i] = soma * a[i];
    //}
    //for (int i = 1; i <= n; ++i) cout << f[i].v << ' ';
    // sei que tudo em [1, md] ta resolvido ja!
    // calcular a contribuicao de [l, md] em (md, r] e pelo menos um dos bichos ta em [l, md]
    // vou somar f[i] * f[j] em i+j+1!
    // i \in [l, md] => j \in [0, min(r-l, md)]
    // agora j sendo maior, i sendo estritamente menor (pra nao ter overcounting)
    // j \in [l, md] => i \in [0, min(r-l, l-1)]
    a[0] = 0;
    auto solve = [&] (auto&& self, int l, int r) -> void {
        if (l == r) {
            if (l == 0) F[0] = 1;
            else {
                sum[l] = sum[l-1] + F[l];
                F[l] = sum[l] * a[l];
            }
            return;
        }
        int md = (l+r)/2;
        self(self, l, md);
        int lim1 = min(r-l, md);
        vector<mint> P(md-l+1), Q(lim1+1);
        for (int i = 0; i <= md-l; ++i) P[i] = F[i+l];
        for (int i = 0; i <= lim1; ++i) Q[i] = F[i];
        auto C1 = convolution(P, Q);
        auto C2 = convolution(P, P);
        for (int i = md-l; i < sz(C1) and l+i < r; ++i) F[l+i+1] += 2*C1[i];
        for (int i = max(0LL, md-2*l); i < sz(C2) and 2*l+i < r; ++i) F[2*l+i+1] -= C2[i];
        self(self, md+1, r);
    };
    solve(solve, 0, n);
    for (int i = 1; i <= n; ++i) cout << F[i].v << " \n"[i==n];
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
