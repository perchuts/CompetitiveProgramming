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

void solve(){
	int n, m; cin >> n >> m;
	vector<int> a(n), ok(2*m+1), dp1 = ok, dp2 = ok, deg = ok;
	vector<vector<int>> g(2*m+1), gr = g, pot = g;
	for (auto& x : a) {
		cin >> x;
		int cur = x, pt = 0;
		while (cur % 2 == 0) pt++, cur /= 2;
		ok[cur] = 1, pot[cur].pb(pt);
	}
	for (int i = 1; i <= 2*m; ++i) {
		sort(all(pot[i]));
		pot[i].erase(unique(all(pot[i])), end(pot[i]));
		for (int j = 2*i; j <= 2*m; j += i) {
			if (ok[j]) g[i].pb(j), gr[j].pb(i);
		}
	}	
	queue<int> q;
	int cnt = 0;
	for (int i = 1; i <= 2*m; ++i) {
		if (ok[i] == 0) continue;
		cnt++;
		deg[i] = sz(g[i]);
		if (deg[i] == 0) q.push(i);
	}
	bool bom = true;
	while (!q.empty()) {
		auto x = q.front(); q.pop();
		// ent, quero calcular minha dp agora
		int mn = -1, okk = 0;
		for (auto y : g[x]) ckmax(mn, dp1[y]+1);	
		for (auto k : pot[x]) if (k >= mn) {
			if (okk == 0) dp1[x] = k, okk = 1;
			else ckmin(dp1[x], k);
		}
		bom &= okk;
		for (auto y : gr[x]) {
			deg[y]--;
			if (deg[y] == 0) q.push(y);
		}
	}
	for (int i = 1; i <= 2*m; ++i) {
		if (ok[i] == 0) continue;
		deg[i] = sz(gr[i]);
		if (deg[i] == 0) q.push(i);
	}
	while (!q.empty()) {
		auto x = q.front(); q.pop();
		// ent, quero calcular minha dp agora
		int mx = 100, okk = 0;
		for (auto y : gr[x]) ckmin(mx, dp2[y]-1);	
		for (auto k : pot[x]) if (k <= mx) {
			if (okk == 0) dp2[x] = k, okk = 1;
			else ckmax(dp2[x], k);
		}
		bom &= okk;
		for (auto y : g[x]) {
			deg[y]--;
			if (deg[y] == 0) q.push(y);
		}
	}
	for (int i = 1; i <= 2*m; ++i) {
		if (ok[i] == false) continue;
		//cout << i << ": " << dp1[i] << ' ' << dp2[i] << endl;
		//cout << "pot[" << i << "]: ";
		//for (auto x : pot[i]) cout << x << ' ';
		//cout << endl;
	}
	for (int i = 0; i < n; ++i) {
		int pt = 0, cur = a[i]; 
		while (cur % 2 == 0) pt++, cur /= 2;
		cout << ((cnt == m and bom and dp1[cur] <= pt and pt <= dp2[cur]) ? "Yes" : "No") << endl;
	}
}

// check if there is a good set containing A[i] for each i
// partition numbers x = 2^p * q in the set q, where q is odd
// can pick only one from each set -> exactly one from constraints. thank you setter!
// additional constraint: if you pick 2^p * q, then for 3*q, 5*q, ... you must pick a power of two strictly smaller than p, i.e.
// let v_2(q) be the power of two associated w/ the value you picked for q.
// the sequence of defined values of v_2(q), v_2(3q), v_2(5q), ... must be strictly decreasing
// so lets build a tree T s.t. i -> j iff i, j exists in A, i, j are odd and j is a multiple of i.
// when picking j, you must ensure that you can build this decreasing sequence for each prime number in the decomposition of j.
int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
