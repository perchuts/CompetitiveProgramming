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
// NTT
//
// Precisa do mint (primitivas de aritmetica modular)
//
// O(n log (n))
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

vector<mint> convolution(const vector<mint>& a, const vector<mint>& b) {
    vector<mint> c(sz(a) + sz(b) - 1);
    for (int i = 0; i < sz(a); ++i) for (int j = 0; j < sz(b); ++j) {
        c[i+j] += a[i] * b[j];
    }
    return c;
}

mint solve(int n, int m, int k, vector<iii> edg){
    vector<vector<int>> g(2*n);
    vector<int> par(n), lvl(n), repr(n), t(2*n);
    iota(all(par), 0); repr = par;
    int cur = n;
    sort(all(edg));
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    auto merge = [&] (int u, int v, int w) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        g[cur].pb(repr[u]), g[cur].pb(repr[v]);
        t[cur] = w;
        repr[u] = cur++;
        if (lvl[u] == lvl[v]) lvl[u]++;
    };
    for (auto [w, u, v] : edg) merge(u, v, w);
    vector<vector<mint>> dp(cur);
    vector<int> seek(cur);
    auto solve = [&] (auto&& self, int u) -> void {
        if (g[u].empty()) {
            dp[u] = {1, 1};
            seek[u] = 1;
            return;
        }
        int l = g[u][0], r = g[u][1];
        self(self, l), self(self, r);
        seek[u] += (t[u] == t[l] ? seek[l] : 1);
        seek[u] += (t[u] == t[r] ? seek[r] : 1);
        if (t[u] == t[l]) {
            dp[l][1] -= 1;
            if (seek[l] >= sz(dp[l])) dp[l].resize(seek[l]+1);
            dp[l][seek[l]] += 1;
        }
        if (t[u] == t[r]) {
            dp[r][1] -= 1;
            if (seek[r] >= sz(dp[r])) dp[r].resize(seek[r]+1);
            dp[r][seek[r]] += 1;
        }
        dp[u] = convolution(dp[l], dp[r]);
        if (sz(dp[u]) > k+1) dp[u].resize(k+1);
        if (seek[u] <= k) dp[u][seek[u]] -= 1;
        dp[u][1] += 1;
        //cout << "seek = " << seek[u] << endl;
        //cout << "dp[" << u << "] = ";
        //for (auto x : dp[u]) cout << x << ' ';
        //cout << endl;
    };
    vector<mint> ans = {1};
    for (int i = 0; i < n; ++i) {
        if (findp(findp, i) == i) {
            solve(solve, repr[i]);
            ans = convolution(ans, dp[repr[i]]);
            if (sz(ans) > k+1) ans.resize(k+1);
        }
    }
    mint tot = 0;
    for (auto x : ans) tot += x;
    return tot;
}

mint brute(int n, int m, int k, vector<iii> edg) {
    set<int> pode;
    vector<int> par(n), lvl(n);
    iota(all(par), 0);
    vector<vector<ii>> g(n);
    sort(all(edg));
    vector<iii> mst;
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    auto merge = [&] (int u, int v, int w) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        if (lvl[u] == lvl[v]) lvl[u]++;
        mst.pb({u, v, w});
        g[u].pb({v, w}), g[v].pb({u, w});
    };
    for (auto [w, u, v] : edg) merge(u, v, w);
    for (int mask2 = 0; mask2 < (1 << n); ++mask2) {
        if (__builtin_popcount(mask2) > k) continue;
        for (int mask = 0; mask < (1<<(sz(mst))); ++mask) {
            if (__builtin_popcount(mask)+__builtin_popcount(mask2) > k) continue;
            vector<int> color(n), vis(n);
            auto go = [&] (auto&& self, int u, int w) -> void {
                color[u] = vis[u] = 1;
                for (auto [v, w2] : g[u]) {
                    if (vis[v] or w2 > w) continue;
                    self(self, v, w);
                }
            };
            for (int i = 0; i < sz(mst); ++i) {
                if (mask >> i & 1) {
                    for (int j = 0; j < n; ++j) vis[j] = 0;
                    auto [u, v, w] = mst[i];
                    go(go, u, w);
                }
            }
            for (int i = 0; i < n; ++i) color[i] |= (mask2>>i&1);
            int x = 0;
            for (int i = 0; i < n; ++i) x += (color[i] << i);
            pode.insert(x);
        }
    }
    return mint(sz(pode));
}

int32_t main(){_
#ifndef gato
    int n, m, k; cin >> n >> m >> k;
    vector<iii> edg(m);
    for (auto& [w, u, v] : edg) cin >> u >> v >> w, --u, --v;
    cout << solve(n, m, k, edg) << endl;
#else
    int t = 1;
    while (true) {
        int n = rnd(1, 7), m = rnd(1, 10), k = rnd(1, 10);
        vector<iii> edg(m);
        for (auto& [w, u, v] : edg) u = rnd(0, n-1), v = rnd(0, n-1), w = rnd(1, 10);
        mint my = solve(n, m, k, edg);
        mint ans = brute(n, m, k, edg);
        if (my != ans) {
            cout << "Wrong answer on test " << t << endl;
            cout << n << ' ' << m << ' ' << k << endl;
            for (auto [x, y, z] : edg) cout << y+1 << ' ' << z+1 << ' ' << x << endl;
            cout << "Your output: " << my << endl;
            cout << "Answer: " << ans << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
#endif
}
