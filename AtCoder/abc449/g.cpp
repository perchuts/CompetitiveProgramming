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

using poly = vector<mint>;

poly D(poly p) {
	if (p.empty()) return p;
	for (int i = 0; i + 1 < p.size(); i++)
		p[i] = (i + 1) * p[i + 1];
	p.pop_back();
	return p;
}

poly I(poly p) {
	int n = p.size();
	p.push_back(0);
	for (int i = n - 1; i >= 0; i--)
		p[i + 1] = p[i] / (i + 1);
	p[0] = 0;
	return p;
}
poly inv(poly p) {
        poly q = {mint(1) / p[0]};
        int n = p.size(), k = 1;
        while (k < n) {
                k *= 2;
                q.resize(2 * k);
                ntt(q, false);
                poly p0(2 * k);
                copy_n(p.begin(), min(k, n), p0.begin());
                ntt(p0, false);
                for (int i = 0; i < 2 * k; i++)
                        q[i] *= 2 - p0[i] * q[i];
                ntt(q, true);
                q.resize(k);
        }
        q.resize(n);
        return q;
}
poly log(poly p) {
	assert(!p.empty() && p[0] == 1);
	int n = p.size();
	auto d = D(p), i = inv(p);
	auto r = convolution(d, i);
	r.resize(n - 1);
	return I(move(r));
}

poly exp(poly p) {
	assert(p.empty() || p[0] == 0);
	poly q = {1};
	int n = p.size(), k = 1;
	while (k < n) {
		k *= 2;
		q.resize(k);
		poly b = log(q);
		for (int i = 0; i < k; i++) b[i] *= -1;
		b[0] += 1;
		for (int i = 0; i < min(n, k); i++) b[i] += p[i];
		q = convolution(q, b);
		q.resize(k);
	}
	q.resize(n);
	return q;
}
int brute(int n, int m) {
    if (n * m > 1e7) return 0;
    vector<int> vals = {1};
    for (int i = 0; i < m-1; ++i) vals.pb(10*vals.back()+1);
    int N = 2e7 + 10;
    vector<int> dp(N);
    reverse(all(vals));
    int ans = 0;
    for (int i = 1; i < N; ++i) {
        for (auto x : vals) {
            if (x <= i) { dp[i] = 1 + dp[i-x]; break; }
        }
        if (dp[i] <= n and dp[i] % 10 == n % 10 and n <= i) {
            cout << i << ' ' << dp[i] << ": ";
            int cur = i;
            for (auto x : vals) {
                int z = 0;
                while (x <= cur) { z++; cur -= x; }
                cout << x << "("<<z<<")"<<" ";
            }
            if (dp[i] != n) cout << "!";
            cout << endl;
            ans++;
        }
    }
    cout << "answer: " << ans << endl;
    return ans;
}

void solve() {
    int n, m; cin >> n >> m;
    if (n <= 10) {
        // ncr(n+m-1, n)
        mint ans = 1;
        for (int i = n+m-1; i >= m; --i) ans *= i;
        for (int i = 1; i <= n; ++i) ans /= i;
        cout << ans << endl;
        return;
    }
    if (m == 1) {
        cout << 1 << endl;
        return;
    }
    int N = 1;
    while (N <= n) N = 2 * N;
    vector<mint> p(N);
    for (int i = 0; i < 10; ++i) p[i]=1;
    // P(x) = poly
    // T = 1/(1-x) 1/(1-x^10)
    // P^{m-1} T [x^n]
    // = exp((m-1) log P) T [x^n]
    // (isso aqui eh em caso de eu nao usar 10)
    // usando 10:
    // i=0~m-2 (excluo todos dps do 10, incluindo ele mesmo. ja exclui o ultimo)
    // S P^i 1/(1-x)[x^n-10]
    // (1-P^{m-1})/(1-P) T [x^n-10]
    // [exp((m-1) log P)-1]/(1+...+x^8) T x^-1 [x^{n-10}]
    // [exp((m-1) log P)-1]/(1+...+x^8) T [x^{n-11}]
    auto P = log(p);
    for (auto& x : P) x *= (m-1);
    P = exp(P);
    p[9] = 0; auto aux = inv(p); p[9] = 1;
    P[0] -= 1; auto Q = convolution(P, aux); P[0] += 1;
    //cout << "Q: ";
    //for (auto x : Q) cout << x << " ";
    //cout << endl;
    //cout << "P: ";
    //for (auto x : P) cout << x << " ";
    //cout << endl;
    auto transform = [&] (vector<mint>& z) {
        for (int i = 1; i < sz(z); ++i) z[i] += z[i-1];
        for (int i = 10; i < sz(z); ++i) z[i] += z[i-10];
    };
    transform(P), transform(Q);
    mint s1 = P[n], s2 = Q[n-9];
    mint ans = s1 + s2;
    //brute(n, m);
    vector<int> vals = {1};
    while (sz(vals) < m and vals.back() <= n) vals.pb(vals.back() * 10 + 1);
    vector<int> dp(n);
    reverse(all(vals));
    for (int i = 0; i < n; ++i) {
        for (auto x : vals) {
            if (x <= i) { dp[i] = 1 + dp[i-x]; break; }
        }
        if (dp[i] % 10 == n % 10) ans -= 1;
    }
    //cout << s1 << " " << s2 << " ";
    cout << ans << endl;
}

int32_t main() {_
#ifndef gato
    int t = 1; //cin >> t;
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
