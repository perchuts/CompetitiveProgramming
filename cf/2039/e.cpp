#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define pb push_back
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define int ll

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using iii = tuple<int,int,int>;

const int inf = 2e9+1;
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}


set<vector<int>> bruta[14];
int lim = 8;
void solve(){
	int n; cin >> n;
	vector<int> dp(n+1, 0);
	int ps = 0, cur = 0;
	for (int i = 4; i <= n; ++i) {
		dp[i] = cur;
		dp[i] = (dp[i] + i-3 + ((i-2)*(i-3)/2)) % mod;
		cur = (cur + dp[i] * i) % mod;
		ps = (ps + dp[i]) % mod;
		// agora comecando do zero!
		//if (i <= lim) cout << i << ": " << dp[i] << " totdp: " << dp[i]+i-1 << endl;
	}
	cout << (ps+n-1) % mod << endl;
}

void brute(vector<int> v, int n) {
	if (n > lim) return;
	bruta[n].insert(v);
	int inv = 0;
	for (int i = 0; i < v.size(); ++i) {
		for (int j = i+1; j < v.size(); ++j) {
			inv += (v[i] > v[j]);	
		}
	}
	vector<int> v2;
	v2.pb(inv);
	for (auto x : v) v2.pb(x);
	brute(v2, n+1);
	for (int i = 1; i < v2.size(); ++i) {
		swap(v2[i], v2[i-1]);
		brute(v2, n+1);
	}

}

int32_t main(){_
  int t = 1; cin >> t;
  //brute({0, 1}, 2);
  //for (int i = 1; i <= lim; ++i) {
  //  cout << "dp["<<i<<"]: " << bruta[i].size() << endl;
  //  if (i >= 6) continue;
  //  for (auto x : bruta[i]) {
  //  	for (auto y : x) cout << y << ' ';
  //  	cout << endl;
  //  }
  //  cout << endl;
  //}
  while(t--) solve();
}
