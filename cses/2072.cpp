#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
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
// Treap
//
// Todas as operacoes custam
// O(log(n)) com alta probabilidade, exceto meld
// meld custa O(log^2 n) amortizado com alta prob.,
// e permite unir duas treaps sem restricao adicional
// Na pratica, esse meld tem constante muito boa e
// o pior caso eh meio estranho de acontecer

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

template<typename T> struct treap {
	struct node {
		node *l, *r;
		int p, sz;
		T val, mi;
		node(T v) : l(NULL), r(NULL), p(rng()), sz(1), val(v), mi(v) {}
		void update() {
			sz = 1;
			mi = val;
			if (l) sz += l->sz, mi = min(mi, l->mi);
			if (r) sz += r->sz, mi = min(mi, r->mi);
		}
	};

	node* root;

	treap() { root = NULL; }
	treap(const treap& t) {
		throw logic_error("Nao copiar a treap!");
	}
	~treap() {
		vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->l), q.push_back(x->r);
			delete x;
		}
	}

	int size(node* x) { return x ? x->sz : 0; }
	int size() { return size(root); }
	void join(node* l, node* r, node*& i) { // assume que l < r
		if (!l or !r) return void(i = l ? l : r);
		if (l->p > r->p) join(l->r, r, l->r), i = l;
		else join(l, r->l, r->l), i = r;
		i->update();
	}
	void split(node* i, node*& l, node*& r, T v) {
		if (!i) return void(r = l = NULL);
		if (i->val < v) split(i->r, i->r, r, v), l = i;
		else split(i->l, l, i->l, v), r = i;
		i->update();
	}
	void split_leq(node* i, node*& l, node*& r, T v) {
		if (!i) return void(r = l = NULL);
		if (i->val <= v) split_leq(i->r, i->r, r, v), l = i;
		else split_leq(i->l, l, i->l, v), r = i;
		i->update();
	}
	int count(node* i, T v) {
		if (!i) return 0;
		if (i->val == v) return 1;
		if (v < i->val) return count(i->l, v);
		return count(i->r, v);
	}
	void index_split(node* i, node*& l, node*& r, int v, int key = 0) {
		if (!i) return void(r = l = NULL);
		if (key + size(i->l) < v) index_split(i->r, i->r, r, v, key+size(i->l)+1), l = i;
		else index_split(i->l, l, i->l, v, key), r = i;
		i->update();
	}
	int count(T v) {
		return count(root, v);
	}
	void add(T v) {
		node* at = new node(v);
		join(root, at, root);
	}
	void insert(T v) {
		if (count(v)) return;
		node *L, *R;
		split(root, L, R, v);
		node* at = new node(v);
		join(L, at, L);
		join(L, R, root);
	}

	void dfs(node* cur) {
		if (cur == NULL) return;
		dfs(cur->l);
		cout << char(cur->val);
		dfs(cur->r);
	}
	void cut_and_paste(int l, int r) {
		node *ini, *fim, *segment;
		index_split(root, ini, fim, l);
		index_split(fim, segment, fim, r-l+1);
		join(ini, fim, ini);
		join(ini, segment, root);
	}
	void erase(T v) {
		node *L, *M, *R;
		split_leq(root, M, R, v), split(M, L, M, v);
		if (M) delete M;
		M = NULL;
		join(L, R, root);
	}
	void meld(treap& t) { // segmented merge
		node *L = root, *R = t.root;
		root = NULL;
		while (L or R) {
			if (!L or (L and R and L->mi > R->mi)) std::swap(L, R);
			if (!R) join(root, L, root), L = NULL;
			else if (L->mi == R->mi) {
				node* LL;
				split(L, LL, L, R->mi+1);
				delete LL;
			} else {
				node* LL;
				split(L, LL, L, R->mi);
				join(root, LL, root);
			}
		}
		t.root = NULL;
	}
};

void solve(){
	int n, q; cin >> n >> q;
	string s; cin >> s;
	treap<int> t;
	for (int i = 0; i < n; ++i) t.add(s[i]);
	while (q--) {
		int l, r; cin >> l >> r;
		--l, --r;
		t.cut_and_paste(l, r);
	}
	t.dfs(t.root);
	cout << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
