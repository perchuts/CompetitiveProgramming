#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll
//#define STRESS

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

void solve(int n, vector<int> v){
	int q0 = 0, q1 = 0, q2 = 0;
	for (auto x : v) {
		if (x == 0) q0++;
		else if (x == 1) q1++;
		else q2++;
	}
	auto ini = v;
	vector<ii> ops;
	vector<vector<vector<int>>> tem(3, vector<vector<int>>(3));
	for (int i = 0; i < n; ++i) {
		if (i < q0) tem[0][v[i]].pb(i);
		else if (i < q0+q1) tem[1][v[i]].pb(i);
		else tem[2][v[i]].pb(i);
	}
	// trivial
	while (!tem[0][1].empty() and !tem[1][0].empty()) {
		int a = tem[0][1].back(), b = tem[1][0].back();
		ops.pb({a+1, b+1});
		tem[0][1].pop_back(), tem[1][0].pop_back();
		tem[0][0].pb(a), tem[1][1].pb(b);
		v[a]--, v[b]++;
	}
	while (!tem[2][1].empty() and !tem[1][2].empty()) {
		int a = tem[2][1].back(), b = tem[1][2].back();
		ops.pb({a+1, b+1});
		tem[2][1].pop_back(), tem[1][2].pop_back();
		tem[2][2].pb(a), tem[1][1].pb(b);
		v[a]++, v[b]--;
	}
	while (!tem[0][1].empty() and !tem[1][2].empty()) {
		int a = tem[0][1].back(), b = tem[1][2].back(), c = tem[2][0].back();
		ops.pb({a+1, c+1});
		ops.pb({b+1, c+1});
		tem[0][1].pop_back(), tem[1][2].pop_back(), tem[2][0].pop_back();
		tem[0][0].pb(a), tem[1][1].pb(b), tem[2][2].push_back(c);
		v[a] = 0, v[b] = 1, v[c] = 2;	
	}
	while (!tem[0][2].empty() and !tem[1][0].empty()) {
		int a = tem[0][2].back(), b = tem[1][0].back(), c = tem[2][1].back();
		ops.pb({a+1, c+1});
		ops.pb({b+1, a+1});
		tem[0][2].pop_back(), tem[1][0].pop_back(), tem[2][1].pop_back();
		tem[0][0].pb(a), tem[1][1].pb(b), tem[2][2].push_back(c);
		v[a] = 0, v[b] = 1, v[c] = 2;	
	}
	assert(tem[0][2].size() == tem[2][0].size());
	if (!tem[0][2].empty()) {
		int um = tem[1][1].back();
		ops.pb({um+1, tem[2][0][0]+1});
		for (int i = 0; i < sz(tem[0][2]); ++i) {
			ops.pb({tem[0][2][i]+1, tem[2][0][i]+1});	
			if (i != sz(tem[0][2])-1) ops.pb({tem[0][2][i]+1, tem[2][0][i+1]+1});
		}
		ops.pb({tem[0][2].back()+1, um+1});
	}
	cout << ops.size() << endl;
	for (auto [x, y] : ops) cout << x << ' ' << y << endl;
	//for (auto [x, y] : ops) {
	//	--x, --y;
	//	if (abs(ini[x] - ini[y]) != 1) {
	//		cout << "WA!1" << endl;
	//		exit(0);
	//	}
	//	if (ini[x] < ini[y]) ini[x]++, ini[y]--;
	//	else ini[x]--, ini[y]++;
	//}
	//for (int i = 1; i < n; ++i) {
	//	if (ini[i-1] > ini[i]) {
	//		cout << "WA!2" << endl;
	//		exit(0);
	//	}
	//}	
	//if (sz(ops) > n) {
	//	cout << "WA!3" << endl;
	//	exit(0);
	//}
}

int32_t main(){_
  int t = 0;
#ifdef STRESS
  while (true) {
	  int n = rnd(1, 20);
	  vector<int> v(n);
	  int ok = 0;
	  for (auto& x : v) x = rnd(0, 2), ok |= (x == 1);
	  if (ok == 0) continue;
	  cout << n << endl;
	  for (auto x : v) cout << x << ' ';
	  cout << endl;
	  solve(n, v);
	  cout << "Accepted on test " << t++ << endl;
  }
#endif
  cin >> t;
  while(t--) {
	  int n; cin >> n;
	  vector<int> v(n);
	  for (auto& x : v) cin >> x;
	  solve(n, v);
  }
}
