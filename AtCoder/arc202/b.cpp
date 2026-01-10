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
	int N = l.size()+r.size()-1, n = 1 << __lg(2*N - 1);
	l.resize(n);
	r.resize(n);
	ntt(l, false);
	ntt(r, false);
	for (int i = 0; i < n; i++) l[i] *= r[i];
	ntt(l, true);
	l.resize(N);
	return l;
}

mint solve(int n, int m) {
    if (n % 2 == 0) return 0;
    // x[0], x[1], x[2]
    // 0 0 -2
    // -2 0 0
    // 0 -2 0
    // 2 0 0
    // 0 2 0
    // 0 0 2
    // 2 2 -2
    // -2 2 2
    // 2 -2 2
    // -2 -2 2
    // -2 2 -2
    // 2 -2 -2
    // 1 1 1
    //-1-1 -1
    // 1 1  1
    //
    //claim no 1.
    //pra cada linha e paridade de colunas, toda vez que eu chego naquela posicao, vou pra uma direcao fixa.
    //caso contrario, suponha que exista linha L e i, j (i % 2 == j % 2) tais que qnd chego em [L][i] vou pra esquerda, e em [L][j] vou pra direita.
    //se i > j, entao existe k tal que i <= k < j onde [L][k] vai pra direita e [L][k+1] vai pra esquerda. quando eu passar pelo segundo cara vou repetir
    //a casa. se i < j, entao se todo prefixo antes do i eh esquerda e todo sufixo depois do j eh direita, ent pega o primeiro e ultimo caras e da merda.
    //caso contrario conseguimos uma analise identica ao caso anterior
    //entao todo mundo vai pra mesma direcao
    if (m & 1) {
        mint ans = 0;
        vector<mint> fat(n+1, 1), ifat(n+1, 1);
        for (int i = 1; i <= n; ++i) ifat[i] = ifat[i-1] / i, fat[i] = fat[i-1] * i;
        for (int S = -n; S <= n; S += 2) {
            int sx = S % m; sx = (sx + m) % m;
            if (m / gcd(sx, m) <= (m-1)) continue;
            int a = (n - S) / 2;
            ans += fat[n] * ifat[a] * ifat[n-a];
        }
        return ans;
    }
    // nota que temos um xadrezinho perfeito row-wise (eh possivel determinar a paridade da coluna pelo numero da rodada!)
    // entao nas rodadas (2K+1) * N nao eh possivel que eu morra, mas eh possivel morrer nas rodadas 2 * K * N
    // entao vamos permitir tudo que eh possivel, mas vamos bloquear esse tipo de coisa
    // (x^{-2} + 2 + x^2) -> indicativo das escolhas possiveis, em duas rodadas
    // ai teremos a soma final, que vai ser o kesimo coeficiente do polinomio acima elevado a n
    vector<mint> poly = {1, 0, 2, 0, 1};
    int pw = 1;
    while (2 * pw <= 4 * n) pw *= 2;
    poly.resize(2*pw);
    ntt(poly, false);
    for (auto& x : poly) x ^= n;
    ntt(poly, true);
    mint ans = 0;
    for (int S = -2*n; S <= 2 * n; S += 2) {
        int sx = S % m; sx = (sx + m) % m;
        if (m / gcd(sx, m) < m/2) continue;
        ans += poly[S+2*n];
    }
    return ans;
}

int32_t main() {_
#ifndef gato
    int n, m; cin >> n >> m;
    cout << solve(n, m) << endl;
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
