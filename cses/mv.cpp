#include <bits/stdc++.h>
using namespace std;
 
#define endl '\n'
#define fast_io cin.tie(0)->sync_with_stdio(0);
#define int ll
typedef long long ll;
 
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
		build_hld(root);
        seg::n = t;
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
 
 
 
int32_t main() {
    fast_io;
 
    int n, m, q; cin >> n >> m >> q;
    vector<tuple<int, int, int>> edges(m);
    for (auto &[w, a, b] : edges) {
        cin >> a >> b >> w; --a, --b;
    }
 
    for (int i = 0; i < n; i++) {
        id[i] = i, sz[i] = 1;
    }
 
    vector<int> ord(m);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        return get<0>(edges[i]) < get<0>(edges[j]);
    });
    for (int i : ord) {
        auto &[w, a, b] = edges[i];
        if (unite(a, b)) {
            hld::add(a, b, w, i);
        }
    }
 
    hld::build();
 
    while (q--) {
        int k; cin >> k;
        bool ok = true;
        vector<int> used;
        while (k--) {
            int i; cin >> i; --i;
            if (ok) {
                auto &[w, a, b] = edges[i];
                auto [w2, id2] = hld::query(a, b);
                auto &[_, a2, b2] = edges[id2];
 
                if (w2 >= w) {
                    hld::update(a2, b2, 0);
                    used.push_back(id2);
                } else ok = false;
            }
        }
 
        cout << (ok ? "YES" : "NO") << endl;
        if (!q) break;
 
        for (int &i : used) {
            auto &[w, a, b] = edges[i];
            hld::update(a, b, w);
        }
    }
 
    return 0;
}
