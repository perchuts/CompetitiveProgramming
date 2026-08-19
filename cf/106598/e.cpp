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
// HLD - aresta
//
// SegTree de soma
// query / update de soma das arestas
//
// Complexidades:
// build - O(n)
// query_path - O(log^2 (n))
// update_path - O(log^2 (n))
// query_subtree - O(log(n))
// update_subtree - O(log(n))

// namespace seg { ... }

// SegTree
//
// Recursiva com Lazy Propagation
// Query: soma do range [a, b]
// Update: soma x em cada elemento do range [a, b]
// Pode usar a seguinte funcao para indexar os nohs:
// f(l, r) = (l+r)|(l!=r), usando 2N de memoria
//
// Complexidades:
// build - O(n)
// query - O(log(n))
// update - O(log(n))


const int MAX = 4e5 + 10;

namespace seg {
	ll black[4*MAX], white[4*MAX], lazy[4*MAX];
	int n, *v;

	ll build(int p=1, int l=0, int r=n-1) {
		lazy[p] = 0;
		if (l == r) {
            black[p] = 0;
        return white[p] = v[l];
    }
		int m = (l+r)/2;
    black[p] = 0;
        
		return white[p] = build(2*p, l, m) + build(2*p+1, m+1, r);
	}
	void build(int n2, int* v2) {
		n = n2, v = v2;
		build();
	}
	void prop(int p, int l, int r) {
        if (lazy[p] == 0) return;
        swap(black[p], white[p]);
        if (l != r) lazy[2*p] ^= 1, lazy[2*p+1] ^= 1;
		lazy[p] = 0;
	}
	ll query(int a, int b, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) return black[p];
		if (b < l or r < a) return 0;
		int m = (l+r)/2;
		return query(a, b, 2*p, l, m) + query(a, b, 2*p+1, m+1, r);
	}
	void update(int a, int b, int p=1, int l=0, int r=n-1) {
		prop(p, l, r);
		if (a <= l and r <= b) {
			lazy[p] ^= 1;
			prop(p, l, r);
        return;
		}
		if (b < l or r < a) return;
		int m = (l+r)/2;
		update(a, b, 2*p, l, m), update(a, b, 2*p+1, m+1, r);
        black[p] = black[2*p] + black[2*p+1];
        white[p] = white[2*p] + white[2*p+1];
	}
};


namespace hld {
	vector<pair<int, int> > g[MAX];
	int pos[MAX], sz[MAX];
	int sobe[MAX], pai[MAX];
	int h[MAX], v[MAX], t;

	void build_hld(int k, int p = -1, int f = 1) {
		v[pos[k] = t++] = sobe[k]; sz[k] = 1;
		for (auto& i : g[k]) if (i.first != p) {
			auto [u, w] = i;
			sobe[u] = w; pai[u] = k;
			h[u] = (i == g[k][0] ? h[k] : u);
			build_hld(u, k, f); sz[k] += sz[u];

			if (sz[u] > sz[g[k][0].first] or g[k][0].first == p)
				swap(i, g[k][0]);
		}
		if (p*f == -1) build_hld(h[k] = k, -1, t = 0);
	}
	void build(int root = 0) {
		t = 0;
		build_hld(root);
		seg::build(t, v);
	}
	ll query_path(int a, int b) {
		if (a == b) return 0;
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return seg::query(pos[b]+1, pos[a]);
		return seg::query(pos[h[a]], pos[a]) + query_path(pai[h[a]], b);
	}
	void update_path(int a, int b) {
		if (a == b) return;
		if (pos[a] < pos[b]) swap(a, b);

		if (h[a] == h[b]) return (void)seg::update(pos[b]+1, pos[a]);
		seg::update(pos[h[a]], pos[a]); update_path(pai[h[a]], b);
	}
	ll query_subtree(int a) {
		if (sz[a] == 1) return 0;
		return seg::query(pos[a]+1, pos[a]+sz[a]-1);
	}
	void update_subtree(int a, int x) {
		if (sz[a] == 1) return;
		seg::update(pos[a]+1, pos[a]+sz[a]-1, x);
	}
	int lca(int a, int b) {
		if (pos[a] < pos[b]) swap(a, b);
		return h[a] == h[b] ? b : lca(pai[h[a]], b);
	}
}

void solve() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n-1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        hld::g[u].pb({v, w});
        hld::g[v].pb({u, w});
    }
    hld::build(0);
    while (q--) {
        int u, v; cin >> u >> v; --u, --v;
        if (u != v) {
            hld::update_path(u, v);
        }
        cout << hld::query_subtree(0) << endl; 
    }
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
