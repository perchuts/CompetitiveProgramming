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
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> ans;
    vector<int> dist(n), par(n), color(n);
    auto dfs = [&] (auto&& self, int u, int p) -> void {
        par[u] = p;
        for (auto v : g[u]) {
            if (v == p) continue;
            dist[v] = 1 + dist[u];
            self(self, v, u);
        }
    };
    dfs(dfs, 0, 0);
    int r = 0;
    for (int i = 0; i < n; ++i) if (dist[i] > dist[r]) r = i;
    for (int i = 0; i < n; ++i) dist[i] = 0;
    dfs(dfs, r, r);
    int r2 = 0;
    for (int i = 0; i < n; ++i) if (dist[i] > dist[r2]) r2 = i;
    int tot = dist[r2], cur = r2;
    while (dist[cur] != (tot+1)/2) cur = par[cur];
    vector<int> centers = {cur, par[cur]};
    for (int i = 0; i < n; ++i) dist[i] = 0;
    vector<mint> P(n/2), Q(n/2);
    vector<bool> tem(n);
    auto dfs2 = [&] (auto&& self, int u, int p, int h, int cor) -> void {
        color[u] = cor;
        if (h == tot / 2) tem[u] = 1;
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u, h+1, cor);
            if (tem[v]) {
                if (tem[u]) {
                    if (cor) Q[h] = 1;
                    else P[h] = 1;
                }
                else tem[u] = 1;
            }
        }
    };
    dfs2(dfs2, centers[0], centers[1], 0, 0);
    dfs2(dfs2, centers[1], centers[0], 0, 1);
    //cout << "centers: " << centers[0]+1 << " " << centers[1]+1 << endl;
    auto R = convolution(P, Q);
    //cout << "P: ";
    //for (auto x : P) cout << x << " ";
    //cout << endl;
    //cout << "Q: ";
    //for (auto x : Q) cout << x << " ";
    //cout << endl;
    for (int i = 0; i < sz(R); ++i) if (R[i] != 0) ans.pb(i+1);
    for (int i = 0; i < sz(P); ++i) if (P[i].v) ans.pb(i+1+tot/2);
    for (int i = 0; i < sz(Q); ++i) if (Q[i].v) ans.pb(i+1+tot/2);
    ans.pb(tot);
    sort(all(ans));
    ans.erase(unique(all(ans)), end(ans));
    cout << sz(ans) << " ";
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
