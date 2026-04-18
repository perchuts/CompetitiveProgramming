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

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n), comps;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> comp(n, -1), par(n);
    vector<mint> ans(n-1);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        comps.back().pb(u);
        par[u] = p;
        comp[u] = sz(comps)-1;
        for (auto v : g[u]) {
            if (v != p) self(self, v, u);
        }
    };
    for (int i = 0; i < n; ++i) {
        if (comp[i] == -1) {
            comps.pb({});
            dfs(dfs, i, i);
        }
    }
    mint tudo = 1;
    if (sz(comps) != 1) {
        for (int i = 1; i <= sz(comps)-2; ++i) tudo *= n;
        for (auto x : comps) tudo *= sz(x);
    }
    if (comp[n-1] == comp[n-2]) {
        dfs(dfs, n-1, n-1);
        int cur = n-2;
        while (par[cur] != n-1) cur = par[cur];
        ans[cur] = tudo;
        for (auto x : ans) cout << x << " ";
        cout << endl;
        return;
    }
    int t1 = sz(comps[comp[n-2]]), t2 = sz(comps[comp[n-1]]), k = sz(comps);
    mint resto = tudo;
    int z = 0, zz = 0;
    for (int i = 0; i < n-1; ++i) {
        if (comp[i] == comp[n-2]) {
            if (t1 + t2 < n) ans[i] = tudo * (t1+t2) / (t1*t2*n);
            else ans[i] = 1;
            resto -= ans[i];
        }
        if (comp[i] != comp[n-1] and comp[i] != comp[n-2]) z++;
    }
    for (auto x : g[n-1]) comps.pb({}), dfs(dfs, x, n-1), zz += sz(comps.back());
    mint tot = (n * zz + z);
    if (tot == 0) resto = 0;
    else resto /= tot;
    for (int i = 0; i < n-1; ++i) {
        if (comp[i] == comp[n-2]) continue;
        int tam = sz(comps[comp[i]]);
        if (par[i] == n-1) ans[i] = resto * tam * n;
        else if (comp[i] < k) ans[i] = resto;
    }
    for (auto x : ans) cout << x << " ";
    cout << endl;
}


int32_t main() {_
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
