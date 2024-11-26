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
const int mod = (119<<23)+1;
const int maxn = 3e5+100;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) {
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}
char meb[4*maxn];

void crivo(int lim) {
	for (int i = 2; i <= lim; i++) meb[i] = 2;
	meb[1] = 1;
	for (int i = 2; i <= lim; i++) if (meb[i] == 2)
		for (int j = i; j <= lim; j += i) if (meb[j]) {
			if (meb[j] == 2) meb[j] = 1;
			meb[j] *= j/i%i ? -1 : 0;
		}
}
void solve(){
	int n; cin >> n;
	vector<int> a(n);
	crivo(1000500);
	for (auto& x : a) cin >> x;
	vector<vector<int>> div(1000001);
	for (int i = 2; i <= 1000000; ++i) {
		for (int j = i; j <= 1000000; j += i) {
			div[j].pb(i);
		}
	}
	vector<int> dp(1000001);
	for (auto x : div[a[0]]) dp[x]++;
	for (int i = 1; i < n; ++i) {
		int my = 0;
		for (auto x : div[a[i]]) {
			my = my + meb[x] * dp[x] * -1;
			if (my < 0) my += mod;
			if (my >= mod) my -= mod;
		}
		for (auto x : div[a[i]]) {
			dp[x] += my;
			if (dp[x] >= mod) dp[x] -= mod;
		}
		if (i == n-1) cout << my << endl;
	}
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
