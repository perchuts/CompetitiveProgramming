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

const int LINF = 1e18;
// Convex Hull Trick Dinamico
//
// para double, use LINF = 1/.0, div(a, b) = a/b
// update(x) atualiza o ponto de intersecao da reta x
// overlap(x) verifica se a reta x sobrepoe a proxima
// add(a, b) adiciona reta da forma ax + b
// query(x) computa maximo de ax + b para entre as retas
//
// O(log(n)) amortizado por insercao
// O(log(n)) por query

struct Line {
	mutable ll a, b, p;
	bool operator<(const Line& o) const { return a < o.a; }
	bool operator<(ll x) const { return p < x; }
};

struct dynamic_hull : multiset<Line, less<>> {
	ll div(ll a, ll b) { 
		return a / b - ((a ^ b) < 0 and a % b);
	}
	
	void update(iterator x) {
		if (next(x) == end()) x->p = LINF;
		else if (x->a == next(x)->a) x->p = x->b >= next(x)->b ? LINF : -LINF;
		else x->p = div(next(x)->b - x->b, x->a - next(x)->a);
	}

	bool overlap(iterator x) {
		update(x);
		if (next(x) == end()) return 0;
		if (x->a == next(x)->a) return x->b >= next(x)->b;
		return x->p >= next(x)->p;
	}
		
	void add(ll a, ll b) {
		auto x = insert({-a, -b, 0});
		while (overlap(x)) erase(next(x)), update(x);
		if (x != begin() and !overlap(prev(x))) x = prev(x), update(x);
		while (x != begin() and overlap(prev(x))) 
			x = prev(x), erase(next(x)), update(x);
	}
	
	ll query(ll x) {
        if (empty()) return 1e18;
		auto l = *lower_bound(x);
		return -(l.a * x + l.b);
	}
};
void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    vector<int> vis(n), subt(n);
    vector<vector<int>> par(n), g(n), bichos(n);
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].pb(v), g[v].pb(u);
    }
    vector<int> pp(n), deg(n), ans(n), idx(n), lx(n), rx(n);
    int tt = -1;
    auto go = [&] (auto&& self, int u, int p) -> void {
        lx[u] = idx[u] = ++tt;
        for (auto v : g[u]) {
            if (v == p) continue;
            pp[v] = u;
            ++deg[u];
            self(self, v, u);
        }
        rx[u] = tt;
    };
    go(go, 0, 0);
    vector<dynamic_hull> seg(4*n);
    auto upd = [&] (auto&& self, int i, int l, int r, int x, int a, int b) -> void {
        seg[i].add(a, b);
        if (l == r) return;
        int md = (l+r)/2;
        if (x <= md) self(self, 2*i, l, md, x, a, b);
        else self(self, 2*i+1, md+1, r, x, a, b);
    };
    auto get = [&] (auto&& self, int i, int l, int r, int x, int y, int pos) -> int {
        if (r < x or y < l) return 1e18;
        if (x <= l and r <= y) return seg[i].query(pos);
        int md = (l+r)/2;
        return min(self(self, 2*i, l, md, x, y, pos), self(self, 2*i+1, md+1, r, x, y, pos));
    };
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 0) q.push(i), upd(upd, 1, 0, n-1, idx[i], b[i], 0);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        int pai = pp[u];
        deg[pai]--;
        if (u != 0 and deg[pai] == 0) {
            ans[pai] = get(get, 1, 0, n-1, lx[pai], rx[pai], a[pai]);
            upd(upd, 1, 0, n-1, idx[pai], b[pai], ans[pai]);
            q.push(pai);
        }
    }
    for (auto x : ans) cout << x << ' ';
    cout << endl;
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
