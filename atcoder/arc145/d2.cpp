#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl '\n'
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int long long
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
void solve() {
	int n, m, sum = 0; cin >> n >> m;
	vector<int> ans;
	for (int i = 1; i <= n; ++i) {
		int pot = 3, resp = 0;
		for (int j = 0; (1 << j) <= i; ++j) {
			if (i >> j & 1) resp += pot;
			pot *= 3;
		}
		ans.pb(resp), sum += resp;
	}
	int mod_m = (m%n + n) % n;
	for (int i = 0; sum % n != mod_m; sum++, i++) ans[i]++;
	int diff = (m - sum) / n;
	for (auto x : ans) cout << x + diff << ' ';
}
int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}
