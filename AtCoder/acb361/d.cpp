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

void solve(){
	int n; cin >> n;
	string s, t; cin >> s >> t;
	vector<vector<int>> dp((1 << (n+2)), vector<int>(n+1, inf));
	int mee = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == 'B') mee += (1 << i);
	}
	int mee2 = 0;
	for (int i = 0; i < n; ++i) {
		if (t[i] == 'B') mee2 += (1 << i);
	}
	dp[mee][n] = 0;
	queue<ii> q;
	q.push({mee, n});
	while (!q.empty()) {
		auto [mask, pos] = q.front();
		q.pop();
		for (int i = 0; i <= n; ++i) {
			int p1 = ((mask>>i)&1), p2 = ((mask>>(i+1))&1);
			if (i == pos || i == pos + 1 || i == pos - 1) continue;
			int novamask = mask;
			if (p1) novamask += (1 << pos);
			if (p2) novamask += (1 << (pos+1));
			novamask &= (((1<<(n+2))-1) - (1<<i) - (1<<(i+1)));
			if (dp[novamask][i] == inf) {
				dp[novamask][i] = dp[mask][pos] + 1;
				q.push({novamask, i});
			}
		}
	}
	cout << (dp[mee2][n] == inf ? -1 : dp[mee2][n]) << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
