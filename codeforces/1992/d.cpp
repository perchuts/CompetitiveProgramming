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
	int n, m, k; cin >> n >> m >> k;
	string s; cin >> s; s += 'L';
 	vector<int> dp(n + 5, k + 5);
	dp[0] = 0;
	string s2; s2 += 'L'; s2 += s;
	swap(s, s2);
	assert(sz(s) == n + 2);
	for (int i = 1; i <= n + 1; ++i) {
		if (s[i] == 'C') continue;
		dp[i] = dp[i-1] + (s[i] == 'W');
		for (int j = i - 1; j >= max(0ll, i - m); --j) 
			if (s[j] == 'L') ckmin(dp[i], dp[j] + (s[i] == 'W'));
	}
	cout << (dp[n+1] <= k ? "YES" : "NO") << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
