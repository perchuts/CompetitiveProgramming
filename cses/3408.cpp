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
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3f;
const int MAX = 3e5 + 10;
 
int id[MAX], sz[MAX];
int find(int x) {
    if (id[x] != x) id[x] = find(id[x]);
    return id[x];
}
bool unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    id[b] = a;
    sz[a] += sz[b];
    return true;
}
 
namespace seg {
    int n;
    pair<int, int> tree[4*MAX];
    void update(int i, pair<int, int> x) {
        i += n;
        tree[i] = x;
        while (i > 1) {
            i /= 2;
            tree[i] = max(tree[2*i], tree[2*i+1]);
        }
    }
    pair<int, int> query(int l, int r) {
        pair<int, int> res = {0, 0};
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = max(res, tree[l++]);
            if (r & 1) res = max(res, tree[--r]);
        }
        return res;
    }
}
namespace hld {
	vector<tuple<int, int, int>> g[MAX];
	int pos[MAX], sz[MAX];
	int pai[MAX];
	int h[MAX], t;
    int N;
    pair<int, int> sobe[MAX], v[MAX];
 
    void add(int a, int b, int w, int id) {
        g[a].emplace_back(b, w, id);
        g[b].emplace_back(a, w, id);
    }
 
	void build_hld(int k, int p = -1, int f = 1) {
		v[pos[k] = t++] = sobe[k]; sz[k] = 1;
		for (auto& i : g[k]) if (get<0>(i) != p) {
			auto [u, w, id] = i;
            sobe[u] = {w, id}; pai[u] = k;
			h[u] = (i == g[k][0] ? h[k] : u);
			build_hld(u, k, f); sz[k] += sz[u];
 
			if (sz[u] > sz[get<0>(g[k][0])] or get<0>(g[k][0]) == p)
				swap(i, g[k][0]);
		}
		if (p*f == -1) build_hld(h[k] = k, -1, t = 0);
	}
	void build(int root = 0) {
		t = 0;
        for (int i = 0; i < N; ++i) {
            pos[i] = sz[i] = pai[i] = h[i] = 0;
            sobe[i] = v[i] = {0, 0};
        }
		build_hld(root);
        seg::n = t;
        for (int i = 0; i <= 5*t; ++i) seg::tree[i] = {0, 0};
        for (int i = 0; i < t; i++) {
            seg::update(pos[i], sobe[i]);
        }
	}
    pair<int, int> query(int a, int b) {
        pair<int, int> res = {0, 0};
        while (h[a] != h[b]) {
            if (pos[a] > pos[b]) swap(a, b);
            res = max(res, seg::query(pos[h[b]], pos[b]));
            b = pai[h[b]];
        }
        if (pos[a] > pos[b]) swap(a, b);
        res = max(res, seg::query(pos[a] + 1, pos[b]));
        return res;
    }
    void update(int a, int b, int w) {
        if (sz[a] < sz[b]) swap(a, b);
        sobe[b].first = w;
        seg::update(pos[b], sobe[b]);
    }
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

vector<int> solve(int n, int m, int q, vector<iii> edg, vector<vector<iii>> sets){
    vector<int> ans(q, 1);
    vector<int> par(n), lvl(n); iota(all(par), 0);
    vector<iii> actions;
    auto findp = [&] (auto&& self, int u) -> int { return (par[u] == u ? u : self(self, par[u]));};
    auto merge = [&] (int u, int v) {
        u = findp(findp, u), v = findp(findp, v);
        if (u == v) return false;
        if (lvl[u] < lvl[v]) swap(u, v);
        par[v] = u;
        actions.pb({u, v, lvl[u]});
        if (lvl[u] == lvl[v]) lvl[u]++;
        return true;
    };
    auto rollback = [&] () {
        assert(!actions.empty());
        auto [u, v, l] = actions.back(); actions.pop_back();
        par[v] = v, lvl[u] = l;
    };
    vector<array<int, 4>> ev;
    for (auto [w, u, v] : edg) ev.pb({w, q, u, v});
    for (int i = 0; i < q; ++i) {
        for (auto [w, u, v] : sets[i]) ev.pb({w, i, u, v});
    }
    sort(all(ev));
    for (int l = 0, r = 0; l != sz(ev); l = r) {
        int tipo = ev[l][1];
        if (tipo == q) {
            while (r != sz(ev) and ev[r][1] == ev[l][1]) merge(ev[r][2], ev[r][3]), r++;
        } else {
            int bef = sz(actions);
            while (r != sz(ev) and ev[r][1] == ev[l][1]) ans[tipo] &= merge(ev[r][2], ev[r][3]), r++;
            while (sz(actions) != bef) rollback();
        }
    }
    return ans;
}

vector<int> mvkaio(int n, int m, int q, vector<iii> edges, vector<vector<iii>> queries) {
    for (int i = 0; i < n; i++) {
        id[i] = i, sz[i] = 1;
    }
    for (int i = 0; i < n; ++i) hld::g[i].clear(); 
    vector<int> ord(m);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        return get<0>(edges[i]) < get<0>(edges[j]);
    });
    hld::N = n;
    for (int i : ord) {
        auto &[w, a, b] = edges[i];
        if (unite(a, b)) {
            hld::add(a, b, w, i);
        }
    }
 
    hld::build();
    vector<int> ans;
    for (auto aaa : queries) {
        int k = sz(aaa);
        bool ok = true;
        vector<iii> used;
        for (auto [w, a, b] : aaa) {
            if (ok) {
                auto [w2, id2] = hld::query(a, b);
                auto [__, a2, b2] = edges[id2];
 
                if (w2 >= w) {
                    hld::update(a2, b2, 0);
                    used.push_back({__, a2, b2});
                } else ok = false;
            }
        }
        ans.pb(ok); 
        for (auto [w, a, b] : used) hld::update(a, b, w);
    }
    return ans; 
}

int32_t main(){_
    int t = 1;
    while (true) {
        int n = 3, m = rnd(n-1, n*(n-1)/2);
        vector<vector<int>> foi(n, vector<int>(n));
        vector<iii> edg;
        int maxw = 2;
        for (int i = 1; i < n; ++i) {
            int p = rnd(0, i-1);
            foi[p][i] = 1;
            edg.pb({rnd(1, maxw), p, i});
        }
        while (sz(edg) != m) {
            int i = rnd(0, n-2), j = rnd(i+1, n-1);
            if (foi[i][j]) continue;
            foi[i][j] = 1;
            edg.pb({rnd(1, maxw), i, j});
        }
        int q = rnd(1, 1);
        vector<vector<iii>> queries(q);
        vector<vector<int>> recu;
        for (auto& x : queries) {
            int k = rnd(1, m);
            vector<int> caras;
            vector<int> pp(m); iota(all(pp), 0);
            shuffle(all(pp), rng);
            for (int i = 0; i < k; ++i) x.pb(edg[pp[i]]), caras.pb(pp[i]+1);
            recu.pb(caras);
        }
        auto my = solve(n, m, q, edg, queries);
        auto mv = mvkaio(n, m, q, edg, queries);
        if (my != mv) {
            cout << "Found in test case " << t << endl;
            cout << n << ' ' << m << ' ' << q << endl;
            for (auto [z, u, v] : edg) cout << u+1 << ' ' << v+1 << ' ' << z << endl;
            for (auto x : recu) {
                cout << sz(x) << endl;
                for (auto y : x) cout << y << ' ';
                cout << endl;
            }
            cout << "My output: ";
            for (auto x : my) cout << x << ' ';
            cout << endl;
            cout << "MvKaio's output: ";
            for (auto x : mv) cout << x << ' ';
            cout << endl;
            exit(0);
        }
        cout << "Accepted on test " << t++ << endl;
    }
}
