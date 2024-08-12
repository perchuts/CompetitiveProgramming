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
 	int n, c, k; cin >> n >> c >> k;
	string s; cin >> s;
	vector<int> dp(1<<c);
	vector<vector<int>> freq(n, vector<int>(c, -1));
	for (int i = 0; i < n; ++i) {
		if (i) for (int j = 0; j < c; ++j) freq[i][j] = freq[i-1][j];	
		freq[i][s[i]-'A'] = i;
		int mask = 0, cur = i;
		while (cur != -1) {
			int best = -1;
			mask |= (1 << (s[cur] - 'A'));
			for (int j = 0; j < c; ++j) {
				if ((mask>>j)&1) {}
				else if (cur != 0) {
					ckmax(best, freq[cur-1][j]);
				}
			}
			ckmax(dp[mask], i-best);
			cur = best;
		}
	}
	int ans = c, bck = s.back() - 'A';
	for (int i = 0; i < (1<<c); ++i) {
		for (int j = 0; j < c; ++j) {
			if ((i>>j)&1) ckmax(dp[i], dp[i-(1<<j)]);
		}
	}
	for (int i = 0; i < (1 << c); ++i) {
		int compll = (1 << c) - 1 - i;
		if ((i>>bck)&1) {
			if (dp[compll] < k) {
				ckmin(ans, __builtin_popcount(i));
			}
		}
	}
	cout << ans << endl;
}

int32_t main(){_
  int t = 1; cin >> t;
  while(t--) solve();
}
