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
	int n; cin >> n;
	vector<int> a(n);
	for (auto& x : a) cin >> x;
	int ans = 0;
	vector<vector<int>> lst(n+1);
	vector<int> dp(n+1);
	for (int i = 1; i <= n; ++i) {
		lst[a[i-1]].pb(i);
		if (i >= 2 and a[i-2] == a[i-1]) {
			int lst_freq = (sz(lst[a[i-1]]) == 2 ? 0 : lst[a[i-1]][sz(lst[a[i-1]])-3]);
			int fim = max(i-2-dp[i-2], lst_freq);
			dp[i] = i - fim;
		}
		ckmax(ans, dp[i]);
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}