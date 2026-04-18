#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll
#define PI pair<int,int>
#define f first
#define s second
#define pb push_back

using namespace std;

using ll = long long;

const int maxn = 3e4+10;
vector<PI> eds[4*maxn];

int n, lim;

void add(int ql, int qr, PI e, int x = 1, int l = 0, int r = lim){
	if (r < ql or qr < l) return;
	if (ql <= l and r <= qr){
		eds[x].pb(e);
		return;
	}
	int tm = (l+r)/2;
	add(ql,qr,e,2*x,l,tm); add(ql,qr,e,2*x+1,tm+1,r);
}

int li[maxn], sz[maxn];
int find(int x){
	if (li[x] == x) return x;
	return find(li[x]);
}

vector<pair<int&,int>> hist;
void rollb(int p){
	while (hist.size() > p){
		auto [a,b] = hist.back(); hist.pop_back(); a = b;
	}
}

void unite(int a, int b){
	a = find(a), b = find(b);
	if (a == b) return;
	if (sz[a] < sz[b]) swap(a,b);
	hist.pb({sz[a],sz[a]});
	hist.pb({li[b],li[b]});
	sz[a] += sz[b];
	li[b] = a;
}

int bip = true;

void add_edge(int a, int b){
	unite(a,b+n), unite(a+n,b);
	if (find(a) == find(a+n)){
		hist.pb({bip,bip});
		bip = false;
	}
}

const int maxq = 1e5+10;
int ans[maxq];
void solve(int x = 1, int l = 0, int r = lim){
	int p = hist.size();
	for (auto [a,b] : eds[x]) add_edge(a,b);
	if (l == r){
		if (bip) ans[l] = true;
	} else{
		int tm = (l+r)/2;
		solve(2*x,l,tm);
		solve(2*x+1,tm+1,r);
	}
	rollb(p);
}

int32_t main() {_
	int m; cin >> n >> m;
	lim = m;

	for (int i = 0; i < 2*n; ++i) li[i] = i;
	for (int i = 0; i < 2*n; ++i) sz[i] = 1;
	
	for (int i = 0; i < m; ++i){
		int a, b; cin >> a >> b;
		a--; b--;
		if (i) add(0,i-1,{a,b});
		if (i != m) add(i+1,m,{a,b});
	}

	solve();

	vector<int> vec;
	for (int i = 0; i < m; ++i){
		if (ans[i]) vec.pb(i);
	}

	cout << vec.size() << endl;
	for (auto v : vec) cout << v+1 << " ";
	cout << endl;
}
