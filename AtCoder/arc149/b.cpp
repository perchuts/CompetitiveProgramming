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

int bit[maxn];

void insert(int x, int k, int n) {
	for (; x <= n; x += (x)&(-x)) ckmax(bit[x], k);
}		

int query(int x) {
	int ans = 0;
	while (x) {
		ckmax(ans, bit[x]);
		x -= x & (-x);
	}
	return ans;
}

void solve(){
	int n; cin >> n;
 	vector<int> a(n), b(n), c(n);
	for (auto& x : a) cin >> x;
	for (auto& x : b) cin >> x;
	for (int i = 0; i < n; ++i) c[a[i]-1] = b[i];
	int best = 0;
	for (int i = 0; i < n; ++i) {
		int my_best = query(c[i]) + 1;
		insert(c[i], my_best, n);
		ckmax(best, my_best + n);
	}
	cout << best << endl;
}

int32_t main(){_
  int t = 1; //cin >> t;
  while(t--) solve();
}
