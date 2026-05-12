#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
//#define endl '\n'
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

vector<mint> fat, ifat;

mint ncr(int a, int b) {
    if (min(a, b) < 0 or a < b) return mint(0);
    return fat[a] * ifat[b] * ifat[a-b];
}

mint solve(int n, int k, string s) {
    int q0 = 0, q1 = 0;
    vector<int> w1(n-k+1), w0(n-k+1);
    for (int i = 0; i <= n-k; ++i) {
        if (s[i] == '?') continue;
        if (s[i] == '0') q0++;
        else q1++;
    }
    vector<mint> pot(n+1, 1);
    for (int i = 1; i <= n; ++i) pot[i] = 2 * pot[i-1];
    auto conta = [&] (int x, int y, int t) { return ncr(t-x-y, k/2-x); };
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
            if (c + i > b + a - i) ans += ncr(a, i);
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
            if (b + i > c + a - i) ans += ncr(a, i);
        }
    }
    q1 = q0 = 0;
    // want to check if, starting at i+1, the string can be periodic
    vector<int> good(n+1, 1), val(n, -1);
    for (int i = n-1; i > n-k; --i) {
        if (s[i] == '0') w0[n-k]++, val[i] = 0;
        if (s[i] == '1') w1[n-k]++, val[i] = 1;
    }
    for (int i = n-k; i; --i) {

        good[i] = good[i+1];
        good[i] &= (s[i] == '?' or val[i+k-1] == -1 or s[i] == s[i+k-1] or char('0'+val[i+k-1]) == s[i]);

        if (s[i] == '0') val[i] = 0;
        else if (s[i] == '1') val[i] = 1;
        else val[i] = val[i+k-1];

        w0[i-1] = w0[i], w1[i-1] = w1[i];

        if (val[i] == 0) w0[i-1]++;
        if (val[i] == 1) w1[i-1]++;

        if (val[i+k-1] == 0) w0[i-1]--;
        if (val[i+k-1] == 1) w1[i-1]--;
    }
	//for (auto x : good) cout << x << " ";
	//cout << endl;
    //cout << ans << endl;
    for (int i = 0; i <= n-k; ++i) {
        if (s[i] == '0') q0++;
        if (s[i] == '1') q1++;
        if (min(q1, q0) > 0) break;
        if (good[i+1]) {
            // tentar fazer 1's
            int qt0 = w0[i], qt1 = w1[i];
            if (q0 == 0 and (i == 0 or val[i+k-1] != 1)) {
                int add = (i != 0 and val[i+k-1] == -1);
                ans += conta(qt1, qt0+add, k-1);
            }
            // tentar fazer 0's
            if (q1 == 0 and (i == 0 or val[i+k-1] != 0)) {
                int add = (i != 0 and val[i+k-1] == -1);
                ans += conta(qt0, qt1+add, k-1);
            }
        }
        //cout << ans << " ";
    }
    //cout << endl;
    return ans;
}

mint brute(int n, int k, string s) {
    vector<int> pos;
    for (int i = 0; i < n; ++i) if (s[i] == '?') pos.pb(i);
    int m = sz(pos);
    mint ans = 0;
    for (int i = 0; i < (1 << m); ++i) {
        string t = s;
        for (int j = 0; j < m; ++j) {
            if (i >> j & 1) t[pos[j]] = '1';
            else t[pos[j]] = '0';
        }
        bool ok = true;
        for (int j = 0; j+k <= n; ++j) {
            int z = 0;
            for (int w = j; w < j + k; ++w) z += t[w] == t[j];
            ok &= (z > k/2);
        }
        ans += ok;
    }
    return ans;
}

int32_t main() {_
    const int n = 100000;
    fat.resize(n+1);
    ifat.resize(n+1);
    fat[0] = 1;
    for (int i = 1; i <= n; ++i) fat[i] = fat[i-1] * i;
    ifat[n] = mint(1) / fat[n];
    for (int i = n-1; ~i; --i) ifat[i] = (i+1) * ifat[i+1];
#ifndef gato
    int t = 1; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        cout << solve(n, k, s) << endl;
    }
#else
    int t = 1;
    while (true) {
        int n = rnd(3, 18), k = rnd(1, (n-1)/2)*2+1;
        string s(n, '0');
        string _t = "10?";
        for (auto& x : s) x = _t[rnd(0, 2)];
        auto my = solve(n, k, s);
        auto ans = brute(n, k, s);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << " " << k << endl;
            cout << s << endl;
            cout << "Solve: " << my << endl;
            cout << "Brute: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
