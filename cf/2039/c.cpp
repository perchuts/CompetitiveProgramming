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

int solve(int x, int m){
	int ans = 0;
	// quero achar os 1 <= y <= m s.t. x^y divide x ou y.
	int comeco = 1;
	while (comeco <= x) comeco *= 2;
	for (int i = 1; i <= min(m, comeco-1); ++i) {
		int k = i ^ x;
		if (k % x == 0 or k % i == 0) ans++;
	}
	// agr entre comeco e 
	if (comeco > m) {
		return ans;
	}
	while (2 * comeco <= m) {
		ans += ((2*comeco-1) / x) - ((comeco-1)) / x; 
		comeco *= 2;
	}	
	// agora sei que o multiplo de x vai ter o mesmo msb que o proprio m
	//cout << x << ' ' << m << endl;
	int cur = 0, x2 = 0;
	for (int j = 61; j >= 0; --j) {
		if (x>>j&1) x2 += (1LL << j);
		if (((m>>j)&1) == 1) {
			if (cur == 0) {
				cur = (1LL << j);
				continue;
			}
			int nc = cur + (1LL << j);
			int a = (x2^cur) + (1LL<<j) - 1;
			ans += (a/x - (a-(1LL<<j)+1)/x);
			ans += ((a-(1LL<<j)+1)%x==0);
			cur = nc;
		}
	}
	int k = m ^ x;
	if (k % x == 0) ans++; 
	return ans;
}

int32_t main(){_
	int tt = 1;
	int t; cin >> t;
	while (t--) {
		int x, m; cin >> x >> m;
		cout << solve(x, m) << endl;
		
	}
	exit(0);
	//cout << solve(7, 14) << endl;
	//exit(0);
	while (true) {
		int x = rnd(1, 1000), m = rnd(1, 1000), ans = 0;
		for (int i = 1; i <= m; ++i) {
			int k = x ^ i;
			ans += (k % x == 0 or k % i == 0); 
		}
		int my = solve(x, m);
		if (my != ans) {
			cout << "Wrong answer on test " << tt << endl;
			cout << x << ' ' << m << endl;
			cout << "Your output: " << my << endl;
			cout << "Answer: " << ans << endl;
			exit(0);
		}
		cout << "Accepted on test " << tt++ << endl;
	}
}
