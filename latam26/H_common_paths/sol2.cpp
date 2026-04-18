#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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
    mod_int(): v(0) {}
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
    m operator -() { return m(-v); }
    m& operator ^= (ll e) {
        if (e < 0) v = inv(v), e = -e;
        v = expo(v, e);
        return *this;
    }
    bool operator == (const m& a) { return v == a.v; }
    bool operator != (const m& a) { return v != a.v; }
    friend m operator +(m a, m b) { return a += b; }
    friend m operator -(m a, m b) { return a -= b; }
    friend m operator *(m a, m b) { return a *= b; }
    friend m operator /(m a, m b) { return a /= b; }
    friend m operator ^(m a, ll e) { return a ^= e; }
    friend ostream& operator <<(ostream& out, m a) {
        return out << a.v;
    }
};

const int MOD = 998244353;

using mint = mod_int<MOD>;

void ntt(vector<mint>& a, bool rev) {
    int n = a.size(); auto b = a;
    assert(!(n&(n-1)));
    mint g = 1;
    while ((g^(MOD/2)) == 1) g += 1;
    if (rev) g = 1 / g;
    for (int step = n / 2; step; step /= 2) {
        mint w = g^(MOD / (n / step)), wn = 1;
        for (int i = 0; i < n/2; i += step) {
            for (int j = 0; j < step; ++j) {
                auto u = a[2*i+j], v = wn * a[2*i+j+step];
                b[i+j] = u + v, b[i + n/2 + j] = u-v;
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

vector<mint> convolution(vector<mint>& a, vector<mint>& b) {
    vector<mint> l(begin(a), end(a)), r(begin(b), end(b));
    int N = l.size() + r.size() - 1;
    int n = 1, log_n = 0;
    while (n <= N) n *= 2, log_n++;
    assert(N <= n);
    l.resize(n);
    r.resize(n);
    ntt(l, false), ntt(r, false);
    for (int i = 0; i < n; ++i) l[i] *= r[i];
    ntt(l, true);
    l.resize(N);
    return l;
}

void solve() {
    auto add = [] (vector<mint>& a, vector<mint>& b) {
        if (a.size() < b.size()) a.resize(b.size());
        for (int i = 0; i < b.size(); ++i) a[i] += b[i];
    };
    int n; cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> subt(n), vis(n), subt_0(n), alt(n), lx(n), rx(n);
    vector<mint> ans(n);
    vector<vector<int>> table(n, vector<int>(20));
    auto jump = [&] (int u, int k) {
        for (int i = 0; i < 20; ++i) {
            if (k >> i & 1) u = table[u][i];
        }
        return u;
    };
    auto is_anc = [&] (int u, int v) {
        return (lx[u] <= lx[v] and rx[v] <= rx[u]);
    };
    auto rooted_subt = [&] (int c, int u) {
        if (u == c) return n;
        if (is_anc(u, c)) {
            int z = jump(c, alt[c] - alt[u] - 1);
            return n - subt_0[z];
        }
        return subt_0[u];
    };
    int tt = 0;
    auto dfs0 = [&] (auto&& self, int u, int p) -> int {
        subt_0[u] = 1;
        alt[u] = 1 + alt[p];
        lx[u] = ++tt;
        if (u != p) {
            table[u][0] = p;
            for (int i = 1; i < 20; ++i) table[u][i] = table[table[u][i-1]][i-1];
        }
        for (auto v : g[u]) {
            if (v == p) continue;
            subt_0[u] += self(self, v, u);
        }
        rx[u] = tt;
        return subt_0[u];
    };
    dfs0(dfs0, 0, 0);
    auto get_tam = [&] (auto&& self, int u, int p) -> int {
        subt[u] = 1;
        for (auto v : g[u]) {
            if (v == p or vis[v]) continue;
            subt[u] += self(self, v, u);
        }
        return subt[u];
    };
    auto get_cen = [&] (auto&& self, int u, int p, int N) -> int {
        for (auto v : g[u]) {
            if (vis[v] or v == p) continue;
            if (2 * subt[v] > N) return self(self, v, u, N);
        }
        return u;
    };
    vector<mint> cur_t = {0};
    int C;
    mint tam_subt_eu;
    mint tudo = 0;
	vector<int> temp_alt(n);
	auto explore = [&] (auto&& self, int u, int p, int h) -> int {
		temp_alt[u] = h;
		for (auto v : g[u]) {
			if (v == p or vis[v]) continue;
			temp_alt[u] = max(temp_alt[u], self(self, v, u, h+1));
		}
		return temp_alt[u];
	};
    auto dfs = [&] (auto&& self, int u, int p, int h) -> void {
        while (cur_t.size() <= h) cur_t.push_back(0);
        mint coeff = rooted_subt(C, u);
        coeff *= coeff;
        for (auto v : g[u]) {
            if (v == p) continue;
            mint peq = rooted_subt(C, v);
            peq *= peq;
            coeff -= peq;
            if (vis[v]) continue;
            self(self, v, u, h+1);
        }
        cur_t[h] += coeff;
        mint resto = (n - tam_subt_eu); resto *= resto;
        ans[h] += coeff * (resto - tudo + tam_subt_eu * tam_subt_eu);
    };
    auto decomp = [&] (auto&& self, int u) -> void {
        C = get_cen(get_cen, u, u, get_tam(get_tam, u, u));
        vis[C] = 1;
        vector<mint> sum_t, res;
        tudo = 0;
        for (auto v : g[C]) {
            mint z = rooted_subt(C, v);
            z *= z;
            tudo += z;
			if (!vis[v]) explore(explore, v, C, 1);
        }
		sort(begin(g[C]), end(g[C]), [&] (int x, int y) {
				return temp_alt[x] < temp_alt[y];
				});
        //cout << "C = " << C << endl;
        for (auto v : g[C]) {
            if (vis[v]) continue;
            tam_subt_eu = rooted_subt(C, v);
            cur_t = {0};
            dfs(dfs, v, C, 1);
            //cout << "T_" << v << "(x) = ";
            //for (auto x : cur_t) cout << x << " ";
            //cout << endl;
            auto P = convolution(cur_t, cur_t);
            for (auto& x : P) x *= -1;
            add(res, P);
            add(sum_t, cur_t);
        }
        if (sum_t.empty()) return;
        sum_t = convolution(sum_t, sum_t);
        add(res, sum_t);
        for (auto& x : res) x /= 2;
        for (int j = 1; j < min(n, (int)res.size()); ++j) ans[j] += res[j];
        for (auto v : g[C]) {
            if (!vis[v]) self(self, v);
        }
    };
    decomp(decomp, 0);
    for (int i = 1; i < n; ++i) cout << ans[i] << " \n"[i==n-1];
}

int32_t main() {_
    solve();
}
