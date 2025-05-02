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

// Avaliacao de Interpolacao
//
// Dado 'n' pontos (i, y[i]), i \in [0, n),
// avalia o polinomio de grau n-1 que passa
// por esses pontos em 'x'
// Tudo modular, precisa do mint
//
// O(n)
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
int solve(int n, int m, int k) {
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    if (n == 0) return 0;
    if (m == 0) return fexp(n%mod, k);
    int N = m+k+100;
    vector<mint> f(N);
    for (int i = 1; i < N; ++i) f[i] = fexp(i, k), f[i] += f[i-1];
    for (int j = 2; j <= m; ++j) {
        vector<mint> nf(N);
        for (int i = 1; i < N; ++i) nf[i] = nf[i-1] + f[i];
        swap(nf, f);
    }
    return evaluate_interpolation(n, f).v;
}
//int solve(int n, int m, int k){
//    vector<int> fat(max({k, n, m})+1, 1), ifat(max({k, n, m})+1);
//    for (int i = 1; i < sz(fat); ++i) fat[i] = i * fat[i-1] % mod;
//    auto fexp = [&] (int b, int e) {
//        int ans = 1;
//        while (e) {
//            if (e&1) ans = ans * b % mod;
//            e /= 2, b = b * b % mod;
//        }
//        return ans;
//    };
//    if (m == 0) return fexp(n, k);
//    if (n == 0) return 0;
//    ifat.back() = fexp(fat.back(), mod-2);
//    for (int i = sz(fat)-2; ~i; --i) ifat[i] = (i+1) * ifat[i+1] % mod;
//    auto C = [&] (int a, int b) {
//        if (b > a-b) b = a-b;
//        int ans = ifat[b];
//        for (int i = a; i > a-b; --i) ans = ans * (i%mod) % mod;
//        return ans;
//    };
//    auto C2 = [&] (int a, int b) {
//        return fat[a] * ifat[b] % mod * ifat[a-b] % mod;
//    };
//    int ans = 0;
//    if (k == 0) return C(n+m-1, m);
//    //for (int j = 0; j < k; ++j) {
//    //    int ways = C(k, j);
//    //    if ((k-j+1) % 2) ways = (mod - ways) % mod;
//    //    ans = (ans + ways * solve(n, m+1, j)) % mod;
//    //}
//    vector<int> c(k+1);
//    c[0] = (k%2?mod-1:1);
//    for (int turn = 1; turn <= k; ++turn) {
//        vector<int> nc(k+1);
//        for (int i = 1; i <= k; ++i) {
//            for (int j = 0; j < i; ++j) {
//                nc[i] = (nc[i] - c[j] * ifat[i-j]) % mod;
//                nc[i] %= mod;
//                nc[i] = (nc[i] + mod) % mod;
//            }
//        }
//        swap(c, nc);
//        ans = (ans +c[k] * solve(n, m+turn, 0)) % mod;
//    }
//    return ans * fat[k] % mod;
//    //resposta pra K = 1: C(n+m+1, m+2)
//    //--m
//    //for (int i = 1; i <= n; ++i) ans = (ans + fexp(i, k) * C(n-i+m, m)) % mod;
//    //return ans;
//}

int brute(int n, int m, int k) {
    auto fexp = [&] (int b, int e) {
        int ans = 1;
        while (e) {
            if (e&1) ans = ans * b % mod;
            e /= 2, b = b * b % mod;
        }
        return ans;
    };
    vector<vector<int>> f(n+1, vector<int>(m+1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (j == 0) f[i][j] = fexp(i, k);
            else for (int w = 1; w <= i; ++w) f[i][j] = (f[i][j] + f[w][j-1]) % mod;
        }
    }
    return f[n][m];
}

int32_t main(){_
    int n, m, k; cin >> n >> m >> k;
    cout << solve(n, m, k) << endl;
    //int tt = 1000;
   // for (int i = 0; i < tt; ++i) {
   //     int n = rnd(0, 500), m = rnd(0, 30), k = rnd(0, 252900);
   //     int my = solve(n, m, k), ans = brute(n, m, k);
   //     if (my != ans) {
   //         cout << "Wrong answer on test " << i+1 << endl;
   //         cout << n << ' ' << m << ' ' << k << endl;
   //         cout << "Your output: " << my << endl;
   //         cout << "Answer: " << ans << endl;
   //         exit(0);
   //     }
   //     cout << "Accepted on test " << i+1 << endl;
   // }
}
