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

const int block = 318;

vector<vector<mint>> pre;
vector<mint> fat, ifat;

mint ncr(int a, int b) {
    if (min(a, b) < 0 or a < b) return mint(0);
    return fat[a] * ifat[b] * ifat[a-b];
}

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    int q0 = 0, q1 = 0;
    vector<int> w1(n-k+1), w0(n-k+1);
    for (int i = 0; i <= n-k; ++i) {
        if (s[i] == '?') continue;
        if (s[i] == '0') q0++;
        else q1++;
    }
    vector<mint> pot(n+1, 1);
    for (int i = 1; i <= n; ++i) pot[i] = 2 * pot[i-1];
    auto get = [&] (int i, int l) {
        mint tot = 0;
        if (i <= block) {
            for (int j = l; j <= i; ++j) tot += ncr(i, j);
            return tot;
        }
        int j = l;
        while (j >= 0 and j % block != block-1) tot += ncr(i, j--);
        tot += pre[i][j/block];
        return pot[i] - tot;
    };
    auto conta = [&] (int x, int y) {
        int z = k-1-x-y;
        // BRUH COMPLIQUEI PRA CARALHO KKKKKKKKKKKKKK
        // x + i = (k-1)/2
        int i = (k-1)/2 - x;
        return ncr(z, i);
    };
    mint ans = 0;
    if (q0 == 0) {
        // can do everything 1's
        int a = 0, b = 0, c = 0;
        for (int i = n-k+1; i < n; ++i) {
            if (s[i] == '?') a++;
            else if (s[i] == '0') b++;
            else c++;
        }
        for (int i = 0; i <= a; ++i) {
            if (c + i + 1 > b + a - i) ans += ncr(a, i);
        }
    }
    if (q1 == 0) {
        // can do everything 0's
        int a = 0, b = 0, c = 0;
        for (int i = n-k+1; i < n; ++i) {
            if (s[i] == '?') a++;
            else if (s[i] == '0') b++;
            else c++;
        }
        for (int i = 0; i <= a; ++i) {
            if (b + i + 1 > c + a - i) ans += ncr(a, i);
        }
    }
    cout << ans << " ";
    q1 = q0 = 0;
    // want to check if, starting at i+1, the string can be periodic
    vector<int> good(n+1, 1), val(n, -1);
    for (int i = n-1; i > n-k; --i) {
        if (s[i] == '0') w0[n-k]++, val[i] = 0;
        if (s[i] == '1') w1[n-k]++, val[i] = 1;
    }
    for (int i = n-k; i; --i) {

        good[i] = good[i+1];
        good[i] &= (s[i] == '?' or s[i+k-1] == '?' or s[i] == s[i+k-1]);

        if (good[i] == 0) break;

        if (s[i] == '0') val[i] = 0;
        else if (s[i] == '1') val[i] = 1;
        else val[i] = val[i+k-1];

        w0[i-1] = w0[i], w1[i-1] = w1[i];

        if (val[i] == 0) w0[i-1]++;
        if (val[i] == 1) w1[i-1]++;

        if (val[i+k-1] == 0) w0[i-1]--;
        if (val[i+k-1] == 1) w1[i-1]--;
    }

    for (int i = 0; i < n-k; ++i) {
        if (s[i] == '0') q0++;
        if (s[i] == '1') q1++;
        if (min(q1, q0) > 0) break;
        if (good[i+1]) {
            // tentar fazer 1's
            int qt0 = w0[i], qt1 = w1[i];
            
            if (q0 == 0) {
                cout << "fazendo conta em i = " << i << " pra 1" << endl;
                cout << conta(qt1, qt0) << endl;
                ans += conta(qt1, qt0);
            }
            // tentar fazer 0's
            if (q1 == 0) {
                cout << "fazendo conta em i = " << i << " pra 0" << endl;
                cout << conta(qt0, qt1) << endl;
                ans += conta(qt0, qt1);
            }
        }
    }
    cout << ans << endl;
}

int32_t main() {_
    const int n = 100000;
    fat.resize(n+1);
    ifat.resize(n+1);
    pre.resize(n+1);
    fat[0] = 1;
    for (int i = 1; i <= n; ++i) fat[i] = fat[i-1] * i;
    ifat[n] = mint(1) / fat[n];
    for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1];
    for (int i = block; i <= n; ++i) {
        for (int j = 0; j + block-1 <= i; j += block) {
            if (j/block == sz(pre[i-1])) {
                mint a = 0;
                for (int z = j; z < j + block; ++z) a += ncr(i, z);
                pre[i].pb(a);
            } else {
                mint a = 2*pre[i-1][j/block] - ncr(i-1, j+block-1);
                pre[i].pb(a);
            }
        }
    }
        for (int i = block; i <= n; ++i) {
            for (int j = 1; j < sz(pre[i]); ++j) pre[i][j] += pre[i][j-1];
        }
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
