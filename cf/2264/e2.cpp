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
map<vector<int>, int> mp;
vector<int> pr;
int calc(vector<int> a) {
    sort(all(a));
    if (mp.find(a) != end(mp)) return mp[a];
    if (a[0] == a.back()) return mp[a] = a[0];
    int opt = 1;
    for (auto p : pr) {
        auto b = a;
        int ok = 0;
        for (auto& x : b) if (x % p == 0) x--, ok = 1;
        if (ok) ckmax(opt, calc(b));
    }
    return mp[a] = opt;
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

int tab[3005][3005];
vector<vector<int>> caras;
bool ok[3005][3005];

void solve() {
    int n; cin >> n;
    vector<int> a(n), cnt(n+1);
    for (auto& x : a) cin >> x, cnt[x]++;
    mint ans = 0;
    vector<mint> pw(n+1, 1);
    for (int i = 1; i <= n; ++i) pw[i] = 2 * pw[i-1];
    for (int i = 1; i <= n; ++i) {
        mint ways = pw[cnt[i]] - 1;
        ans += ways * i;
        for (int j = i + 1; j <= n; ++j) {
            mint w2 = pw[cnt[j]] - 1;
            ans += ways * w2 * tab[i][j];
            ways *= pw[cnt[j]];
        }
    }
    cout << ans << endl;
}

int32_t main() {_
    caras.resize(3001);
    vector<int> cc(3001);
    for (int i = 2; i <= 3000; ++i) {
        if (cc[i]) continue;
        pr.pb(i);
        for (int j = i; j <= 3000; j += i) cc[j] = 1, caras[j].pb(i);
    }
    for (int i = 1; i <= 3000; ++i) sort(all(caras[i])), caras[i].erase(unique(all(caras[i])), end(caras[i]));
    for (int i = 1; i <= 3000; ++i) {
        for (int j = i + 1; j <= 3000; ++j) {
            ok[i][j] = 1;
            for (auto p : caras[j]) ok[i][j] &= (i % p == 0);
        }
    }
    for (int i = 1; i <= 3000; ++i) {
        tab[i][i] = i;
        for (int j = i+1; j <= 3000; ++j) {
            if (ok[i][j]) tab[i][j] = tab[i-1][j-1];
            else tab[i][j] = tab[i][j-1];
        }
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
