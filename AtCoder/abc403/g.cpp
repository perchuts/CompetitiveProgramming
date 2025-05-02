#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
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
const int mod = 1e9;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
// Splay Tree
//
// SEMPRE QUE DESCER NA ARVORE, DAR SPLAY NO
// NODE MAIS PROFUNDO VISITADO
// Todas as operacoes sao O(log(n)) amortizado
// Se quiser colocar mais informacao no node,
// mudar em 'update'

template<typename T> struct splaytree {
	struct node {
		node *ch[2], *p;
		int sz, s0, s1;
		T val;
		node(T v) {
			ch[0] = ch[1] = p = NULL;
			sz = 1;
            s0 = v.first;
            s1 = 0;
			val = v;
		}
		void update() {
            s0 = s1 = sz = 0;
            if (ch[0]) {
                sz = ch[0]->sz;
                s0 = ch[0]->s0;
                s1 = ch[0]->s1;
            }
            if (sz&1) s1 += val.first; 
            else s0 += val.first;
            sz++;
            if (ch[1]) {
                if (sz&1) s1 += ch[1]->s0, s0 += ch[1]->s1; 
                else s1 += ch[1]->s1, s0 += ch[1]->s0;
                sz += ch[1]->sz;
            }
		}
	};

	node* root;

	splaytree() { root = NULL; }
	splaytree(const splaytree& t) {
		throw logic_error("Nao copiar a splaytree!");
	}
	~splaytree() {
		vector<node*> q = {root};
		while (q.size()) {
			node* x = q.back(); q.pop_back();
			if (!x) continue;
			q.push_back(x->ch[0]), q.push_back(x->ch[1]);
			delete x;
		}
	}

	void rotate(node* x) { // x vai ficar em cima
		node *p = x->p, *pp = p->p;
		if (pp) pp->ch[pp->ch[1] == p] = x;
		bool d = p->ch[0] == x;
		p->ch[!d] = x->ch[d], x->ch[d] = p;
		if (p->ch[!d]) p->ch[!d]->p = p;
		x->p = pp, p->p = x;
		p->update(), x->update();
	}
	node* splay(node* x) {
		if (!x) return x;
		root = x;
		while (x->p) {
			node *p = x->p, *pp = p->p;
			if (!pp) return rotate(x), x; // zig
			if ((pp->ch[0] == p)^(p->ch[0] == x))
				rotate(x), rotate(x); // zigzag
			else rotate(p), rotate(x); // zigzig
		}
		return x;
	}
	node* insert(T v, bool lb=0) {
		if (!root) return lb ? NULL : root = new node(v);
		node *x = root, *last = NULL;;
		while (1) {
			bool d = x->val < v;
			if (!d) last = x;
			if (x->val == v) break;
			if (x->ch[d]) x = x->ch[d];
			else {
				if (lb) break;
				x->ch[d] = new node(v);
				x->ch[d]->p = x;
				x = x->ch[d];
				break;
			}
		}
		splay(x);
		return lb ? splay(last) : x;
	}
	int size() { return root ? root->sz : 0; }
	int count(T v) { return insert(v, 1) and root->val == v; }
	node* lower_bound(T v) { return insert(v, 1); }
	void erase(T v) {
		if (!count(v)) return;
		node *x = root, *l = x->ch[0];
		if (!l) {
			root = x->ch[1];
			if (root) root->p = NULL;
			return delete x;
		}
		root = l, l->p = NULL;
		while (l->ch[1]) l = l->ch[1];
		splay(l);
		l->ch[1] = x->ch[1];
		if (l->ch[1]) l->ch[1]->p = l;
		delete x;
		l->update();
	}
	int order_of_key(T v) {
		if (!lower_bound(v)) return root ? root->sz : 0;
		return root->ch[0] ? root->ch[0]->sz : 0;
	}
	node* find_by_order(int k) {
		if (k >= size()) return NULL;
		node* x = root;
		while (1) {
			if (x->ch[0] and x->ch[0]->sz >= k+1) x = x->ch[0];
			else {
				if (x->ch[0]) k -= x->ch[0]->sz;
				if (!k) return splay(x);
				k--, x = x->ch[1];
			}
		}
	}
	T min() {
		node* x = root;
		while (x->ch[0]) x = x->ch[0]; // max -> ch[1]
		return splay(x)->val;
	}
};
void solve(){
    int q; cin >> q;
    int z = 0;
    splaytree<ii> sexo;
    map<int, int> cnt;
    while (q--) {
        int y; cin >> y;
        int x = (y + z) % mod + 1;
        sexo.insert({x, cnt[x]++});
        z = (sexo.root)->s0;
        cout << z << endl;
    }
}

int32_t main(){_
    int t = 1; //cin >> t;
    while(t--) solve();
}
