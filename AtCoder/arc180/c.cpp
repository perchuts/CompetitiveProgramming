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
set<vector<int>> solutions;
int dp[110][3000];
void brute(vector<int> a) {
	int n = sz(a);
	solutions.clear();
	for (int i = 0; i < (1 << n); ++i) {
		vector<int> cur;
		int pr = 0;
		for (int j = 0; j < n; ++j) {
			if ((i>>j)&1) pr += a[j], cur.pb(pr);
			else cur.pb(a[j]);
		}
		solutions.insert(cur);
	}
}
void solve(){
	mt19937 rng(time(0));
	auto rnd = [&] (int l, int r) {
		uniform_int_distribution<int> uid(l, r);
		return uid(rng);
	};
	int n = 10;
	vector<int> v(n);
	//for (auto& x : v) cin >> x;
	for (auto& x : v) x = rnd(-10, 10);
	brute(v);
	int shift = 1050, ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= 10*i+shift + 30; ++j) {
			dp[i][j] = 0;
			int other = j - v[i-1], consegue = 0;
			if (j - shift == v[i-1]) continue;
			for (int k = i - 1; k >= 1; --k) {
				if (consegue) dp[i][j] = (dp[i][j] + dp[k][shift]) % mod;
				if (v[k-1] == (other - shift)) consegue = 1;
				dp[i][j] = (dp[i][j] + (other >= 0 ? dp[k][other] : 0)) % mod;
			}
			dp[i][j] = (dp[i][j] + consegue) % mod;
			ans = (ans + dp[i][j]) % mod;
		}
	}
	if (ans+1 != sz(solutions)) {
		cout << "Wrong answer" << endl;
		cout << n << endl;
		for (auto x : v) cout << x << ' ';
		cout << endl;
		cout << sz(solutions) << ' ' << ans+1 << endl;
		exit(0);
	}
	//cout << (ans + 1) % mod << endl;
}

void soln(){
	int n; cin >> n;
	vector<int> v(n);
	for (auto& x : v) cin >> x;
//	brute(v);
//	for (auto x : v) cout << x << ' ';
//	cout << endl;
	//for (auto s : solutions) {
	//  for (auto x : s) cout << x << ' ';
	//  cout << endl;
	//}
	int shift = 1050, ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= 10*i+shift + 30; ++j) {
			int other = j - v[i-1], consegue = 0;
			if (j - shift == v[i-1]) continue;
			for (int k = i - 1; k >= 1; --k) {
				if (consegue) dp[i][j] = (dp[i][j] + dp[k][shift]) % mod;
				if (v[k-1] == (other - shift)) consegue = 1;
				dp[i][j] = (dp[i][j] + (other >= 0 ? dp[k][other] : 0)) % mod;
			}
			dp[i][j] = (dp[i][j] + consegue) % mod;
			ans = (ans + dp[i][j]) % mod;
		}
	}
	//cout << sz(solutions) << ' ';
	cout << (ans + 1) % mod << endl;
}
int32_t main(){_
 // int o; cin >> o;
 // if (o) {
 //     int t; cin >> t;
 //     for (int i = 1; i <= t; ++i) {
 //   	  solve();
 //   	  cout << "test " << i << " ok" << endl;
 //   	  cout.flush();
 //     }
 // } else soln();
 soln();
}
