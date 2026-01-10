#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define gato

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
vector<mint> solve(int n, int k, vector<int> p) {
    vector<mint> fat(n+1, 1), ifat(n+1), resp;
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1];
    ifat[n] = mint(1)/fat[n];
    for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1];
    vector<mint> cc(n+1), bit(n+1);
    auto insert = [&] (int x, mint z = mint(1)) { while (x <= n) bit[x] += z, x += x & (-x); };
    auto query = [&] (int x) { mint ans = 0; while (x) ans += bit[x], x -= x & (-x); return ans; };
    for (int i = 0; i < k; ++i) cc[i] = p[i] - 1 - query(p[i]), insert(p[i]);
    // fixa a menor posicao i onde q[i] < p[i]
    // se t nao aparece em P:
    // se t < p[i]: (n-i)!/(n-k)! => coloca o t em i. nao colocar o t em i: (cc[i]-1) * (k-i) * (n-i-1)!/(n-k)!
    // se t > p[i]: cc[i] * (k-i) * (n-i-1)!/(n-k)!
    // se t aparece em P:
    // se t aparece antes: cc[i] * (n-i)!/(n-k)!
    // se t aparece agora: 0
    // se t aparece depois: mesma analise t < p[i], t > p[i]
    // some isso sobre todo i
    // isso eh basicamente um problema de estrutura!
    // t -> t+1
    // vai ficar guardado na estrutura a relacao de desigualdade estrita. qnd aparecer um cara igual a um termo da sequencia,
    // a gente soma um prefixo disso e o resto vai ser o sufixo precomputado
    // t -> t+1:
    // se aparece t na sequencia: adicione fat[n-i-2] * fat[n-k] * cc[i]
    vector<mint> suf(n+1);
    for (int i = k; i; --i) {
        if (i != n) suf[i] = suf[i+1];
        suf[i] += fat[n-i] * ifat[n-k] * cc[i-1];
    }
    vector<int> occ(n+1, -1);
    for (int i = 0; i < k; ++i) occ[p[i]] = i+1;
    for (int i = 1; i <= n; ++i) bit[i] = 0;
    for (int i = 0; i < k; ++i) {
        if (p[i] != 1) {
            mint adc = fat[n-i-1] * ifat[n-k];
            if (i != k-1) adc += fat[n-i-2] * ifat[n-k] * (k-i-1) * (cc[i]-1);
            insert(i+1, adc);
        }
    }
    auto responde = [&] (int i) {
        if (occ[i] != -1) {
            resp.pb(query(occ[i]-1) + (occ[i] == k ? 0 : suf[occ[i]+1] + cc[occ[i]-1] * (k-occ[i]) * fat[n-occ[i]-1] * ifat[n-k])+1);
        } else {
            resp.pb(query(k));
        }
    };
    responde(1);
    for (int t = 1; t < n; ++t) {
        if (t != 1 and occ[t] != -1 and occ[t] != k) {
            int i = occ[t] - 1;
            insert(i+1, fat[n-i-2] * ifat[n-k] * cc[i] * (k-i-1));
        } 
        if (occ[t+1] != -1) {
            int i = occ[t+1] - 1;
            mint adc = fat[n-i-1] * ifat[n-k];
            if (i != k-1) adc += fat[n-i-2] * ifat[n-k] * (k-i-1) * (cc[i]-1);
            insert(i+1, -adc);
        }
        responde(t+1);
    }
    return resp;
}

vector<mint> brute(int n, int k, vector<int> p) {
    vector<mint> fat(n+1, 1), ifat(n+1), resp;
    for (int i = 1; i <= n; ++i) fat[i] = i * fat[i-1];
    ifat[n] = mint(1)/fat[n];
    for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1];
    vector<mint> cc(n+1), bit(n+1);
    auto insert = [&] (int x, mint z = mint(1)) { while (x <= n) bit[x] += z, x += x & (-x); };
    auto query = [&] (int x) { mint ans = 0; while (x) ans += bit[x], x -= x & (-x); return ans; };
    for (int i = 0; i < k; ++i) cc[i] = p[i] - 1 - query(p[i]), insert(p[i]);
    for (int t = 1; t <= n; ++t) { 
        mint ans = 0;
        bool foi = 0;
        for (int i = 0; i < k; ++i) {
            if (foi) {
                ans += fat[n-i-1] * ifat[n-k] * cc[i];
                continue;
            }
            if (t == p[i]) {
                if (i != k-1) ans += cc[i] * (k-i-1) * fat[n-i-2] * ifat[n-k];
            } else if (t < p[i]) {
                ans += fat[n-i-1] * ifat[n-k];
                if (i != k-1) ans += fat[n-i-2] * ifat[n-k] * (k-i-1) * (cc[i]-1);
            } else {
                if (i != k-1) ans += fat[n-i-2] * ifat[n-k] * cc[i] * (k-i-1);
            }
            if (t == p[i]) { foi = true; continue; }
        }
        if (foi) ans += 1;
        resp.pb(ans);
    }
    return resp;
}

int32_t main() {_
#ifndef gato
    int n, k; cin >> n >> k;
    vector<int> p(k);
    for (auto& x : p) cin >> x;
    auto ans = solve(n, k, p);
    for (auto x : ans) cout << x << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 30), k = rnd(1, n);
        vector<int> p(n); iota(all(p), 1); shuffle(all(p), rng); p.resize(k);
        auto my = solve(n, k, p);
        auto ans = brute(n, k, p);
        for (int i = 0; i < n; ++i) if (my[i] != ans[i]) {
            cout << n << " " << k << endl;
            cout << "Wrong answer on test " << t << endl;
            for (auto x : p) cout << x << " ";
            cout << endl;
            cout << "error for i = " << i+1 << endl;
            cout << "Solve: ";
            for (auto x : my) cout << x << " ";
            cout << endl;
            cout << "Brute: ";
            for (auto x : ans) cout << x << " ";
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
