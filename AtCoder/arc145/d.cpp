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
bitset<2000000000> mark;
void solve() {
	int n; ll m; cin >> n >> m;
	vector<int> ans;
	int act = 0;
	ll SHIFT = m / n;
	ll sum = 0;
	for (int i = 1; i <= n; ++i) {
		while (mark[act]) act++;
		for (int j = 0; j < i-1; ++j) mark[2*act-ans[j]+SHIFT] = 1;
		ans.pb(act + SHIFT), sum += act + SHIFT, act++;
	}
	act--;
	ll mod_m = ((m%n)+n)%n;
	ll need = (mod_m - sum%n + n) % n;
	act += need;
	sum -= ans.back();
	while (mark[act]) act += n;
	ans.back() = act + SHIFT;
	sum += ans.back();
	ll shift = (m-sum) / n;
	for (auto x : ans) cout << x + shift << ' ';


}

int32_t main() {_
	int t = 1; //cin >> t;
	while(t--) solve();
}
