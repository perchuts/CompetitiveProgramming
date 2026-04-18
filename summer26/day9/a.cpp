#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

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
/**
 * Author: chilli, Takanori MAEHARA, Benq, Simon Lindholm
 * Date: 2019-05-10
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/graph/arborescence.cc
 * and https://github.com/bqi343/USACO/blob/42d177dfb9d6ce350389583cfa71484eb8ae614c/Implementations/content/graphs%20(12)/Advanced/DirectedMST.h for the reconstruction
 * Description: Finds a minimum spanning
 * tree/arborescence of a directed graph, given a root node. If no MST exists, returns -1.
 * Time: O(E \log V)
 * Status: Stress-tested, also tested on NWERC 2018 fastestspeedrun
 */
/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure with undo.
 * If undo is not needed, skip st, time() and rollback().
 * Usage: int t = uf.time(); ...; uf.rollback(t);
 * Time: $O(\log(N))$
 * Status: tested as part of DirectedMST.h
 */
#define rep(i, a, b) for(int i = a; i < (b); ++i)
typedef pair<int, int> pii;
typedef vector<int> vi;

struct RollbackUF {
	vi e; vector<pii> st;
	RollbackUF(int n) : e(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;)
			e[st[i].first] = st[i].second;
		st.resize(t);
	}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		st.push_back({a, e[a]});
		st.push_back({b, e[b]});
		e[a] += e[b]; e[b] = a;
		return true;
	}
};


struct Edge { int a, b; ll w; };
struct Node { /// lazy skew heap node
	Edge key;
	Node *l, *r;
	ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};
Node *merge(Node *a, Node *b) {
	if (!a || !b) return a ?: b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }

pair<ll, vi> dmst(int n, int r, vector<Edge>& g) {
	RollbackUF uf(n);
	vector<Node*> heap(n);
	for (Edge e : g) heap[e.b] = merge(heap[e.b], new Node{e});
	ll res = 0;
	vi seen(n, -1), path(n), par(n);
	seen[r] = r;
	vector<Edge> Q(n), in(n, {-1,-1}), comp;
	deque<tuple<int, int, vector<Edge>>> cycs;
	rep(s,0,n) {
		int u = s, qi = 0, w;
		while (seen[u] < 0) {
			if (!heap[u]) return {-1,{}};
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w, pop(heap[u]);
			Q[qi] = e, path[qi++] = u, seen[u] = s;
			res += e.w, u = uf.find(e.a);
			if (seen[u] == s) { /// found cycle, contract
				Node* cyc = 0;
				int end = qi, time = uf.time();
				do cyc = merge(cyc, heap[w = path[--qi]]);
				while (uf.join(u, w));
				u = uf.find(u), heap[u] = cyc, seen[u] = -1;
				cycs.push_front({u, time, {&Q[qi], &Q[end]}});
			}
		}
		rep(i,0,qi) in[uf.find(Q[i].b)] = Q[i];
	}

	for (int i = 0; i < cycs.size(); ++i) {
		int u = get<0>(cycs[i]);
		int t = get<1>(cycs[i]);
		vector<Edge> comp = get<2>(cycs[i]);
		uf.rollback(t);
		Edge inEdge = in[u];
		for (auto& e : comp) in[uf.find(e.b)] = e;
		in[uf.find(inEdge.b)] = inEdge;
	}
	rep(i,0,n) par[i] = in[i].a;
	return {res, par};
}

void solve() {
    int n;
    while (cin >> n) {
		if (n == 0) break;
        vector<string> v(n);
        for (auto& x : v) cin >> x;
        auto kmp = [] (string s) {
            vector<int> pi(s.size());
            for (int i = 1, j = 0; i < s.size(); ++i) {
                while (j and s[j] != s[i]) j = pi[j-1];
                if (s[i] == s[j]) j++;
                pi[i] = j;
            }
            return pi;
        };
        vector<int> ok(n, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                string s = v[i] + "#" + v[j];
                auto pi = kmp(s);
                for (int k = v[i].size()+1; k < pi.size(); ++k) {
                    if (pi[k] == v[i].size()) ok[i] = 0;
                }
            }
        }
        vector<string> vv;
        for (int i = 0; i < n; ++i) if (ok[i]) vv.pb(v[i]);
        n = vv.size(), v = vv;
        v.pb("");
        // onde eu decidi enfiar a string 
        vector<vector<pair<int, int>>> opt(n+1, vector<pair<int, int>>(n+1));
        vector<Edge> g;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                string t = v[j] + "#" + v[i];
                auto pi = kmp(t);
                int cost = v[j].size();
                opt[i][j] = {v[i].size()-1, cost};
                for (int k = v[j].size() + 1; k < t.size(); ++k) {
                    if (ckmin(cost, (int) v[j].size() - pi[k])) opt[i][j] = {k - ((int)v[j].size() + 1), cost};
                }
                g.pb({i, j, cost});
            }

            g.pb({n, i, (int)v[i].size()});
            opt[n][i] = {-1, v[i].size()};
        }
        pair<int, vi> z = dmst(n+1, n, g); vi par = z.second;
        int h = 1;
        vector<vector<int>> label(n+1); vector<pair<int, char>> trie; vector<int> foi(n+1); foi[n] = 1; label[n].pb(0);
		function<void(int)> process = [&] (int u) {
            if (foi[u]) return;
            process(par[u]);
            foi[u] = 1;
			int pos = opt[par[u]][u].first, need = opt[par[u]][u].second;
            label[u].resize(v[u].size());
            int start = pos + need - v[u].size() + 1, lst = 0;
            for (int i = 0; i < v[u].size(); ++i) {
                if (i + start <= pos) label[u][i] = label[par[u]][i + start];
                else {
					label[u][i] = h++, trie.pb({lst, v[u][i]});
				}
                lst = label[u][i];
            }
		};
        for (int i = 0; i < n; ++i) process(i);
        cout << h << endl << 0 << endl;
		for (int i = 0; i < trie.size(); ++i) cout << trie[i].first+1 << " " << trie[i].second << endl;
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
