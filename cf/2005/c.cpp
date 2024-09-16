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

int dp[5], ndp[5], ok[26];
string narek = "narek";
ii vals[5];

void solve(){
	int n, m; cin >> n >> m;
	vector<string> ss(n);
	for (auto& x : ss) cin >> x;
	for (int i = 0; i < 5; ++i) dp[i] = -1e7;
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 5; ++j) ndp[j] = -1e7, vals[j] = {0, 0};
		for (int w = 0; w < 5; ++w) {
			int need = w, tot = 0;
			for (auto x : ss[i]) {
				tot -= ok[x-'a'];
				if (narek[need] == x) need = (need + 1) % 5, tot += 2;
			}
			vals[w] = {tot, need};
			if (w == 0) ckmax(ndp[need], tot);
		}
		for (int fim = 0; fim < 5; ++fim) {
			int xx = dp[fim] + vals[fim].first;	
			ckmax(ndp[vals[fim].second], xx);
		}
		for (int w = 0; w < 5; ++w) ckmax(dp[w], ndp[w]);
		for (int w = 0; w < 5; ++w) ckmax(ans, dp[w] - 2*w);
	}
	cout << ans << endl;
}

int32_t main(){_
	for (auto x : narek) ok[x-'a'] = 1;
	int t = 1; cin >> t;
	while(t--) solve();
}
