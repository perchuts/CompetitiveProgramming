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

void solve(){
	int n; cin >> n;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
	auto solve = [&] (vector<int> vv) {
		int resp = 0;
		vector<int> id(n), mark(n), state(n);
		iota(all(id), 0);
		sort(all(id), [&] (int a, int b) { return vv[a] > vv[b]; });
		for (int i = 0; i < n / 2; ++i) resp += vv[id[i]], mark[id[i]] = 1;
		for (int i = 0; i < n; i += 2) if (mark[i] == mark[i+1]) state[i] = (mark[i] ? -1 : 1);
		int cur1 = 0, cur2 = 0, ed2 = 0, st1 = 0, smx = 0, smn = 0;
		for (int i = 0; i < n; ++i) {	
			cur1 += state[i], cur2 += state[i];
			ckmax(smx, cur1);
			if (ckmin(smn, cur2)) ed2 = (i+1)%n;
			ckmin(cur2, 0);
			if (ckmax(cur1, 0)) st1 = (i+1)%n;
		}
		if (smx >= -smn) return make_pair(resp, (st1+1+n)%n);
		return make_pair(resp, (ed2+1+n)%n);
	};	
	ii resp = solve(v);
	cout << resp.second << ' ' << resp.first << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
