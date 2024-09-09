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
	vector<vector<int>> g(n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].pb(v), g[v].pb(u);
	}
	vector<int> leaf(n);
	string s; cin >> s;
	auto dfs = [&] (auto&& self, int u, int p) -> void {
		leaf[u] = 1;
		for (auto v : g[u]) {
			if (v == p) continue;
			leaf[u] = 0;
			self(self, v, u);
		}
	};
	dfs(dfs, 0, 0);
	int falta_decidir = 0, gastar = 0, tot_leaf = 0;
	vector<int> cnt(2);
	for (int i = 1; i < n; ++i) {
		if (leaf[i]) {
			if (s[i] == '1') cnt[1]++; 
			else if (s[i] == '0') cnt[0]++;
			else falta_decidir++;
			tot_leaf++;
		} else if (s[i] == '?') gastar++; 
	}
	if (s[0] == '?') {
		if (cnt[0] != cnt[1]) {
			cout << max(cnt[0], cnt[1]) + falta_decidir/2 << endl; 
		} else {
			if (falta_decidir % 2) {
				if (gastar % 2) cout << cnt[0] + (falta_decidir+1)/2 << endl;
				else cout << cnt[0] + (falta_decidir)/2 << endl;
			} else {
				cout << cnt[0] + falta_decidir/2 << endl;
			}
		}
	} else {
		int quero = s[0] - '0';
		cnt[quero^1] += (falta_decidir+1)/2;
		cout << cnt[quero^1] << endl;
	}
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
