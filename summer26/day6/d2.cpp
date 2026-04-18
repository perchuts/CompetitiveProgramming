#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define pb push_back

using namespace std;

using ll = long long;
const int LINF = 1e18;

struct node{
	pair<int,int> val;
	int lazy;
	node *l, *r;
	node () {}
	node(pair<int,int> v) : val(v), lazy(0), l(NULL), r(NULL) {}

	void prop(){
		val.first += lazy;
		if (l) l->lazy += lazy;
		if (r) r->lazy += lazy;
		lazy = 0;
	}	
};

void merge(node* &a, node* &b){
	if (!a) swap(a,b);
	if (!b) return;
	a->prop(), b->prop();
	if (a->val > b->val) swap(a,b);
	merge(rand()%2 ? a->l : a->r,b);
}	

pair<int,int> pop(node* &R){
	R->prop();
	auto ret = R->val;
	node* tmp = R;
	merge(R->l, R->r);
	R = R->l;
	if (R) R->lazy -= ret.first;
	delete tmp;
	return ret;
}	

void apaga(node* R) {if (R) apaga(R->l), apaga(R->r), delete R;}

int dmst(int n, int r, vector<pair<pair<int,int>,int>>& ar){
	vector<int> p(n); iota(p.begin(),p.end(),0);
	function<int(int)> find = [&](int k) {return p[k]==k?k:p[k]=find(p[k]);};
	vector<node*> h(n);
	for (auto e : ar) {
		node* novo = new node({e.second, e.first.first});
		merge(h[e.first.second], novo);
	}
	vector<int> pai(n,-1), path(n);
	pai[r] = r;
	int ans = 0;

	for (int i = 0; i < n; ++i){
		int u = i, at = 0;
		while (pai[u] == -1){
			if (!h[u]){
				for (auto i : h) apaga(i);
				return LINF;
			}
			path[at++] = u,  pai[u] = i;
			auto [mi,v] = pop(h[u]);
			ans += mi;

			if (pai[u = find(v)] == i){
				while (find(v == path[--at]) != u)
					merge(h[u],h[v]),h[v]=NULL,p[find(v)] = u;
				pai[u] = -1;
			}
		}
	}

	for (auto i : h) apaga(i);
	return ans;
}

int solve(){
	int n; cin >> n;
	int m; cin >> m;
	vector<pair<pair<int,int>,int>> ars;
	for (int i = 0; i < m; ++i){
		int a, b; cin >> a >> b;
		int w; cin >> w;
		ars.pb({{a,b},w});
	}

	if (n == 0) return 0;
	if (m == 0) return LINF;
	return dmst(n,0,ars);
}


int32_t main() {_
	int t; cin >> t;
	for (int i = 1; i <= t; ++i){
		int v = solve();
		if (v != LINF) cout << "Case #" << i << ": " <<  v << endl;
		else cout << "Case #" << i << ": " <<  "Possums!" << endl;
	}
}
