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
void solve(){
    int n; cin >> n;
    vector<vector<int>> adj(n, vector<int>(n));
    for (auto& x : adj) for (auto& y : x) cin >> y;
    vector<int> par(n), lvl(n, 1); iota(all(par), 0);
    auto findp = [&] (auto&& self, int u) -> int { return par[u] = (par[u] == u ? u : self(self, par[u])); };
    auto merge = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) {
            cout << 0 << endl;
            exit(0);
        }
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u, lvl[u] += lvl[v];
    };
    int edg = 0;
    for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j) {
        if (adj[i][j] == 1) merge(i, j), edg++;
    }
    int N = 0;
    vector<int> who(n);
    for (int i = 0; i < n; ++i) if (findp(findp, i) == i) who[i] = N++;
    if (N == 1) {
        cout << 1 << endl;
        exit(0);
    }
    vector<vector<mint>> M(N, vector<mint>(N));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(par[i] == findp(findp, i));
            if (adj[i][j] == -1 and par[i] != par[j]) {
                M[who[par[i]]][who[par[j]]] -= 1;
                M[who[par[i]]][who[par[i]]] += 1;
            }
        }
    }
    M.pop_back();
    for (auto& x : M) x.pop_back();
    auto get_det = [&] (vector<vector<mint>> M) {
        int n = sz(M);
        mint det = 1;
        auto get = [&] (int i) {
            for (int j = i; j < n; ++j) {
                if (M[j][i] != 0) return j;
            }
            return -1LL;
        };
        for (int i = 0; i < n; ++i) {
            int k = get(i);
            if (k == -1) return mint(0);
            if (k != i) swap(M[i], M[k]), det *= -1;
            mint X = M[i][i];
            det *= X;
            for (int j = 0; j < n; ++j) M[i][j] /= X;
            for (int j = i+1; j < n; ++j) {
                mint Y = M[j][i];
                for (int w = 0; w < n; ++w) M[j][w] -= M[i][w] * Y;
            }
        }
        return det;
    };
    cout << get_det(M) << endl;
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}

